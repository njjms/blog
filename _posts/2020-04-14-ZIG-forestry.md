---
layout: post
title: "Small Area Estimation with Gaussian Copula"
date: 2020-04-8 23:07:28 +0000
categories: [statistics, research]
---

The following are notes based on this [presentation](/assets/ms_references/monleon.pdf) by Dr. Lisa Madsen, Vicente Monleon, and Lisa Wilson.

# Premise: Forest inventory variables are difficult to model

The Forestry Inventory and Analysis program ([FIA](https://www.fia.fs.fed.us/about/about_us/index.php)) under the USDA Forest Service collects and analyzes data on the status, trends, and ownership of forests in the United States.
FIA analyses are critical for federal uses such as monitoring changing wildlife habitats, assessing ecosystem management practices, and evaluating policy and conservation initiatives.

Forestry inventory is an intensive process conducted by closely examining sampled plots of land and tabulating various variables of interest.
Inventory variables include things like:

+ Total volume (of wood)
+ Total biomass
+ Number of trees
+ Volume of particular trees, such as Douglas Fir or Hemlock
+ Tree cover
+ Other relevant information, such as soils, understory vegetation, tree crown conditions, down woody material, and invasive species

However, this is a difficult problem for the following reasons:

+ The data is spatially correlated
+ The data is often zero-inflated
+ Often positive and very skewed

These data conditions prevent classical statistical modeling approaches.
Traditional methods for heteroskedasticity or nonnormality such as simple transformations will not work for this type of data.

# Usage of the Copula Model

A **copula model** is a multivariate distribution function for which the marginal distributions of each variables are uniform.
These copula models take advantage of the *probability integral transform*, that is if $V \sim f$ with CDF $F$, then the variable $U = F(v)$ is uniformly distributed on the unit interval.
The benefit of these technique is that we can examine the marginal distributions separately and then fitted jointly with the copula using maximum likelihood.
Essentially, we can **separate the marginal distributions from the dependency strucutre of a given multivariate distribution**.

**Sklar's Theorem** (see [here](http://www.columbia.edu/~mh2078/QRM/Copulas.pdf)): Consider a $d$-dimensional CDF $F$ with marginals $F_1, \ldots , F_d$.
Then there exists a copula $C$ such that

$$
F(x_1, \ldots, x_d) = C(F_1(x_1),\ldots, F_d(x_d))
$$

for all $x_i \in (-\infty, \infty)$ and $i = 1, \ldots, d$.

**In short**, every multivariate distribution function can be expressed in terms of its univariate marginal distributions and a copula describing the dependence among them.
Pretty neat!

# Using Zero-Inflated Gamma

The volume data was examined to have a serious positive skew and heavy zero inflation.
After a cubic root transformation, the data achieved a more normal curve, *except* of course for the zeros in the data.

This is where the zero-inflated gamma distribution can help.
The observed value $V$ transformed to $U = g(V) = V^{1/3}$ can be modeled using a Bernoulli mixture of 0s and random Gamma variable

$$
U = (1 - B)(0) + BW
$$

where $B \sim Bernoulli(\pi)$ and $W \sim Gamma(\alpha, \beta)$.

*Note*: Madsen modeled the mean of $B$ and $W$ as a function of an indicator of forestland (based on of NLCD forest cover classes), LANDSAT tesseled cap "wetness" variable (tsc3), and their interaction.

In practice, employing the Gaussian copula consisted of the following steps, beginning with two transformations:

1. The first transformation is to estimate the cumulative distribution function of this marginal distribution $U = F(v)$
2. The second transformation is to use the univariate standard normal function $\Phi^{-1}(U)$ to get a standard normal random variable
3. Join the marginal standard normals together to get a multivariate standard normal distribution
4. Model the spatial dependence structure using a rank correlation matrix 

$$
C(v, \Sigma) = \Phi_{\Sigma} \left(\Phi^{-1}(F_1(v_1)), \ldots, \Phi^{-1}(F_n(v_n))\right)
$$
Note the use of the multivariate normal distribution with $\Sigma$

5. Use normal distribution tools for analysis and prediction like kriging
6. Backtransform to get back to the original scale

# Results

Once covariates like temperature and precipitation were included in the model, spatial correlation became negligible.
The semivariogram showed an essentailly flat curve.

Since this spatial correlation was very weak, this opened the door to using the ZIG model to model the total volume as well as volume of particular tree species.

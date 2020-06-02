---
layout: post
title: "Small Area Estimation: An Appraisal"
date:   2020-05-30 23:07:28 +0000
categories: [statistics, research]
---

This [paper](/assets/rao.pdf) and this [vignette](/assets/smallarea.pdf) provides a very useful overview on *small area estimation*: what it is, why we need it, techniques to do it, etc.
The following document are my notes on this paper.

# Introduction

Small area estimation is important in survey sampling since stakeholders are getting more interested in reliable sampling statistics for small areas.
This makes it necessary to borrow information from realted areas to find more accurate estimates for a given area.
Some techniques the authors emphasize are 

+ Empirical best linear unbiased estimator
+ Empirical and hierarchical Bayes

# What is a small area?

A small area can be a county, municipality, town, or a subpopulation within a large geographic area.
Most old small area estimation required census enumeration.
However, direct survey estimators are likely to have large standard errors since the sample size for the area of interest will be small.

New methods use related or similar small areas and connect them using supplementary data, such as census records.

# Demographic Examples

Old methods for estimation total population in a specific area such as Vital Rates (VR), CM-II, and HU are basically just special cases of multiple linear regression.
These *regression-symptomatic* procedures make use of symptomatic variables such as birth and death rates to estimation the population at a given year $t$.
They use procedures such as the **ratio-correlation** and **difference-correlation** methods.A

### Synthetic estimates

A synthetic estimate is when "an unbiased estiamtion is obtained from a sample survey for a large area; when this estimate is used to derive estimates for subareas under the assumption that the samll areas have the same characteristics as the large area, we identify these estimates as synthetic estimates".
Synthetic estimates are easy to understand and employ in most sampling frameworks.

A synthetic estimator of small area total $Y_i = \sum_g Y_{ig}$ where the population is split into $g$ subgroups is:

$$
\hat{Y}_i = \sum_g \left(\frac{X_{ig}}{X_{.g}}\right) \hat{Y}_{.g}
$$

Synthetic estimators however can be biased.

### Composite estimators

To balance the potential bias of a synthetic estimator with the instability of a direct estimator, we take a weighted average of the two estimators.
This is called a composite estimator.

$$
\hat{Y}_i = w_i \hat{Y}_{1i} + (1 - w_i) \hat{Y}_{2i}
$$

where the $Y_i$s are the direct and indirect estimators respectively.
There are several different ways to estimate these weights using MSE and variance.

# Small Area Models

Small area models considered here include random area-specific effects.
One of the most popular models is the Fay-Harriot model.
If we have $i$ small areas, then the model is a mixed effects model:

$$
y_i = x_i^T \beta + \nu_i + \epsilon_i\text{, } i = 1, \ldots, m
$$

where $x_i$ is the vector of known covariates, $\beta$ is a vector of unknown regression coefficients for the auxiliary variables, $\nu_i$ are area specific random effects, and $\epsilon_i$ represent the sampling errors.
It is assumed that $\nu_i \sim N(0, \psi)$ and $\epsilon_j \sim N(0, D_j)$ where pairs $i,j$ are independent.
Furthermore, we assume that $\psi$ is unknown but the $D_i$ values are known.

$\psi$ the variance of the random effects components can be estimation a few different ways.

1. Prasad-Rao Estimator
2. The Fay-Herriot Estimator where we iteratively solve $\frac{1}{m - p}\sum_{i=1}^{m} \frac{(y_i - x_i^T\beta)^2}{\psi + D_i} = 1$
3. Maximum Likelihood (assumes a normal likelihood)
4. Restricted Maximum Likelihood which is solved by an iterative Fisher scoring algorithm (see Wiley 2006)

The estimates of the regression coefficients is given by $(X^T V^{-1} X)^{-1} X^T V^{-1} y$ where $V$ is the variance-covariance diagonal matrix of $Y$ with $\psi + D_i$ elements.

The small area mean is a quantity $\eta = X\beta + \nu$ and the small area mean for the $ith$ small area is $\eta_i = x_i^T \beta + \nu_i$.

# BLUP vs EBLUP

If $\beta$ and $\psi$ are known, the best predictor of $\eta$ is given by

$$
X\beta + 
\begin{pmatrix}
\frac{\psi}{\psi + D_1} (y_1 - x_1^T\beta) \\
\ldots \\
\frac{\psi}{\psi + D_m} (y_m - x_m^T\beta) \\
\end{pmatrix}
$$

However, if only $\beta$ is unknown, it is customary to replace $\beta$ with the coefficient estimate in the above expression. The result is the **BLUP**.
If both $\beta$ and $\psi$ are unknown, we replace both with the coefficient and variance estimates and the resulting $\eta$ is called **EBLUP**.

There are estimates for the MSPE of EBLUP.

# R

The `smallarea` package is useful in employing Fay-Herriot models and performing small area estimation

{% highlight R %}
library(smallarea)
response <- c(1, 2, 3, 4, 5)
X <- cbind(c(1,1,1,1,1), c(1,2,4,4,1), c(2,1,3,1,5))
sampling.var <- c(.5, .7, .8, .4, .5)
answer <- prasadraoest(response, X, sampling.var)
answer$estimate
> 1.780361

answer <- fayherriot(response, X, sampling.var)
answer$estimate
> 1.793244
{% endhighlight %}

The `smallareafit` function is the main function in the `smallarea` library.
The function takes a formula as its first argument, but the formula needs to contain $D$ a column a sampling variances and $D$ should preceded the other variables.

{% highlight R %}
data <- data.frame(response = rnorm(5,3, 1.5), x1 = c(1,2,4,4,1), x2 = c(2,1,3,1,5), D = c(.5, .7, .8, .4, .5))
ans <- smallareafit(response ~D + x1 + x2, data, method = "FH")
ans
{% endhighlight %}

`ans` is a list containing a numeric vector for the EBLUP of the small area means, a numeric vector of estimated MSPE, an estimate of the variance component, a numeric vector containing the estimates of the regression coefficients.


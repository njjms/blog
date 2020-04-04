---
layout: post
title:  "Sampling and geostatistics for spatial data, ver Hoef (2002): literature review"
date:   2020-04-02 23:07:28 +0000
categories: statistics
---

In [this paper](/assets/ms_references/verhoef2002.pdf), ver Hoef gives a primer on **what** geostatistics is and how it differs from classic statistical sampling.

# Differences in Methods

The most fundamental difference between classical sampling and geostatistics is that classical sampling relies on **design based inference** while geostatistics uses **model based inferences**.
Both classical sampling and geostatistical estimators are unbiased and have valid variances and confidence intervals, but generally speaking geostatistical methods produce more efficient estimators.

What does ver Hoef mean by **design based vs. model based** inference and what are the differences between them?
In a word: **assumptions**, specifically assumptions on what is random and what is fixed.

Consider a scenario where a pattern of points is created from a deterministic function and then we randomly sample some of those points.
The pattern is fixed but the samples are random.
Statistical inference based on these random samples are design based inference.

Now consider the flip side of that scenario where the sampling occurs at fixed locations in the space.
The pattern itself is instead random (perhaps through an autoregressive process).
Statistical inference is then based on the random mechanism which governs how the data is generated.
This is an example of a model-based inference.

# Examples with infinite populations

Consider a spatially continuous (infinite population) for some fixed pattern, such as the depth of snow in a small study area.
A reasonable estimate would be to sample several points, take the mean of the depth, and then estimate the volume by multiplying the average by the known volume.
The variance in this case of simple sampling would be the familiar $\frac{s^2}{n}$.

If we were to use block kriging instead, we would assume that the pattern is the result of some random process and the sample unit locations are fixed (the estimator and prediction variance will be given by eq [5] and [6] in the appendix).

# Estimating spatial autocorrelation

A common assumption for spatial data is that they come from a stationarity model, that is, if $Z(s)$ is a random variable at location s, then $E[Z(s)] = \mu$, and the autocovariance only depends on the spatial relationship between variables, not their exact location in space.
These two assumptions together form the **second-order stationarity assumption**.

The autocovariance $C(h)$ requires a particular parametric form, and in this paper ver Hoef uses an isotropic exponentical model:

$$
C(\|h\|) = \theta_n I_{\|h\| = 0} + \theta_s exp(\|h\|/ \theta_r)
$$

where

+ $\|h\|$ is the Euclidean distance
+ The nugget effect $\theta_n$
+ The partial sill $\theta_s$
+ The range parameter $\theta_r$

When plotted, the autocovariance function looks like a decreasing function as lag increases.

This autocovariance function can be estimated in a variety of ways, and in this paper ver Hoef uses REML (see [Kitanidis 1983](https://agupubs.onlinelibrary.wiley.com/doi/epdf/10.1029/WR019i004p00909)).
In the case of no autocovariance, the REML estimate of variance is identical to the classical $s^2$.
ver Hoef makes the case that REML has many great advantages, notably being more "automatic" (vague wording) and that the alternative weighted least squares requires that you bin the lags between the locations.

ver Hoef then performs a simulation study where data is created using a fixed pattern in 2 dimensions with n=100.
The following validation statistics were computed for 1000 iterations:

+ Bias of estimated $\alpha$ between classical sampling and block kriging
+ RMSE $(\hat{\alpha_m} - \alpha)^2$
+ 80% confidence interval coverage $\hat{\alpha} \pm 1.28 \sqrt{\hat{\text{var}}{\hat{\alpha}}}$

The results for both BK and RS show no significant evidnece of bias since the bias is very small compared to RMSE.
Both methods have confidence intervals with accurate coverage.
BK however does have a smaller RMSE than RS.

# Inference for finite populations

In this scenario, suppose that we have a spatial area $A$ with $N$ total sample units.
The population total is the sum of the variable of interest over all $N$ units.

Using random sampling, the estimated variance of $\hat{\alpha_{RS}} = N^2(s^2 / n)(1 - n/N)$.
Notice that the finite population has a finite population correction factor of $1 - n/N$ which goes to 0 as $n$ grows to $N$.

In block kriging, we have to think carefully about our hypothesis. 
The parameter we are interested in can be rewritten $b^T z$ where $z = (z_s^T, z_u^T)^T$.
The weight vector $b$ can be defined so that we can focus on the total over the area, the average of the area, or an average of a small subregion.

# Comparison in fixed populations

A set of species diversity values from a grid of 200 plots is used for this comparison.
Similar to the study with the infinite populations, ver Hoef found that FPBK had a smaller RMSE than classical sampling.

# Simulation of random populations

To simulate spatially autocorrelated data, ver Hoef used the Cholesky decomposition (Cressie 1993, p201) with an exponential covariance model.
He simulated 1000 spatially autocorrelated data sets and for each data set, a random sample of size 50 was drawn as well as fixed systematic sample of size 50.
One design consideration for the fixed sample is to first characterize the spatial autocovariance at small distances, then spread the data locations out as much as possible.
Therefore ver Hoef used pairs of locations that were close together but then spread the pairs out as much as possible.

Once again, FPBK was shown to have a smaller RMSE than classical sampling.A

# Conclusions

Classical sampling is classic for a reason.
It has a lot of advantages, such as making pretty much no assumptions about the data since all inferences come from the sampling design.
The estimators from classical sampling tend to be based on the mean, so as a result, they are normally distributed.

Block kriging was technically inappropriate for a lot of the simulations done in this paper since those were not a result of a random process, but even still over repeated sampling these estimates still had a lower RMSE than classical sampling.
Block kriging does make use of a linear combination of the data, sort of like the sample mean, but with unequal weights.
A similar effect to CLT happens here (see [Davidson 1994](https://pdfs.semanticscholar.org/09bb/355e3f01df123e330ff7cfa86872099e44aa.pdf) for CLT on correlated data) happens where the weighted sums of block kriging tend toward a normal distribution over repeated sampling so the prediction intervals are approximately correct.
However, the convergence is not as fast as for independent data, so for situations with a surface or finite population with very skewed data, the block kriging results might not be favorable.

However, for a lot of ecological applications, using block kriging is still a good idea.
Random sampling is necessary for classical inference since it makes the random varialbes nearly uncorrelated.
However, with block kriging, since the autocorrelated is modeled, random sampling is not necessary.
This allows for more convenient and powerful sample designs for ecologists, as well as allowing for small area estimation.

As a final note, it is pretty difficult to randomly simulate an autocorrelated surface that is spatially continuous and where the value at every location is known, so ver Hoef did not attempt those simulations.


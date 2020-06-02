---
layout: post
title: "Maximum likelihood estimation of regression parameters with spatially dependent discrete data (2009): literature review"
date: 2020-04-8 23:07:28 +0000
categories: [statistics, research]
---

This [paper](/assets/ms_references/madsen2009.pdf) illustrates how to use a Gaussian copula to model discrete, dependent values like we would find in forestry applications.
The following document are my notes on this paper.

# Abstract

In statistics, a generalized estimating equation (GEE) is used to estimate the parameters of a generalized linear model with a possible unknown correlation between outcomes.
However, GEES aren't as successful when it comes to spatially correlated count data because of how it incorporates correlation.
This paper proposes using a spatial Gaussian copula model allows for maximum likelihood estimation of regression parameters for discrete, spatially dependent data.
Simulations suggest that these copula ML estimators are as efficient as GEE estimators in cases of weak spatial dependence and their efficiency surpasses that of GEE estimators as the spatial dependence increases.

# Background

When a spatially dependent response can be assumed to be Gaussian, the regression problem falls into the geostatistical framework.
We can use techniques such as weighted least squares and maximum likelihood to solve for the coefficients.
When the response is discrete however, researchers turn to [GEEs](https://online.stat.psu.edu/stat504/node/180/).
Some researchers even use GEEs for nonnormal spatial data.
However, this approach is flawed:

+ Spatial GEE models assume that responses are independent, conditional on a spatially correlated latent variable
+ Only correlation (linear dependence) is modeled. Correlation might not be a the right measure of dependence for highly nonnormal data.
+ GEE estimators are not asymptotically efficient, especially compared to maximum likelihood estimators

### Background on Generalized Estimating Equations

First introduced in this [paper](https://watermark.silverchair.com/73-1-13.pdf?token=AQECAHi208BE49Ooan9kkhW_Ercy7Dm3ZL_9Cf3qfKAc485ysgAAAlwwggJYBgkqhkiG9w0BBwagggJJMIICRQIBADCCAj4GCSqGSIb3DQEHATAeBglghkgBZQMEAS4wEQQMczU61jYcuTH0o8DLAgEQgIICD7OcUsv_ey-D5xmUT0wGeFVeIMZ1jbhHrbqYkOUG_cwNYaMmnmOVl5tXCZyfuvlJINafgo4J1i5gBcGvgo4WBP-6YY9_Fb3lCvqLedaKMX0xsQPF3FDfI9jq8b6bhbVISgMf782YgxPml2ti36mJ4LNDGWNRk9R-1ftm8uS0TargbwrbL_3qBiS7UaLc93-GpGfHkIBPnqd-MOPS6G9w1hAOuft2csN8PXsEQ7iVylBPIp5jRwKqfXh67i9XeeGO5kU9EmjQ537IucAyh3gH-U_-oPt1elRE9WScgVT-ZdYXurslPU0A-iUlJHFW1tTHFoZZK9hJeLNNO3np-worBcCnYSmr6QkNwV5aFGrDczso_DV752TMJmJxXuHx_ya08jCZkiNCq79lu9EPQStwNsYQ2m9QQGxVg84sTQbfgBq1ui2VQUQi4p_9LGGsHiopccBBK9DCzprjkq_5F0XzopbrwggarknUYQhZMdSrMEFSuyIvQZQvtDsadvH22YbXBUOwFYVCWmJBzzJmItNru_2AW8ELiSw23jPUij6LIaYH42Xa9M5zRCmo2ojifNF33QEkgGxbXYGMEqUoZD5VAWR51u5IxJM6S5gP0hidHQMgDGfL6Gg0nS_SlYbMvLhAeO6WVKpqIXAj3kbx7j2nR8plpiCbR70miJaHQNceFy_7B285aWEmakHr7iBJ_d2n) by Liang and Zeger but a succinct overview is provided by [PSU](https://online.stat.psu.edu/stat504/node/180/).

For a response variable $Y$ that can be either continuous or categorical and the individual response observations are **not** independent and a design matrix $X$, the form of the GEE is:

$$
g(\mu_i) = x_i^T \beta
$$

This form is similar to a regular GLM (notice the link function $g$) but full specification of the joint distribution is not required and therefore there is **no likelihood function.**
The covariance structure of the correlated responses must be specified and modeled somehow.

Assumptions:

+ The responses $Y_1, \ldots, Y_n$ are correlated or clustered
+ Covariates can be power terms or other nonlinear transformations of original independent variables like interaction terms
+ Homeskedastcity does not need to be satisfied
+ Errors are correlated
+ Covariances structure must be specified a priori.

An example of a covariance structure would be **independence**:

$$
\begin{pmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{pmatrix}
$$

Another example would be **exchangeable**:

$$
\begin{pmatrix}
1 & \rho & \rho \\
\rho & 1 & \rho \\
\rho & \rho & 1
\end{pmatrix}
$$

This method uses quasi-likelihood estimation, not ML estimation.
This quasi-likelihood estimate of $\beta$ arises from maximization of a normality-based log likelihood without assuming the response is normally distributed.
There is no closed-form solution so GEE estimates are obtained using an iterative algorithm (iterative quasi-scoring procedure).

GEE estimates are valid **even if** the covariance is misspecified.
However, the standard errors of these estimates will be suspect and it may not be a good idea to use these estimates in a confidence interval without some kind of adjustment.
In general, empirical based standard errors understimate the true standard errors unless the sample data is large.

# Methods

Copula models allows well-known geostatistical correlation structures to be used.
There are also no artificial limits on dependence and can model correlations up to the theoretical maximum. 
Copula models have been used to model dependence and construct multivariate distributions.

Given random variables $Y_1$ and $Y_2$ with continuous marginal distributions $F_1$ and $F_2$, the maximum possible correlation between $Y_1$ and $Y_2$ can be achieved via a Gaussian copula:

$$
C(y_1, y_2 | \delta) = \Phi_{\delta} \left(\phi^{-1}\left(F_1(y_1\right), \phi^{-1}\left(F_2(y_2)\right)\right)
$$

where $\phi$ is the standard normal cdf and $\phi_d$ is the bivariate normal cdf with correlation $\delta$.
This function is the joint distribution function of $Y_1$ and $Y_2$ whose dependence is determined by $\delta$, sometimes referred to as the *normal scoring* and is connected to other sources of dependence, like Kendall's $\tau$.

The Gaussian copula easily generalize to the multivariate setting.

$$
C(y, \Sigma) = \Phi_\Sigma \left(\phi^{-1}\left(F_1(y_1))\right), \ldots, \phi^{-1}\left(F_n(y_n))\right)\right)
$$

where $\Phi_\Sigma$ is the multivariate normal cdf with covariance matrix $\Sigma$.
Differentiating the above yields the joint density function

$$
c(y, \Sigma) = \| \Sigma\|^{-1/2} exp\left(-\frac{1}{2} z^T \left(\Sigma^{-1} - I_n\right)z \right) \prod_{i=1}^n f_i(y_i)
$$

where $z = \left(\phi^{-1}\left(F_1(y_1)\right), \ldots, \phi^{-1}\left(F_2(y_2)\right)\right)$.

If $Y_i$ are discrete, then the joint pmf $g(y, \Sigma) = P(Y_1 = y_1, \ldots, Y_n = y_n)$ contains $2^n$ terms but we can make it continuous by associating the $Y_i$s with a continous random variable $Y_i^{\*} = Y_i - U_i$ where $U_i$ are observations from a standard uniform distribution. 
This makes $Y_i^{\*}$ a continuous random variable with distribution function

$$
F_i^{*}(y) = F_i\left(\lfloor y \rfloor \right) + \left(y - \lfloor y \rfloor \right)P\left(Y_i = \lfloor y + 1 \rfloor \right)
$$

and density function 

$$
f_i^{*}(y) = P(Y_i = \lfloor y + 1 \rfloor )
$$

Note that no information is lost by continuously extending $Y_i$.
Furthermore, this continuoys extension preserves Kendall's $\tau$, so these continous extensions have the same dependence structure as $Y_i$ and $Y_j$.

If $Y$ is an isotropic discrete random spatial process observed at locations $s_1, \ldots, s_n$, then the multivariate Gaussian copula can be used to model the joint distribution of $\left(Y_1, \ldots, Y_n\right)$ by giving the copula correlation matrix $\Sigma$ a spatial form.
Specfically, define $\Sigma(\theta)$ to be an $n$ x $n$ correlation matrix with the $i, j$th element being

$$
\Sigma_{i, j}(\theta) = \rho(\| s_i - s_j \|)
$$

where $\rho(h)$ is an isostropic parametric correlogram.
Cressie 1993 (p.67) has a description of this **correlogram or autocorrelation function**:

$$
\rho(h) \equiv \frac{C(h)}{C(0)}, \text{ provided that } C(0) > 0
$$

where $C(0)$ is the *sill* of the semivariogram and with the properties that:

+ $C(h) = C(-h)$
+ $\rho(h) = \rho(-h)$
+ $\rho(0) = 1$

From our above equation for $C(y, \Sigma)$ depends on the ancillary statistic $U_i$, so if we integrate over the vector $\left(U_1, \ldots, U_n\right)$ and take the expected likelihood, we arrive at

$$
L(\beta, \theta, \phi | y) = E[\frac{exp(-(1/2)z^{*}\left(\Sigma^{-1} - I_n\right) z^{*} \prod_{i=1}^n f_i^{*}(y_i^{\*})}{2\pi^{n/1} \| \Sigma\|^{1/2}}]
$$

where $z^{\*} = \left(\phi^{-1}(F_1^{\*}(y_1^{\*}), \ldots, \phi^{-1}(F_n^{\*}(y_n^{\*})\right)$ and $y$ is the data vector.
This likelihood equation is equal to the true joint probability mass function $g(y, \Sigma)$.

The parameter vector $\xi = (\beta, \theta, \phi)$ can be estimated by maximizing the log of this equation.
Since what we are really interested in is $\beta$, the covariance parameters $\theta$ and $\phi$ are nuisance parameters and are only used to account for spatial dependence and overdispersion.
Under [regularity conditions](https://www.jstor.org/stable/2336405?seq=1), the MLEs will be consistent and asymptotically normal with asymptotic covariance matrix given by the Fisher Information.

# Real Data Example
Madsen demonstrated usage of these copula ML estimators using data on Japanese grub beetle density with percent soil organic matter content as a covariate.

The observed grub counts are overdispersed so we assumed a marginal negative binomial distribution with means

$$
\mu_i = exp(\beta_0 + \beta_1 x_i + \beta_2 x_i^2 + \beta_3 x_i^3)
$$

The correlogram $\rho(h)$ is assumed to be exponential with two parameters so that the $i,j$th element of the correlation matrix $\Sigma(\theta)$ is 

$$
\Sigma_{ij}(\theta) =
\begin{cases}
\theta_0 exp(-h_{ij}\theta_1) & \text{ for } i \neq j \\
1 & \text{ when } i = j
\end{cases}
$$

where $h_{ij}$ is the distance between the locations $y_i$ and $y_j$, $0 < \theta_0 \leq 1$ is the nugget parameter and $\theta_1 > 0$ is the "decay parameter".
It should be emphasized that this exponenetial model is not the correlation between counts separated by distance $h$.
It is *normal scoring* which is a quantity that is monotone related to $corr(Y_i, Y_j)$.

Variance estimates were obtained by numerically approximating the Hessian matrix $H$ at the MLE and taking the variance of $\hat{\xi}$ was $-\hat{H}^{-1}$.
Individual hypotheses $H_0: \beta_k = 0$ may be tested via a Wald statistic $W = \frac{\hat{\beta_k}}{SE\left(\hat{\beta_k}\right)}$ where $W$ follows an approximate standard normal distribution.
A 95% confidence interval can be obtained with a familiar looking formula:

$$
\hat{\mu_0} \pm 1.96 \sqrt{x_0^T \hat{var}(\hat{\beta}) x_0}
$$

where $x_0 = \left(1, x_0, x_0^2, x_0^3\right)$.

A point estimate of the overdispersion parameter $\phi$ can be used to obtain $var\left(y_i\right)$.

# Simulation Example

Spatial locations were simulated on a regular square grid with 1 unit spacing.
Spatial dependence is described as *effective range, the distance at which correlation drops to .05.
For each sample size, four levels of spatial dependence (weak (R = 1.2), low (R = 3.1), moderate (R = 5.3), and strong (R = 8.3)).
$N = 500$ sets were generated for each scenario and the ML estimates $\hat{\beta_{ML}}$ and $\hat{\beta_{GEE}}$ were compared using relative efficiency:

$$
\frac{(N-1)^{-1} \sum_{i=1}^N (\hat{\beta_{GEE}} - \bar{\hat{\beta_{GEE}}})^2}{(N-1)^{-1} \sum_{i=1}^N (\hat{\beta_{ML}} - \bar{\hat{\beta_{ML}}})^2}
$$

ML estimates were show in 11 out of 12 simulated scenarios with different sample sizes to be more efficient than GEE estimates.

Though the motivation for this work is to analyze spatially correlated discrete data, the model is general and can be applied to toehr correlated discrete data including longitudinal data.
In the spatial context, Gaussian copula correlation matrix is modeled using a spatial correlation function.
In other setting, other correlation models can be used.


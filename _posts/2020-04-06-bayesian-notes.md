---
layout: post
title:  Notes on Bayesian Statistics
date:   2020-04-06 23:08:28 +0000
categories: statistics
---

This is planned to be a running document for all of my notes in Statistics 559 at Oregon State University.

# 4/16 Reference Priors

Suppose we have $X_1, \ldots ,X_n \overset{\text{iid}}{\sim} f(x|\theta), \theta \in \Theta$.
Furthermore, suppose that $T = T(X_1, \ldots ,X_n)$ is a sufficient statistic.
Then

$$
\prod_{i=1}^n f(x_i | \theta) = f(T | \theta) f(X_1, \ldots ,X_n | T) \propto f(T | \theta)
$$

Let $\pi(\theta)$ represent *prior knowledge* about $\theta$ so that 

$$
\pi(\theta | X_1, \ldots ,X_n ) \propto \pi(\theta) f(T | \theta) \propto \pi(\theta | T)
$$

To find $\pi(\theta)$ which maximizes *mutual information* between $\theta$ and $T$, let 

$$
M(\pi, f) = \int \int f(\theta , T) log\left(\frac{f(\theta,T)}{\pi(\theta) f(T)}\right) d\theta dT
$$

Define a **reference prior** $\pi^{\*}$ as

$$
\pi^{*} = \text{arg max} M\left(\pi, f\right)
$$

There is a connection between the **mutual information** and the **Kullback-Leibler divergence**:
What is the KL divergence?
The KL divergence from pdf $g$ to pdf $f$ is defined as

$$
KL(f, g) = \int f(x) log\left(\frac{f(x)}{g(x)}\right) dx
$$

The KL divergence is not a distance metric, *but* it is similar in that $KL(f, g) \geq 0$ and is 0 if $f = g$.
Namely, KL divergence is not symmetric and does not satisfy the triangle inequality.
For $f \equiv N(\mu_0, \sigma_0^2)$ and $g \equiv N(\mu_1, \sigma^2_1$ we get 

$$
KL(f, g) = \frac{1}{2} \left(\frac{\sigma^2_0}{\sigma^2_1} + \frac{(\mu_1 - \mu_0)^2}{\sigma^2_1} - 1 + log \left(\frac{\sigma^2_1}{\sigma^2_0}\right)\right)
$$

We can redefine mutual information in terms of KL divergence:

$$
M\left(\pi, f\right) = E[ KL(\pi(.|T), \pi(.)) ] = \int \pi(\theta) log \left(\frac{g(\theta)}{\pi(\theta)}\right) d\theta = -KL(\pi, g)
$$

where $exp\left(\int f(T | \theta) log \pi (\theta | T) dT\right)$.
$g$ is not a pdf, but it can be made into one using the proper normalizing constant.

So $\pi^{*}$ *maximizes expected KL divergence* from prior to posterior.
More specifically, $M(\pi, f)$ is maximised iff $KL(\pi, g)$ is minimized iff $\pi(\theta) \propto g(\theta)$.
However for a lot of situations, this is difficult!
Is it actually possible to solve $g(\theta)$?

There is an asymptotic result available to us! 
Let's go back to Theory II. 
Let $\hat{\theta}_n$ be the MLE for $\theta$.
Then for large $n$:

$$
\pi(\theta | T) \approx N(\theta | \hat{\theta}_n, (nI(\hat{\theta}_n))^{-1})
$$

We can apply this to $g(\theta)$.

$$
g(\theta) = exp\left(\int f(T | \theta) log(\pi(\theta | T)) dt \right) = exp\left( E_{f(.|\theta )} log \pi(\theta | T)\right)
$$

Note that

$$
E_{f(.|\theta )} log \pi(\theta | T) \approx \text{constants } + \frac{1}{2}log I\left(\theta\right)
$$

Hence,

$$
g(\theta) \approx exp\left(\text{constants } + \frac{1}{2}log I\left(\theta\right)\right) \prop exp \left(log \sqrt{I(\theta)}\right) = \sqrt{I(\theta )}
$$

So the distribution that maximizes KL divergence from the posterior *i.e.* a noninformative prior, we have Jeffrey's prior!
**TL;DR** In the single-parameter case, reference priors equal Jeffrey's prior!

# 4/14 Empirical Bayes prior

Suppose we have $X_1, \ldots ,X_n \overset{\text{iid}}{\sim} Bin(n, \theta )$, $0 < \theta < 1$.
Take $\pi(\theta) = Beta(a, b)$. Can we use the data to choose parameters $a$ and $b$?

Note that the marginal distribution is

$$
p(X_i = x) = \int_0^1 \binom{n}{x} \theta^x (1 - \theta)^{n-x} \frac{1}{B(a, b)} \theta^{a-1} (1 - \theta)^{b -1} d\theta 
$$

gives us

$$
P(X_i = x) = \binom{n}{x} \frac{B(x + a, n - x + b)}{B(a, b)}, x = 0, \ldots, n
$$

known as the beta-binomial distribution.
The first two moments will be $\mu = \frac{na}{a + b}$ and $\mu^2 = \frac{na (n(1+a) + b)}{(a+b)(a + b + 1)}$.
Then if we have data, we can calculate estimates for the first and second moments and then using the method of moments we can find estimates $\hat{a}$ and $\hat{b}$.
We then use these parameter estimates in our prior!

# 4/12 Jeffrey's Prior

Two basic interpretations for prior distributions:

+ *Population interpretation* is that the prior represents a population of possible parameter values from which $\theta$ has been drawn.
+ *State of knowledge interpretation* says that we express our knowledge and uncertainty about $\theta$ as if its value is a random realization from the prior distribution

In Laplace's initial work on Bayesian inference with the binomial distribution, he often justified use of the uniform prior using the *principle of insufficient reason*, that is, a uniform specification is appropriate when nothing is known about $\theta$.

Suppose that $X_1, \ldots ,X_n \overset{\text{iid}}{\sim} f(x | \theta), \theta \in \Theta$, Jeffrey's Prior  is that $\pi(\theta) \propto \sqrt{I(\theta)}$, supposing $f$ satisfies some regularity conditions.
Here are some Jeffrey's Priors.

|          | parameter  | Jeffrey's Prior                 |
|----------|------------|---------------------------------|
| binomial | p          | Beta(1/2, 1/2)                  |
| normal   | $\mu$      | $\pi(\theta) = 1$               |
| normal   | $\sigma^2$ | $\pi(\sigma^2) = \sigma^{-2}$   |
| Poisson  | $\lambda$  | $\pi(\lambda) = \lambda^{-1/2}$ |

Note that all these priors are also invariant priors.

A conjugate prior **can** sometimes be the same for an invariant prior, given certain hyperparameters!

# 4/9 Priors

A **conjugate prior** means that the posterior distribution and prior distribution come from the same family of distributions.
Famous examples include the binomial data with a beta prior, poisson data with a gamma prior, and the normal prior with normal data.

For a binomial distribution with a Beta prior for $\theta$, the posterior is

$$
p(\theta | y) \propto \theta^{y + \alpha -1} (1 - \theta)^{n - y + \beta - 1} = \text{Beta}(\theta | \alpha + y, \beta + n - y)
$$

Invariant priors are when $X_1, \ldots ,X_n \overset{\text{iid}}{\sim}$ location-scale family of distributions with $\theta \in \Theta$.
Ideally, we want a prior $\pi (\theta)$ such that 

$$
\int_a^b \pi(\theta) d \theta = \int_{a+c}^{b+c} \pi(\theta) d \theta
$$

However, a function with this property will not be a proper probability distribution $\int_{-\infty}^{\infty} \pi (\theta) d \theta = \infty$.
This is alright **if** the posterior distribution is still a proper probability distribution.

For scale family distributions, we have to transform the data first *ex* dividing all observations by a known $\sigma$ and then turning the scale family into a location family.
Suppose $X_1, \ldots ,X_n \overset{\text{iid}}{\sim}N(0, \sigma^2)$.
Then define

$$
\frac{X_i}{\sigma} \sim f(x), \frac{X_i^2}{\sigma^2} \sim \chi_1^2, \text{ and } log(X_i^2) - 2log(\sigma ) \sim log(\chi_1^2)
$$

If we define $Y_i = log(X_i^2)$, then $Y_1, \ldots, Y_n \overset{\text{iid}}{\sim} g(y - \theta), \theta = 2 log \sigma, -\infty < \theta < \infty$.
The invariant prior for $\theta$ is $\pi(\theta) = 1, \forall \theta \in \Theta$.

After using univariate change of variable formula with $\theta = 2 log \sigma $, we get that $\pi (\sigma) \propto \frac{1}{\sigma }$.

Using an invariant prior vs. a conjugate prior (say for normal data with a normal prior) can sometimes lead to posterior distributions which are the same if taken to some limit.
For example, with normal data and a normal prior vs invariant prior gives

$$
N(\bar{X}, \frac{\sigma^2}{n}), \text{ as } \tau \rightarrow \infty
$$

So both posteriors become $\pi(\theta) = N(\mu, \tau^2)$ with a very large $\tau$ which is known as a **vague/diffuse** prior!

Another example using invariant priors: Suppose that we have $X \overset{\text{iid}}{\sim} Bin(n, p)$.
Note that $X$ is **not** a location family.
If we apply the normal approximation $X \approx N(np, np(1-p))$, then by delta method $\sqrt{n}(g\left(\frac{X}{n} - g(p)\right) \rightarrow N(0, [g'(p)]^2 p)$.
We can use a variance stabilizing transformation, like $g(p) = sin^{-1}\sqrt{p} = \theta $ so the variance after delta method is a constant.
This is useful because now we can write $\theta $ as a location family and we can use a noninformative prior!

Using change of variable formula, we get that $\pi(p) \propto \frac{1}{\sqrt{p(1-p)}}$.
This is equivalent to $beta(\frac{1}{2}, \frac{1}{2})$, so we should be using this distribution as a noninformative prior instead of a flat uniform prior.


# 4/6 Chapter 1

In a sentence, **Bayesian inference** is the process of fitting a probability model to some data and summarizing the result by a probability distribution on the parameters of the model and on unobserved quantities, like predictions for new observations.
This process requires three steps:

1. Setting up a *full probability model* which is a joint probability distribution for all quantities in the problem
2. Conditioning on the observed data and obtaining a *posterior distribution*
3. Evaluating the fit of the model and the implications of the resulting posterior distribution

Bayesian inference is attractive because of the simplicity of interpretation compared to the frequentist paradigm.
A Bayesian interval is a direct statement on the likelihood of an unknown quantity.
This advantage also manifests itself in being able to set up complex models with lots of parameters!

For notation, we will use $\theta$ to refer to unobservable vector quantities/parameters of interest, $y$ denote the unobserved data, and $\tilde{y}$ denoting the unknown, but potentially observable quantities.

Bayesian statistical conclusions about $\theta$ or $\tilde{y}$ are made in terms of conditional *probability statements*.
These statements are conditional on the observed values of our data $y$.
Going back to our checklist, we start off with a *model* providing a joint probability distribution for $\theta$ and $y$.
This joint probability function can be written as a product of $p(\theta)$ referred to as the *prior distribution*, and $p(y|\theta)$, referred to as the sampling distribution.

Bayes' rule gives us the familiar formula for the *posterior density*:

$$
p(\theta | y) = \frac{p(\theta)p(y | \theta)}{p(y)}
$$

This is sometimes also written as:

$$
p(\theta | y) \propto p(\theta) p(y | \theta)
$$

To make inferences about unknown observables (*predictive inferences*), we follow a similar logic.
Before $y$ is considered, the distribution of the unknown but observable $y$ is:

$$
p(y) = \int p(\theta) p(y | \theta) d\theta
$$

which is often referred to as the *marginal distribution* of $y$, or the *prior predictive distribution*.

The *posterior predictive distribution* of $\tilde{y}$ is:

$$
p(\tilde{y} | y) = \int p(\tilde{y} | \theta) p(\theta | y) d \theta
$$

Note that this is basically an average of conditional predictions over the posterior distribution of $\theta$.

Bayesian inference follows the **likelihood principle**, which states that for a given sample of data, any two probability models $p(y | \theta)$ that have the same likelihood function yield the same inference for $\theta$.

The ratio of posterior densitities evaluated at the points $\theta_1$ and $\theta_2$ under a given model are called the *posterior odds* for $\theta_1$ compared to $\theta_2$.
Such a ratio often looks like this:

$$
\frac{p(\theta_1 | y)}{p(\theta_2 | y)} = \frac{p(\theta_1)}{p(\theta_2)} \frac{p(y | \theta_1)}{p(y | \theta_2)}
$$

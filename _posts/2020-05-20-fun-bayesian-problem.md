---
layout: post
title: "Bayesian time! Revisiting t-tests and F-tests"
date: 2020-05-20 23:07:28 +0000
categories: statistics
---

This quarter (my last quarter at OSU!), I decided to take a class in Bayesian statistics.
We just finished up our midterm where we tackled a pretty fun, easy problem where we explored the Bayesian equivalents of the t-test and the F-test *aka the bread and butter of intro statistics*.

# The problem

The following data is the amount of aluminum in 19 samples of pottery at two kiln sites.
We have the following data for each of the samples:

+ $n_1 = 14, \bar{x}_1 = 12.275, s_1 = 1.31$
+ $n_2 = 5, \bar{x}_2 = 18.18, s_2 = 1.78$

Assume that the amount of aluminum at site 1 has a normal distribution $N(\mu_1, \sigma^2_1)$ and site 2 has another normal distribution $N(\mu_2, \sigma^2_2)$.
We want to construct a 95\% Bayesian intervals for:

+ The difference in means $\mu_1 - \mu_2$
+ The ratio of the two variances $\sigma^2_1 / \sigma^2_2$

# Bayesian methods

In order to answer this question, we have to use the following facts on the posterior distributions for the Normal parameters which were derived on page 65 of *Bayesian Data Analysis* (best Bayesian book 4ever).
If we define our data vector as $X$, the marginal posterior distributions for $\mu$ and $\sigma^2$ are:

+ $\mu \lvert \sigma^2, X \sim N(\bar{X}, \sigma^2/n)$
+ $\sigma^2 \lvert X \sim \text{Scaled Inv-}\chi^2 (n - 1, s^2)$

If we make the reasonable assumptions that the samples are independent from one another, we can compute the posterior distributions for each $\mu$ and $\sigma^2$, sample from those posterior distributions, and then get the Bayesian intervals using those random samples.

There is no built-in sampling function in `R` for the inverse $\chi^2$ distribution, but if we use the fact that $\frac{(n-1)s^2}{\sigma^2} \sim \chi^2_{n-1}$, we can work around this.

If we random sample $X$ from the $\chi^2_{n-1}$ distribution, we can get an inverse $\chi^2$ distributed random observation $\sigma^2$ using $\sigma^2 = \frac{(n-1)s^2}{X}$.
We then use this $\sigma^2$ value in our conditional Bayesian posterior for $\mu$.

The `R` code that I used for this problem is provided here:

{% highlight R %}
llanderyn <- c(14.4, 13.8, 14.6, 11.5, 13.8, 10.9, 10.1, 11.6, 11.1, 13.4, 12.4, 13.1,12.7, 12.1)
island_thomas <- c(18.3, 15.8, 18.0, 18.0, 20.8)

n1 <- length(llanderyn)
xbar_1 <- mean(llanderyn)
s_1 <- sd(llanderyn)

sigma2_1_post <- ((n1-1)*s_1^2)/(rchisq(10000, df = n1 -1))
mu_1_post <- sapply(sigma2_1_post, FUN = function(x) rnorm(n = 1, mean = xbar_1, sd = sqrt(x/n1)))

n2 <- length(island_thomas)
xbar_2 <- mean(island_thomas)
s_2 <- sd(island_thomas)

sigma2_2_post <- ((n2-1)*s_2^2)/(rchisq(10000, df = n2 -1))
mu_2_post <- sapply(sigma2_2_post, FUN = function(x) rnorm(n = 1, mean = xbar_2, sd = sqrt(x/n2)))

mudiff_post <- mu_1_post - mu_2_post
quantile(mudiff_post, c(.025, .975))
{% endhighlight %}

The 95\% Bayesian credible interval we get for $\mu_1 - \mu_2$ is $(-8.24, -3.58)$.

There are a few ways to compute the Bayesian posterior interval for $\frac{\sigma^2_1}{\sigma^2_2}$.
The first way is to recognize that since the conditional posterior for $\sigma^2_1$ and $\sigma^2_2$ is scaled inverse-$\chi^2$, we can reorganize the ratio of the variables into an F-distribution.

$$
\sigma^2_1 \lvert data \sim \text{Scaled Inv-}\chi^2(n_1 -1, s^2_1) \text{ so }
$$

$$
\frac{\sigma^2_1}{(n_1 - 1) s_1^2} \sim \text{Inv-}\chi^2(n_1 - 1) \text{ and }
$$

$$
\frac{(n_1 - 1)s_1^2}{\sigma^2_1} \sim \chi^2(n-1)
$$

This also holds for $\sigma^2_2$.
Therefore, the ratio of $\frac{\sigma^2_1}{\sigma^2_2}$ can be turned into a scaled F-distribution through the following steps.

$$
\frac{s_2^2 / \sigma^2_2}{s_1^2 / \sigma^2_1} \sim F(n_2 - 1, n_1 - 1)
$$

$$
\frac{\sigma^2_1}{\sigma^2_2} \left(\frac{s^2_2}{s^2_1}\right) \sim F(n_2 - 1, n_1 - 1)
$$

$$
\frac{\sigma^2_1}{\sigma^2_2} \sim \frac{s_1^2}{s_2^2} F(n_2 - 1, n_1 - 1)
$$

So now we can either simulate a lot of scaled inverse-$\chi^2$ random variables for $\sigma^2_1$ and $\sigma^2_2$ which we have already done, simulate a lot of random observations from an F distribution and scale them, or just find the quantiles of this scaled F distribution.
Any of the following produce approximately the same intervals:

{% highlight R %}
s1_s2_ratio <- sigma2_1_post/sigma2_2_post
quantile(s1_s2_ratio, c(.025, .975))
# or...
s1_s2_ratio <- (s_1^2/s_2^2)*rf(length(sigma2_1_post), n2-1, n1-1)
quantile(s1_s2_ratio, c(.025, .975))
# or...
(s_1^2/s_2^2)*(qf(c(.025, .975), n2-1, n1-1))
{% endhighlight %}

The 95% Bayesian credible interval we get then for $\sigma^2_1 / \sigma^2_2$ is $(.07, 2.4)$

Note that we assumed that we have a noninformative prior on the random vector $(\mu, \sigma^2)$.
*Bayesian Data Analysis* suggests using a prior proportional to $\frac{1}{\sigma^2}$.

We could have used a conjugate prior, such as the Normal-Scaled-inverse-$\chi^2$ distribution which was mentioned in the textbook, but this would have required us to specify guesses for $\mu_1$, $\mu_2$, $\sigma^2_1$, and $\sigma^2_2$.
Since we did not have this information available to us, it was probably in our best interest to let the data ``speak for itself''.

# Comparison to frequentist methods

Using the base `R` functions `t.test` and `var.test`, we find that the t-test with the unequal variance assumption gives us a 95% frequentist confidence interval for $\mu_1 - \mu_2$ of $(-7.8, -3.4)$ and a 95\% frequentist inverval for $\sigma^2_1 / \sigma^2_2$: of $(.069, 2.42)$.

**Note** that `var.test()` uses this formula to calculate the confidence interval for $\frac{\sigma^2_1}{\sigma^2_2}$:

$$
\left[ \frac{s_1^2}{s_2^2}\frac{1}{F_{\alpha/2, n1-1, n2-1}}, \frac{s_1^2}{s_2^2}F_{\alpha/2, n2-1, n1-1} \right] 
$$

Looks familiar, right?
It's pretty much what we derived up above for the Bayesian method!

# Conclusion

These intervals are **close** to our Bayesian intervals, but not exactly the same.
I think the value in doing basic Bayesian problems is that not only do I practice Bayesian concepts, I also get a refresher on the properties and definitions of familiar probability distributions.
A helpful ancillary benefit for someone with an MS oral exam coming up!

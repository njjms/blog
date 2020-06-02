---
layout: post
title:  What is completeness anyways? (and other comments about statistics)
date:   2020-04-06 23:07:28 +0000
categories: statistics
---

When I was taking my statistical theory courses last year, I'll admit that I took a couple concepts at face value.
Most of those holes were patched up by the time I had to take my qualifying exams, but one thing that I still didn't really understand even while handing in my exam is the logic behind the **completeness** of a statistic.

### A quick definition

A statistic $T$ is **complete** for a particular distribution $F$ if:

$$
E_{\theta}[g(T)] = 0, \text{ }\forall \theta
$$

is true only if $g$ is the zero function (i.e. regardless of input, the function only returns 0).
In Casella-Berger, they make use of the confusing phrase "$g(T)$ is an unbiased estimator of $0$".
If there is any other function $g$ that makes the above equality true, then $T$ is not complete.

Proving a statistic is complete can get pretty hairy, but thankfully, most of the examples in Casella-Berger are showing that a statistic is *not* complete.
All that's required then is to find a function of $T$ where the expection is zero and that function is not the trivial zero function. 

### Ok, so what does completeness really mean?

Completeness is a condition which guarantees that there is **only one** unbiased estimator of $\theta$ based on the sufficient statistic $T$.

This is easy to see via contradition.
For example, suppose we had two different unbiased estimators of $\theta$, $g_1(T), g_2(T)$ where $P(g_1(T) \neq g_2(T)) > 0, \forall \theta$.
Then $g_1(T) - g_2(T))$ is an unbiased estimator for 0 (and therefore $T$ is not complete)!

After reading a bunch of [crossvalidated](https://stats.stackexchange.com/questions/196601/what-is-the-intuition-behind-defining-completeness-in-a-statistic-as-being-impos) posts, I also learned some other useful facts about sufficient statistics.
Namely, for sufficient statistics that **are not complete**, there exists function of that sufficient statistic which are not informative about $\theta$.
Conversely, a complete sufficient statistic is "maximally informative", that is, no function of a complete sufficient statistic is uninformative about $\theta$.

#### Completeness and minimal sufficient statistics

Anyone who has made a cursory reading of Casella-Berger knows that there are cases where no UMVUE exists.
As a prime example, there are setting where there is no UMVUE because there are some values of $\theta$ where the estimator has 0 variance, however, these estimators are not the UMVUE since they don't have the minimum variances for other values of $\theta$.
One thing to know though is that if a minimal sufficient statistic (found via Lehmann-Scheffe, for example) is not complete, there will not be a UMVUE because the optimal unbiased estimator changes depending on the value of $\theta$.

An example of a minimal sufficient statistic that is not complete is if we are given

$$
X_1, \ldots, X_n \sim N(\theta, \theta^2)
$$

and the minimal sufficient statistic is $T = (\sum X_i, \sum X_i^2)$.

Note that $E[T_1] = n\theta$ and $E[T_1^2] = n\theta^2 + n^2\theta^2$ and $E[T_2] = n(Var[X_i] + E[X_i]^2) = 2n\theta^2$.
Then we can define

$$
g(T) = \frac{T_2}{2n} - \frac{T_1^2}{n(n+1)}
$$

and note that $E[g(T)] = 0$. Therefore, the minimal sufficient statistic $T$ is not complete.

#### One cooool side fact... there are cases where no unbiased estimator exists!

Thanks to Dr. Sarah Emerson for this!

An unbiased estimator has to be unbiased for all values of the parameter it is estimating.
Here is a scenario where that is not the case!
Suppose we have:

$$
X_1, \ldots, X_n \sim Bernoulli(p)
$$

and suppose our parameter of interest is the odds $\theta = \frac{p}{1-p}$.

Now, consider a general estimator $T(X_1, \ldots, X_n)$.
If $T$ is unbiased, then $E_{\theta}[T] = \theta, \forall \theta$.

Now note that there are $2^n$ possible outcomes in the sample space.
We can index these outcomes from $j = 1, \ldots, 2^n$ and let $t_j$ be the value of $T$ when we observe outcome $j$.
Also define $n_j$ for the number of ones observed in outcome $j$.

We can write the expection of $T(X_1, \ldots, X_n) = \sum_{j = 1}^{2^n} t_j p^{n_j} (1-p)^{n - n_j}$.
Going back to $T$, we need $E[T] = \frac{p}{1-p} = \sum_{j = 1}^{2^n} t_j p^{n_j} (1-p)^{n - n_j}$ since $T$ is supposed to be unbiased.

**However**, this is not possible.
$\frac{p}{1-p}$ is not a polynomial of $p$, so it cannot be made equal to a finite order polynomial like $\sum_{j = 1}^{2^n} t_j p^{n_j} (1-p)^{n - n_j}, \forall p$.
So there is no unbiased estimator of $\theta$!

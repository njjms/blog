---
layout: post
title: "So that's what a random effect is?"
date:   2022-01-13 23:07:28 +0000
categories: statistics
---

Continuing the unofficial ongoing series of me learning things I should have learned in school but for realsies this time, I just had a really refreshing dive in to the tempestuous ocean of random effect calculations.
If you happen upon this blog, I invite you to take a dip!

# What is a random effect (and why would we use one)?

As has been famously pointed out by numerous statistical resources (see [here](https://bbolker.github.io/mixedmodels-misc/glmmFAQ.html#introduction) for some details), the definition of which covariates are random and which are fixed varies depending upon what dusty tome you're reading.
However, I find the following interpretation intuitive, and therefore, useful:

+ If the levels of the covariate cover your entire population, it's fixed
+ If the levels of the covariate are a sample from a possibly infinite population, it's random

Okay, that's fine for getting through the easy part of a statistics graduate program qualifying exam or having the self-satisfying knowledge that you've correctly specified your model formula, but what are the actual benefits to your model?
I myself wondered this for a while - I knew it was some vague notion of accounting for additional variance in your model that might otherwise end up in something you don't want, for example, the estimates of your fixed effects.
What sort of got the gears turning for me was this [stats.stackoverflow post](https://stats.stackexchange.com/questions/250277/are-mixed-models-useful-as-predictive-models).
Another thread in a similar vein is this [one](https://stats.stackexchange.com/questions/120964/fixed-effect-vs-random-effect-when-all-possibilities-are-included-in-a-mixed-eff).
The key theme that of these threads discussing the advantages of mixed models was "parsimony", that is to say, by correctly specifying random effects we make the model simpler and have to estimate less parameters?
Now how can that be?

In order to answer that question, we need some insight into what is **actually** happening in your computer when you specify a covariate to be random.

# Enter... some math

For the purposes of this journey, let's restrict our discussion to random effect intercepts.

Let's define our mixed effects model.

$$
Y = X\beta + Zb + \epsilon
$$

where the distribution of $b$ our random effects and $\epsilon$ are defined

$$
b \sim N(0, \psi) \textrm{ and } \epsilon \sim N(0, \sigma^2)
$$

Gelman and Hill is an excellent resource for mixed effects modeling, and they provide the following mathematical formula for random intercept estimates.

$$
\hat{b} = \frac{\psi}{\sigma^2} Z^t \Sigma (y - X\beta)
$$

where the big matrix $\Sigma$ is defined as 

$$
\Sigma = \left( \frac{\psi}{\sigma^2} Z Z^t + I_n \right)^{-1}
$$

We can already notice a few things here, without even jumping into R.
First of all, the estimator for the random intercepts depends on only these things: 

+ $\psi$, the variance of the random intercept
+ $\sigma^2$, the residual variance
+ $(y - X\beta)$, the residuals after only accounting for the fixed effects

This means that after fitting the fixed effect part of the model, we can estimate all the random intecepts using just $\psi$!
Random intercepts are just the residuals of the fixed effects, weighted and normalized by the ratio of the variances between the random effect and the residuals.
Imagine that if we treated this covariate as fixed, we would have to estimate these intercepts directly - particularly problematicif this is a factor with a lot of levels!
In addition to shrinking our intercept estimates, the decision to use a random effect has saved us degrees of freedom and simplified our model.

# R

Let's do a concrete [example](https://stats.stackexchange.com/questions/242759/calculate-random-effect-predictions-manually-for-a-linear-mixed-model) in R.
The `cake` dataset has 3 cake recipes being baked at 6 temperatures, with 15 replicates at each combination of recipe and temperature.
Consider the following mixed effects model with one fixed covariate (temp) and one random covariate (replicate).

{% highlight R %}
library(lme4)
m = lmer(angle ~ temp + (1 | replicate), data=cake)
summary(m)
{% endhighlight %}

The summary output of this mixed effect model is displayed below:

```
Linear mixed model fit by REML ['lmerMod']
Formula: angle ~ temp + (1 | replicate)
   Data: cake

REML criterion at convergence: 1671.7

Scaled residuals: 
     Min       1Q   Median       3Q      Max 
-2.83605 -0.56741 -0.02306  0.54519  2.95841 

Random effects:
 Groups    Name        Variance Std.Dev.
 replicate (Intercept) 39.19    6.260   
 Residual              23.51    4.849   
Number of obs: 270, groups:  replicate, 15

Fixed effects:
            Estimate Std. Error t value
(Intercept)  0.51587    3.82650   0.135
temp         0.15803    0.01728   9.146

Correlation of Fixed Effects:
     (Intr)
temp -0.903
```

If we look at the estimated random intercepts from this model, we would see the following:

{% highlight R %}
ranef(m)
   (Intercept)
1   14.2365633
2   13.0000038
3    4.6666680
4    1.1182799
5    0.2580646
6   -3.2903235
7   -4.6344100
8   -4.5806465
9   -4.6344100
10  -3.1827966
11  -2.1612910
12  -1.1397853
13  -0.2258065
14  -4.0967754
15  -5.3333349
{% endhighlight %}

Now, let's try to calculate this step-by-step instead of having `ranef` do all the heavy lifting.
The trickiest part is figuring out how to extract the design matrices corresponding to the random effect: $Z$ and $Z^t$.

Luckily, R has a built in function to extract components from a `merMod` object called `getME`.
This function takes a `merMod` as its first argument, and a string specifying the component to be extracted as its second argument. 
Two of those arguments are exactly what we need: "Z" and "Zt"!

To demonstrate that this approach works:

{% highlight R %}
z <- getME(m, "Z")
zt <- getME(m, "Zt")
str(z)
str(zt)
{% endhighlight %}

That's actually the hardest part!
Now we just need $\psi$, $\sigma^2$, and $y - X\beta$.

As we saw above in `summary(m)`, there is a table labeled "Random effects" which has the estimated variance for all random effects and the residual error.
From this table, we see that $\psi = 39.19$ and $\sigma^2 = 23.51$.

Finally, we can calculate $y - X\beta$ directly or we can use `predict(m, re.form = NA)`.
The `re.form = NA` option is needed here to enforce that predictions are calculated only using the fixed effects.
Note that if you just call `predict(m)`, the random intercepts will be included in the prediction calculations which will lead to results that are the opposite sign of what you would expect.

This gives us the final step!

{% highlight R %}
psi <- 39.19
sig <- 23.51
big_sig <- solve(((z * psi) %*% zt) / sig + diag(270))
(psi/sig * zt) %*% big_sig %*% (cake$angle - predict(m, re.form = NA))
15 x 1 Matrix of class "dgeMatrix"
1  14.2366373
2  13.0000713
3   4.6666923
4   1.1182857
5   0.2580659
6  -3.2903406
7  -4.6344340
8  -4.5806703
9  -4.6344340
10 -3.1828132
11 -2.1613022
12 -1.1397912
13 -0.2258077
14 -4.0967967
15 -5.3333626
{% endhighlight %}

Matches up well with the results from `ranef(m)`!

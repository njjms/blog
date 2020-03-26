---
layout: post
title:  "Finally understanding transformations in linear models"
date:   2019-02-25 07:07:28 +0000
permalink: /statistics/
categories: statistics
---

One thing that has always somewhat confused me is the interpretation and usage of transformations in linear models.
Since I'm studying stats, it's probably about time that I actually figure out how to use them properly.

# First thing's first!

Our general **motivation** here is that we are looking for a transformation that makes the relationship simpler.
In the context of linear models, we essentially want the relationship between the covariates and the response to be *linear*.

In other words, we want to find a function $g()$ such that:
$$
E[g(Y)] = X \beta \\
Var[g(Y)] = \sigma^2 I
$$

# Transforming the response

The challenging bit here with transforming the response is that it makes the interpretation *hard*.
This sucks because the response is what we care about.
We *don't* (at least generally speaking) care about the transformed response, so usually what we have to do is backtransform i.e. applying the inverse of $g()$.
However, parameters don't usually have nice interpretations, even when we backtransform.

There are special cases to this where interpretation is relatively straightforward, such as the common log transform.
There are tons of potential transformations though, so this isn't always possible.

# Box-Cox transformations

The Box-Cox transformation which relies on a parameter $\lambda$

$$
g_{\lambda}(y) = \frac{y^{\lambda} -1}{\lambda} \text{ when } \lambda \neq 0 \\
g_{\lambda}(y) = ln(y) \text{ when } \lambda = 0
$$

We can estimate this parameter using MLE, which R does for you using the `boxcox(lm, plotit=TRUE)` function from the MASS package.
This creates a nice looking graph with log-Likelihood as your y-axis and various values of $\lambda$ as the x-axis.

# Tranforming the predictors

We can transform each of the individual covariates using separate *basis functions*.
The individual basis functions can have their coefficients estimated using regular ol' least squares.

With the clever use of indicator functions, we can essentially have basis functions *take over* for each other in certain parts of the model.
This is useful if we think that there are multiple different groups in the model that should have different slopes and intercepts.

A related idea is *broken stick regression* where the transformation function is based around some constant $c$.
The function ensures that the two separate lines should be connected.
When plotted, it will appear like a... well, broken stick.
It's useful for when we think that the slope will change part way through.

When we transform the predictors, it is difficult to interpret the parameters.
For the most part though, the *best way* to present the results is a plot of the estimated functions for each $X_i$  
The significance of an individual variable(s) can still be assessed with an F-test.

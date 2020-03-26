---
layout: post
title: "Where did the Normal Distribution even come from?"
date: 2020-03-25 010:07:28 +0000
categories: statistics
---

So it's been a *long* while since I've thought about statistical theory, much less written a post about it.
But since it's spring break **and** since I'm locked in because of the coronavirus pandemic, I thought it would be a good time to revisit some good ol' math!

For a lot of folks, especially statisticians, no function is as beautiful or as useful as the pdf of the normal distribution:

$$
f_X(x | \mu, \sigma^2) = \frac{1}{\sqrt{2\pi\sigma^2}} \text{exp} \left( \frac{-(x - \mu)^2}{2 \sigma^2} \right)
$$


It's easy enough to see that a function of this form creates a bell curve but I have always been interested in finding out how de Moivre discovered this function.

### The Setup

No big surprise, but the discovery was motivated by gambling.
de Moivre came up with the normal distribution as an approximation of the binomial distribution, since he noticed that with large numbers of coin flips, the drawn distribution approached a smooth looking curve.

Consider two independent, identically distributed random variables $X$ and $Y$ with any arbitrary probability density function.
We assume that the function is even s.t. $f_X(x) = f_X(-x)$.
We also want the property that $lim_{x\rightarrow \pm \infty} g_X(x) = 0$, which makes sense... extreme values should be less likely.
If we consider the 2-tuple $(X, Y)$, let's think of the function of the norm of these two values $g(\sqrt{X^2 + Y^2})$ since the norm is a quantity of these variables that is unique.

Because of their independence, the joint pdf $f_{XY}(x,y)$ can be split apart and can be related back to $g(\sqrt{X^2 + Y^2})$.
This gives us

$$
f_X(x) f_Y(y) = g(\sqrt{X^2 + Y^2})
$$

For $X = 0$ and $Y = 0$, this gives us that $f_X(x) \propto g(x^2)$ and $f_Y(y) \propto g(y^2)$.

This is a great result!
It allows us to write $g(x^2)g(y^2) \propto g(x^2 + y^2)$.

Only two functions have this property, the exponential function and the natural logarithm.
However, we want the property that $lim_{x\rightarrow \pm \infty} g_X(x) = 0$.

In that case, we want the function $g_X(x)$ to be a negative exponential function, so something of the form $g(r) = \alpha e^{-\beta r}$.

This finally gives us that $f_X(x) \propto g(x^2) = \alpha e^{-\beta x^2}$.

### $\alpha$ and $\beta$ adjustments

We still need to make some adjustments and do some calculus to figure out the proper $\alpha$ and $\beta$.

First, let's start with the easiest part.
We know that we want our distribution to be centered at some value $\mu$.
Currently, our function $\alpha e^{-\beta x^2}$ is centered at 0.

To make it centered at $\mu$, we need to make sure that the power of the exponential is equal to 0 at $\mu$.
This would give us $f_X(x) \propto \alpha e^{-\beta (x - \mu)^2}$.

Now we need to figure out the form of $\alpha$ and $\beta$.
To do this, we (code: I) need to remember the Gaussian integral:

$$
\int_{-\infty}^{\infty} e^{-u^2} du = \sqrt{\pi}
$$

Applying this gives us with the fact that the pdf must integrate to 1 over the whole domain, we get:

$$
\alpha \int_{-\infty}^{\infty} e^{-\beta u^2} du = \alpha \sqrt{\frac{\pi}{\beta}} = 1
$$

Which is great! Now we have a relationship between $\alpha$ and $\beta$.

$$
\alpha = \sqrt{\frac{\beta}{\pi}}
$$

Now we just have to pick the correct $\beta$ and it will give us a value for $\alpha$.
Now we know that we want to have a dispersion parameter $\sigma^2$ and somehow incorporate it into the power term of the exponent since this will control how peaked or flat the curve will be.
If $\sigma^2$ is large, then the curve is very flat.
If $\sigma^2$ is small, then the curve will have a sharper peak.

If we set $\beta = \frac{1}{2 \sigma^2}$, then $\alpha = \frac{1}{\sqrt{2 \pi \sigma^2}}$!

--- 
layout: page
title: Theory Exams
permalink: /theory_comps/
---

Here are the statistical theory comprehensive exam questions from the last 20 or so years at Oregon State University.

## COMPS 2000

#### Problem 1

**TOPIC**: Conditional probability distributions

N is a Poisson random variable where $\lambda$ is chosen from an **Exp(1)** distribution

a. Find the unconditional probabilities $P[N = x]$ for $x = 0, 1, 2, \ldots$

\begin{align*}
P[N = x] = \int_{0}^{\infty} P(X | \lambda) P(\lambda) d\lambda
\end{align*}

**HINT:** Integral makes use of Gamma kernel trick $\int_0^{\infty} exp(-2\lambda) \lambda^x = \Gamma(x + 1) (\frac{1}{2})^{x+1}$

b. Find the unconditional expected value of N

\begin{align}
E[N] = \sum_{x = 0}^{\infty} x P(N = x) = \sum_{x = 0}^{\infty}x (\frac{1}{2})^{x + 1}
\end{align}

**HINT:** Makes use of $2E[N] - E[N]$ and the series identity $\sum_{x = 1}^{\infty} (\frac{1}{2})^x = 1$

c. Is the unconditional variance of N less than 1, equal to 1, or greater than 1?

**HINT:** Makes use of the law of total expectation and total variance

\begin{align}
E[N] = E[E[N | \lambda]] = E[\lambda] = 1 \\
Var[N] = E[Var[N|\lambda]] + Var[E[N | \lambda]] = E[\lambda] + Var[\lambda] = 1 + 1 = 2
\end{align}

#### Problem 2

**TOPIC:** MLEs and UMVUEs on shifted exponential distribution

Suppose that $X_1, \ldots, X_n$ are i.i.d. with a shifted exponential distribution 

a. Find a two dimensional sufficient statistic for $(\alpha, \beta)$.

**HINT:** Using the factorization theorem, we can split the likelihood function into separate functions for $\alpha$ and $\beta$.
We get $T = (X_{(1)}, \sum_{i=1}^{n} x_i)$ as our two dimensional sufficient statistic.

b. Find the MLEs for $\alpha$ and $\beta$

**HINT:** $f(x | \alpha, \beta)$ increases as $\alpha$ increases, so the MLE of $\alpha$ is $X_{(1)}$.
After doing some calculus, the MLE for $\beta$ is $\frac{1}{n}\sum (x_i - X_{(1)})$

c. Find the minimal sufficient statistic for $\beta$

Using Lehmann-Scheffe (1), we find that $\sum x_i$ or $\bar{X}$ is the minimal sufficient statistic for $\beta$.

d. Find the UMVUE of $\beta$

**HINT:** Since $\sum x_i$ is the minimal sufficient statistic for $\beta$ and 1-1 function $\sum (x_i - \alpha) \sim Gamma(n, \beta)$ is our complete sufficient statistic, let $T = \sum x_i - \alpha$ where $E[T] = n \beta$, so therefore $W = \frac{1}{n} \sum x_i - \alpha$ is he UMVUE for $\beta$.

e. Find the UMVUE for $\beta^2$

**HINT:** Try $E[\sum (x_i - \alpha)^2] = \sum (Var[x_i - \alpha] + E[x_i - \alpha]^2) = \sum \beta^2 + \beta^2 = 2n\beta^2$.
Therefore $W = \frac{1}{2n} \sum (x_i - \alpha)^2$ is the UMVUE for $\beta^2$.

#### Problem 3

**TOPIC:** Probability Modelling

A component has an exponential lifetime with an expected life of 10 years.
A unit consists of four identical, independent components.

a. A unit has 4 components wired in *series* if the failure of any single component makes the unit fail. What is the distribution of the units lifetime?

**HINT:** Use cumulative distribution function of $Y = min(X_1, \ldots, X_4)$.

\begin{align}
F_{Y}(y) = 1 - P(Y > y) = 1 - P(X_1 > y)P(X_2 > y)P(X_3 > y)P(X_4 > y) = 1 - exp(\frac{y}{10})^4
\end{align}

So $Y \sim Exp(\frac{5}{2})$

b. What is the units expected lifetime if the unit has its components in series?

c. A unit has the four components in *parallel* if the unit fails only when all the components fail. What is the distribution of the units lifetime if the unit has its components in parallel?

**HINT:** Let $W = max(X_1, \ldots, X_4)$. 
Using cumulative distribution functions, we find that $P(W < w) = P(X_1 < w)P(X_2 < w)P(X_3 < w)P(X_4 < w) = (1 - exp(-\frac{w}{10}))^4$ and $f_w(w) = \frac{2}{5}(1 - exp(-\frac{w}{10}))^3 exp(-\frac{w}{10})$

d. What is the unit's expected lifetime if the unit has its components in parallel?

**HINT:** Should be $\frac{2}{5}(10^2 - 3(5^2) + 3(\frac{10}{3})^2 - (\frac{10}{4})^2) = \frac{125}{6}$

#### Problem 4

**TOPIC:** UMPs with the $f(x|\theta) = \theta x^{\theta - 1}$ which is the Beta($\theta$, 1) distribution.

Let $X_1, \ldots, X_n$ is i.i.d. Beta($\theta$, 1) for 0 < x < 1 for some $\theta$ > 0.
Let $W = -ln(\prod x_i)$.

It can be shown that $2\theta W \sim \chi^2_{2n}$

a. Find the UMP size $\alpha$ test for testing $H_0: \theta = 1$ vs. $H_1: \theta > 1$

**HINT:** The monotone likelihood ratio is decreasing w.r.t. $\prod x_i$ so we reject for large values of $\prod x_i$ or $-ln(\prod x_i) < k^{*}$

b. Find the MLE of $\theta$

**HINT:** The MLE of $\theta$ is $-\frac{n}{ln(\prod x_i)}$

c. Find the Likelihood Ratio Test for testing $H_0: \theta = 1$ vs $H_1: \theta \neq 1$. Show that it rejects if W is too large or too small.

**HINT:** Find the Likelihood function with the MLE of $\theta$ plugged in and then take the derivative. 
It will be seen that we should reject $H_0$ if W is too large and too small compared to the sample size n.

d. Find a $1-\alpha$ CI based on the LRT in part c. Find constraints which determine the lower bound L(W) and upper bound U(W) of the confidence interval.

#### Problem 5

**TOPIC:** Showing $\bar{X}$ and $s^2$ is independent.

Suppose that $X_1, \ldots, X_n$ is a random sample of n independent observations from a $N(\mu, \sigma^2)$ distribution where $\mu$ and $\sigma^2$ are unknown parameters.

a. What is the distribution of $\bar{X}$? 

$N(\mu, \frac{\sigma^2}{n})$

b. What is the distribution of $s^2$?

$\frac{(n-1)s^2}{\sigma^2} \sim \chi^2_{n-1}$

c. Is the correlation between $\bar{X}$ and s positive, negative, or 0?

**HINT:** Use Basu's theorem. $\bar{X}$ is a CSS for $\mu$ and $s^2$ is ancillary for $\mu$. The estimates are independent and the correlation is 0.

d. Suppose that $Y_1, \ldots, Y_m$ is a random sample of m independent observations from a $N(0, \sigma^2)$ distribution where $\sigma^2$ is the same unknown parameter as above. Using only the Ys, find an unbiased estimator of $\sigma^2$ with variance $\frac{2\sigma^4}{m}$.

**HINT:** Using $\sum_{i = 1}^{m} (\frac{Y_i}{\sigma})^2 \sim \chi_m^2$ which gives us $E[\frac{1}{m}\sum_{i = 1}^{m} Y_i^2] = \sigma^2$

e. Let $\mu_0$ be hypothesized value for $\mu$. Suppose the sample of Xs and the sample of Ys are independent from one another. Using both samples, construct a test statistic T whose distribution when $\mu = \mu_0$ is a t-distribution with n+m-1 df.

**HINT:** Use $\frac{1}{n}\sum \frac{x_i}{\sigma} \sim N(\mu, \frac{1}{n})$, $\frac{(n-1)s^2}{\sigma^2} \sim \chi_{n-1}^2$, and $\sum_{i =1 }^{m} (\frac{Y_i}{\sigma})^2 \sim \chi^2_m$

We get $T = \frac{\sqrt{n}(\bar{X} - \mu_0)}{\sqrt{(n-1)s^2 + \sum Y_i^2 / (n + m - 1)}} \sim t_{n + m -1}$ and note that the numerator is independent of the denominator.

## COMPS 2001

#### Problem 1

**TOPIC:** Properties of the Standard Normal distribution

Let $X_1, \ldots, X_n$ be i.i.d. N(0, 1)

a. Find the correlation between $X_1$ and $\bar{X}$

**HINT:** $cov(x_1, \bar{X}) = \frac{1}{n}cov(x_1, x_1) = \frac{1, n}$ so correlation between $X_1$ and $\bar{X}$ is $\frac{\frac{1}{n}}{\sqrt{1}\sqrt{\frac{1}{n}}} = \frac{1}{\sqrt{n}}$

b. Find the distribution of $\bar{X}$ given $X_1 = x_1$

**HINT:** Use the fact that $\sum_{i = 2}^{n} x_i \sim N(0, n - 1)$ and set that pdf for the value $n\bar{X} - x_1$

c. Find the distribution of $X_1$ given that $\bar{X} = \bar{x}$

**HINT:** Use that fact that $X_1$ is independent of $X_2, \ldots, X_n$ on $f(X_1 = x_1 | \sum_{i = 2}^n x_i = n\bar{X} - X_1)$ to get the pdf

#### Problem 2

**TOPIC:** Properties of the Poisson distribution

$X_1, \ldots, X_n$ is i.i.d. Poisson($\lambda$)

a. Find a minimal sufficient statistic

**HINT:** Using Lehmann-Scheffe (1), we find that $T = \sum X_i$ is our minimal sufficient statistic

b. Let $\theta = P_{\theta}(X_1 = 0)$. Find an unbiased estimator of $\theta$ that is a function on the minimal sufficient statistic.

**HINT:** Use $E[I(X_1 = 0) | Y = y] = P(X_1 = 0 | \sum X_i = y) = (\frac{n-1}{n})^y$.
Then we plug in $\sum X_i$ for the value of $y$

c. Find the variance of the estimator in part (b).

**HINT:** Find $E[W^2]$ and $E[W]$ which requires multiplying a constant into a summation to get a Poisson pmf to get $E[W^2] = exp(-2\lambda + \frac{\lambda}{n})$

d. Let Y denote the number of observations $X_i$ that are 0. Find a function of Y that is unbiased for $\theta$.

**HINT:** $Y \sim Binomial(n, p = \theta)$, so $\frac{Y}{n}$ is unbiased for $\theta$

e. Find the variance of the estimator in part d.

**HINT:** $Var[\frac{Y}{n}] = \frac{\theta(1- \theta)}{n} = \frac{exp(-\lambda)(1 - exp(-\lambda))}{n}$

f. Which of the two estimators in parts (b) and (d) has the smaller variance?

**HINT:** Calculated Var[(b)] - Var[(d)]. Should be > 0, since (b) is the UMVUE.

#### Problem 3

**TOPIC:** UMP test for Beta($\theta + 1$, $\theta$) = $f(x | \theta) = (\theta + 1)x^\theta$

a. Find UMP test at level $\alpha$ for $H_0: \theta = \theta_0$ vs. $H_1: \theta > \theta_0$

**HINT:** The ratio should be monotone decreasing with respect to $\prod X_i$.
To get the critical value, use the fact that $Y = -ln(x) \sim exp((\theta + 1)^{-1})$ so $\sum Y_i \sim Gamma(n, (\theta + 1)^{-1})$

b. Find the rejection region of the UMP test when $\alpha = .05$ and $\theta_0 = 2$, $n = 10$.

c. Find a 95% confidence interval for $\theta$ when $n = 10$ by inverting the UMP test in part a.

**HINT:** Use the fact that $-(\theta +1)ln(\prod X_i) \sim Gamma(n, 1)$

#### Problem 4

**TOPIC:** Finding the MLE and LRT of the exponential($\frac{1}{\beta}$), x > 0, $\beta$ > 0

a. Find the MLE for $\beta$

**HINT:** The MLE of $\beta$ is $\frac{n}{\sum X_i}$

b. Derive the LRT for testing $H_0: \beta = \beta_0$ $H_1: \beta \neq \beta_0$

**HINT:** IF $\beta_0 > \beta_{MLE}$ then $\Lambda(X)$ is monotonically decreasing w.r.t. $\sum X_i$. The reverse if $\beta_0 < \beta_{MLE}$.

c. What is the asymptotic distribution of -2ln($\Lambda(X)$)

It is known to be $\chi^2_1$

d. If $n = 50$, $\beta_0 = 1$, $\sum X_i = 65$, $\alpha = .05$, do we acept or rejet the $H_0$ from (b)?

We should fail to reject $H_0$.

e. If $n = 50$, $\beta_0 = 1$, $\sum X_i = 65$, $\alpha = .05$, do we acept or rejet the $H_0$ using the LRT asymptotic test in part (c)?

We should fail to reject $H_0$.

#### Problem 5

Didn't do this one.

## COMPS 2002

#### Problem 1

**TOPIC:** Finding the UMP test for the Rayleigh distribution

$X_1, \ldots, X_n \sim f(x | \theta) = 2\theta^{-1} x exp(-\frac{x^2}{\theta})$

a. Derive a UMP test for $H_0: \theta \geq \theta_0$ vs $H_1: \theta < \theta_0$

**HINT:** Should find that the ratio is monotone increasing function w.r.t. $\sum X_i^2$

b. Derive the likelihood ratio test for $H_0: \theta = \theta_0$ vs. $H_1: \theta \neq \theta_0$

**HINT:** The unconstrained MLE  comes out to be $\frac{\sum X_i^2}{n}$

c. Derive the likelihood ratio test for $H_0: \theta > \theta_0$ vs. $H_1: \theta < \theta_0$

**HINT:** Note that the constrained MLEs has two cases: if $\theta_0 \leq \theta_{MLE}$, then $\theta_{0,MLE} = \theta_{MLE}$. IF $\theta_0 > \theta_{MLE}$, then $\theta_{0,MLE} = \theta_0$

d. Are the tests in (a) and (c) equivalent? Justify your answer.

**HINT:** Take the derivative of the likelihood ratio test in part (c) and it can be seen that $\Lambda(X)$ is the monotone increasing function w.r.t. $\sum X_i^2$ so the tests are equivalent.

#### Problem 2

**TOPIC:** Properties of Normal Distributions with different location parameters

$Y_1, \ldots, Y_n$ is i.i.d. $N(\beta x_i, \sigma^2)$ with known constants $x_1, \ldots, x_n$.

a. Find a two dimensional sufficient statistic for $(\beta, \sigma^2)$.

**HINT:** We should find that $(\sum y_i^2, \sum x_i y_i)$ is the two-dimensional sufficient statistic.

b. Find the maximum likelihood estimates for $\beta$ and $\sigma^2$

**HINT:** After doing a few partial derivatives, we get that $\beta_{MLE} = \frac{\sum x_i y_i}{x_i^2}$ and $\sigma^2_{MLE} = \frac{1}{n}(\sum y_j - \beta_{MLE} x_j)^2$

c. Find the UMVUE for $\beta$ 

**HINT:** After doing some factorization of the PDF, we see that the CSS for $\beta$ is $\sum x_i y_i$. Taking the expectation of this and then correcting it, we find that $W = \frac{\sum x_i y_i}{\sum x_i^2}$ is the UMVUE for $\beta$

d. Find the distribution of the MLE for $\beta$

**HINT:** $x_iy_i \sim N(\beta x_i^2, x_i^2\sigma^2)$ so $\frac{\sum x_i y_i}{\sum x_i^2} \sim N(\beta, \frac{\sigma^2}{\sum X_i^2})$

e. How would you obtain a $100(1- \alpha)$% CI for $\beta$

**HINT:** To begin, we need a pivotal quantity. 

Try $T = \frac{ \frac{\sum x_i y_i}{\sum x_i^2} - \beta / \sqrt{\frac{\sigma^2}{\sum x_i^2}}}{\frac{(n-1)s^2}{\sigma^2} / (n - 1)} \sim t_{n-1}$

#### Problem 3

**TOPIC:** Properties of a random sample

$X_1, \ldots, X_n$ is a random sample.

a. Suppose the only thing you known about the density of the Xs is that $Var(\frac{1}{\sqrt{X_i}}) < \infty$. Suggest a consistent estimator of $E[\frac{1}{\sqrt{X_i}}]$

**HINT:** Using WLLN, $\frac{1}{n} \sum \frac{1}{\sqrt{x_i}} \rightarrow_p E[\frac{1}{\sqrt{X_i}}]$ since the variance is finite, so the sample mean is our consistent estimator.

b. Suppose the denisty of $X_i$ is $f_{\theta}(x) = \frac{1}{\theta} exp(-\frac{x}{\theta}), x > 0$. Estimate $E[\frac{1}{\sqrt{X_i}}]$ using calculus and come up with an MLE.

**HINT:** The MLE will be the sample mean. The expected value an ve found using the Gamma kernel trick: $\int_{0}^{\infty} \frac{1}{\sqrt{X_i}} \frac{1}{\theta} exp(-\frac{x}{\theta}) = \Gamma(\frac{1}{2}) \theta^{-\frac{1}{2}} = \sqrt\frac{\pi}{\theta}}$

c. Are the estimates in (a) and (b) the same?

#### Problem 4

Didn't do this one.

#### Problem 5

**TOPIC:** Some results on limiting distributions

a. Let $X_n$ be a $\chi^2_n$ r.v. Show that the limiting distribution of $\sqrt{n}(\frac{X_n}{n} - 1)$ is N(0, 2) as $n \rightarrow \infty$.

**HINT:** Let $X_n = \sum_{i = 1}^{n} Z_i^2$ where $Z_i \sim N(0, 1)$. $E[Z_i^2] = 1$ and $Var[Z_i^2] = 2$. From CLT, then $\sqrt{n}(\frac{X_n}{n} - 1) \rightarrow_d N(0, 2)$

b. Let $Y_1, \ldots, Y_n$ be i.i.d. $N(\mu, \sigma^2)$ and let $s_n^2$ be the sample mean. Use the result in (a) to derive the limiting distribution of $\sqrt{n}(s_n^2 - \sigma^2)$ as $n \rightarrow \infty$.

**HINT:** Use the fact that $\frac{(n-1)s^2}{\sigma^2} \sim \chi^2_{n-1} = \sum_{i = 1}^{n-1}W_i and then invoke CLT to get the limiting distribution.

## COMPS 2003

#### Problem 1

**TOPIC:** MLE of the Pareto Distribution

$X_1, \ldots, X_n$ are i.i.d. $f(x) = \frac{aK^a}{x^{a+1}}, x \geq K$ and a, K are positive

a. Find a pair of jointly sufficient statistics for a and K

**HINT:** Factoring the pdf apart gives us $T = (\prod X_i, X_{(1)})$ as our jointly sufficient statistic.

b. Find he MLEs for a and K

**HINT:** Inspection shows that the likelihood increases as K increases, so $K_{MLE} = X_{(1)}$. Differentiating the log likelihood shows that $a_{MLE} = \frac{n}{\sum ln(\frac{x_i}{k})}$

c. Assuming K is known to be 1, find the MLE for $A = \frac{1}{a}$

**HINT:** Since MLEs are invariant, $A_{MLE} = \frac{\sum ln(x_i)}{n}$.

d. Find the mean and variance of A.

**HINT:** The distribution $Y_i = ln(X_i) \sim exp(\frac{1}{a})$ and $\sum Y_i \sim $ Gamma(n, $\frac{1}{a}$). This gives us that $E[A_{MLE}] = \frac{1}{a}$ and $Var[A_{MLE}] = \frac{1}{a^2 n}$

e. Compute the information $I_{x_i}(a)$ and find the CRLB for the variance of the unbiased estimators of A.

**HINT:** Recall that the pdf is given as $f(x|a) = \frac{a}{x^{a+1}}, x \geq 1$. Then $I_{x_i}(a) = \frac{1}{a^2}$ and the CRLB = $\frac{[g'(a)]^2}{n I_{x_i}(a)} = \frac{1}{a^4} \frac{a^2}{n} = \frac{1}{na^2}$

f. Is $A_{MLE}$ the UMVUE of $\frac{1}{a}$? 

**HINT:** Yes, since it achieves the CRLB. Alternatively, you can factor $f_{y}(y) = a exp(-ay)$ apart to see the CSS.

g. What is the asymptotic distribution of $A_{MLE}$?

**HINT:** Use CLT. Since $A_{MLE} \sim \Gamma(\frac{1}{a}, \frac{1}{na^2})$, then $\sqrt{n}(A_{MLE} - \frac{1}{a}) \sim N(0, \frac{1}{a^2})$

#### Problem 2

**TOPIC:** Joint and marginal distributions of Exponential r.v.s

Let $X_1, X_2, X_3$ be i.i.d. with $f(x) = \frac{1}{\theta} exp(-\frac{1}{\theta}), x > 0, \theta > 0$

Furthermore, define $Y_1 = X_1, Y_2 = X_1 + X_2, Y_3 = X_1 + X_2 + X_3$

a. Determine the joint distribution of $Y_1, Y_2, Y_3$.

**HINT:** This requires calculating the Jacobian which turns out to be

\begin{pmatrix}
1 & 0 & 0 \\
1 & 1 & 0 \\
1 & 1 & 1
\end{pmatrix}

the determinant of which is 1 since we can row reduce this to an identity matrix.

Afterwards, we can just plug in to the original joint pdf (easy since they are all independent) with $X_1 = Y_1, X_2 = Y_2 - Y_1, X_3 = Y_3 - Y_2$.
The final answer should be $\frac{1}{\theta^3}exp(-\frac{y_3}{\theta}), y_3 \geq y_2 \geq y_1 \geq 0$

b. Determine the marginal distribution of $Y_3$

**HINT:** This just involves integrating the joint pdf over $dy_1$ (limits 0 to $y_2$) and $dy_2$ (limits 0 to $y_3$).
The final answer should be $\frac{y_3^2}{2\theta^3}exp(-\frac{y_3}{\theta})$

c. Determine the conditional distribution of $Y_1$ and $Y_2$ given $Y_3 = y_3$.

**HINT:** This just involves employing the definition of conditional distributions so $f_{y_1,y_2,y_3}(y_1, y_2 | y_3) = \frac{f_{y_1,y_2,y_3}(y_1, y_2, y_3)}{f_{y_3}(y_3)} = \frac{2}{y_3^2}, y_3 > y_2 > y_1 > 0$

d. Determine the conditional expectation $E[Y_2 | Y_3 = y_3]$

**HINT:** First we need to get $f_{Y_2 | Y_3}(y_2 | y_3) = \int_0^{y_2} \frac{2}{y_3^2} dy_1 = \frac{2y_2}{y_3^2}, y_3 > y_2 > 0$ and then we calculate the conditional expectation using the new conditional distribution $E[Y_2 | Y_3 = y_3] = \int_0^{y_3} y_2 \frac{2y_2}{y_3^2} dy_2$

e. What does (a), (b), (c) tell you about how you should use these variables to estimate $\theta$?

The only value you need is $y_3$! It is the complete sufficient statistic!

#### Problem 3

**TOPIC:** UMP test for a Rayleigh distribution

$X_1, \ldots, X_n$ be i.i.d. $f(x|\theta) = 2\theta^{-1}x exp(-\frac{x^2}{\theta})I_{x > 0}, \theta > 0$

a. Find the UMP level $\alpha$ test for $H_0: \theta \leq \theta_0$ vs. $H_1: \theta \geq \theta_0$

**HINT:** Similar to previous years. Should find that this is a decreasing function of $\sum X_i^2 \sim \Gamma(n, \theta)$

b. Find an appropriate pivot quantity and use it to construct a two-sided equal tail $(1 - \alpha)100%$ CI for $\theta$.

**HINT:** An appropriate pivot quantity is $\frac{\sum X_i^2}{\theta} \sim \Gamma(n, 1)$

c. Find the maximum likelihood estimator of $\theta$

**HINT:** A little differentiation should show that $\theta_{MLE} = \frac{\sum X_i^2}{n}$

d. Find the likelihood ratio test of asymptotic size $\alpha$ for testing $H_0: \theta = \theta_0$ vs. $H_1: \theta \neq \theta_0$

**HINT:** Should get $\Lambda(X) = \left(\frac{\sum X_i^2}{n \theta_0}\right)^n exp(-\frac{\sum X_i^2}{\theta_0} + n)$. Then take the log of this and multiply by -2 to get your $\chi^2$ statistic.

#### Problem 4

**TOPIC:** Convergence with Normal Distribution

$X_1, \ldots, X_n$ are i.i.d. $N(\mu, 1)$

a. Find the asymptotic distribution of the sample mean $\bar{X}$ as $n \rightarrow \infty$

**HINT:** From CLT, $\sqrt{n}(\bar{X} - \mu) \rightarrow_d N(0, 1)$

b. Use part (a) to perform a large sample test of $H_0: \mu = \mu_0$ vs. $H_1: \mu \neq \mu_0$

**HINT:** They are just asking for a z-test here. Use $Z = \frac{\bar{X} - \mu}{\sqrt{\frac{1}{n}}} \sim N(0, 1)$ under $H_0$

c. Does $\bar{X}^2exp(-\bar{X})$ converge to a limit in probability?

**HINT:** Sure does. By continuous mapping theorem (Mann-Wald), since $\bar{X} \rightarrow_p \mu, \bar{X}^2exp(-\bar{X}) \rightarrow_p \mu^2exp(\mu)$

d. Fina a large sample approximation for the distribution of $\bar{X}exp(-\bar{X})$.

**HINT:** Use the Delta method. Should get that $\sqrt{n}(\bar{X}^2exp(-\bar{X}) - \mu^2exp(-\mu^2)) \rightarrow_d N(0, \mu^2exp(-2\mu)(2-\mu)^2)

#### Problem 5

**TOPIC:** Moment generating functions and Poisson r.v.s

Let A, B, C be independent Poisson r.v.s with mean $\alpha, \beta, \gamma$ respectively.

a. Use MGFs to determine the distribution of X = A + C

**HINT:** $M_X(t) = exp(\alpha(e^t - 1))exp(\gamma(e^t - 1)) = exp((\alpha + \gamma)(e^t -1))$ so $X \sim$ Poisson($\alpha + \gamma$)

b. Let X = A + C, Y = B + C. Find an expression of the correlation between X and Y in terms of the parameters $\alpha, \beta, \gamma$

**HINT:** cor(X, Y) = cor(A + C, B + C) = cor(A, B) + cor(A, C) + cor(C, B) + var(C) = var(C) = $\gamma$

c. Let $\lambda = E[X], \mu = E[Y]$. Suppose that $(X_1, Y_1), \ldots, (X_n, Y_n)$ are a random sample of pairs of counts following the model above. The difference in sample means $\bar{X} - \bar{Y}$ is an unbiased estimator of $\lambda - \mu$.
Find an unbiased estimator of Var($\bar{X} - \bar{Y}$)

**HINT:** Var($\bar{X} - \bar{Y}$) = Var{$\bar{X}$} + Var{$\bar{Y}$} - 2cov($\bar{X}, \bar{Y}$) = $\frac{\alpha + \gamma}{n} + \frac{\beta + \gamma}{n} - 2(\frac{\gamma}{n}) = \frac{\alpha + \beta}{n}$

## COMPS 2004

#### Problem 1

**TOPIC:** MLEs of a Shifted Exponential distribution

$X_1, \ldots, X_n$ be i.i.d. $f(x|\theta) = exp(-(x - \theta)), \theta \leq x < \infty$

a. Write the likelihood function and find the MLE of $\theta$

**HINT:** The MLE is $X_{(1)}$

b. Find the distribution function and the pdf of $\theta_{MLE}$

**HINT:** Using $P(X_{(1)} > x) = \prod P(X_i > x) = exp(-n(x - \theta))$ we find that $F_{X_{(1)}}(x) = 1- exp(-n(x - \theta))$ so $f_{X{(1)}}(x) = n exp(-n(x - \theta)), \theta \leq x < \infty$ or alternatively can use the formula for the pdf of the minimum order statistic.

c. Find $E[\theta_{MLE}]$. Is $\theta_{MLE}$ unbiased for $\theta$

**HINT:** This is easily done since $X_{(1)}$ belongs to a location scale family so $n(X_{1} - \theta) \sim exp(1)$ giving us $E[X_{(1)}] = \frac{1}{n} + \theta$

d. Find a $100(1-\alpha)%$ CI for $\theta$.

**HINT:** Use $n(X_{(1)} - \theta) \sim Exp(1)$ as your pivot!

#### Problem 2

**TOPIC:** Moment generating functions with Chi-squared distribution

Let $X \sim \chi^2_p$ with $f(x|p) = \frac{a}{\Gamma(p/2)2^{p/2}} x^{p/2 - 1} exp(-\frac{x}{2})$ and let $Y \sim \chi^2_q$ and independent of X.

a. Find the MGF of X

**HINT:** This involves using the $\chi^2$ kernel to simplify. 

\begin{align}
M_X(t) &= E[e^{tX}] = \int_{0}^{\infty} e^{tX} \frac{1}{\Gamma(p/2) 2^{p/2}} x^{p/2 - 1} exp(-\frac{x}{2}) dx \\
&= \frac{\Gamma(p/2)( \frac{1}{2} - t)^{-p/2}}{\Gamma{p/2} 2^{p/2}} \int_0^{\infty} \frac{1}{\Gamma(p/2) (1/2 - t)^{-p/2}}x^{p/2 - 1}exp(-(1/2 - t)x)dx \\
&= \frac{1}{(1 - 2t)^{p/2}}, t < \frac{1}{2}
\end{align}

. Show that $X + Y \sim \chi^2_{p+q}$

**HINT:** This is shown easily by $M_{X + Y}(t) = M_X(t)M_Y(t)$

c. Find the density of $\frac{X}{Y}$

**HINT:** Using the fact that $\frac{X/p}{Y/q} \sim F_{p, q}$, let W = $\frac{X}{Y} = \frac{p}{q}F_{p, q} \rightarrow \frac{q}{p}W = F_{p, q}$
Then plugging this in to the pdf of an F distribution which is ugly to begin with, we get some really ugly looking pdf.

d. Does $\frac{X}{p}$ have a limit as $p \rightarrow \infty$?

**HINT:** Sure. Since X is just a sum of p $\chi^2_1$ r.v.s, we can use WLLN to show that $\frac{X}{p} \rightarrow_p 1$

#### Problem 3

**TOPIC:** UMP tests with Poisson r.v.s

X and Y are independent r.v.s where $X \sim Poisson(\lambda)$ and $Y \sim Poisson(\lambda + 1)$

a. Find the test statistic and the most powerful test of $H_0: \lambda = \lambda_0$ vs $H_1: \lambda = \lambda_1$. Give the form of the rejection region.

**HINT:** Finding the ratio shows that our test statistc will be $T = \left( \frac{\lambda_0}{\lambda_1}\right)^x \left( \frac{\lambda_0 + 1}{\lambda_1 + 1}\right)^Y$ and we reject when $T < k$

b. Show that the test in part (a) can be expressed as "Reject $H_0$ iff aX + bY > c".

**HINT:** If you take the log, you find that $ln(T) = X ln(\frac{\lambda_0}{\lambda_1}) + Y ln(\frac{\lambda_0 + 1}{\lambda_1 + 1})$

c. Is there a uniformly most powerful test of $H_0: \lambda = \lambda_0$ vs $H_1: \lambda \neq \lambda_0$?

**HINT:** No, the rejection region for the most powerful test depends on whether $\lambda$ is greater than or less than $\lambda_0$ and you cannot have a single test which has both rejection regions.

d. If $\lambda$ is large, X has an approximately normal distribution. Why?

**HINT:** Use MGFs. $M_{X/\lambda}(t) = E[exp(\frac{xt}{\lambda})] = exp(-\lambda) exp(\lambda exp(t/\lambda)) \sum_{x = 0}^{\infty} \frac{ exp(-\lambda exp(t / \lambda)) (\lambda exp(t/\lambda)^x}{x!}$
The last part is equal to the normal MGF since the infinite summation is equal to 1.
Therefore if $\lambda$ is large, then $\frac{X}{\lambda} \sim N(1, \frac{1}{\lambda}) \rightarrow X \sim N(\lambda, \lambda)$

e. Let $\lambda_0 = 20$ and $\lambda_1 = 30$ and are relatively large. We observe X = 22 and Y = 27. Calculate the p-value of the test from part (a) in the orm of of $\phi(d)$

f. Suppose we observe X = 22 and Y = 27. The MLE of $\lambda$ is 23.96. Consider the LRT of $H_0: \lambda = 20$ vs. $H_1: \lambda \neq 20$. Express the approximate p-vlue of this test in the form of 1 - F(d) where F is the cdf of the $\chi^2$ distribution.

#### Problem 4

**TOPIC:** MLEs, Least Square Estimators, UMVUEs of Poisson r.v.s with different constants

$X_1, \ldots, X_n$ be i.i.d. Poisson with $E[X_i] = \lambda z_i$ where $z_i$ are known constants and $\lambda > 0$ is an unknown parameter.

a. Find the least squares estimate of $\lambda$. Is it unbiased?

**HINT:** Taking the derivative of $\sum (X_i - E[X_i])^2 = \sum X_i^2 - 2\lambda \sum X_i z_i + \lambda^2 \sum z_i^2$ gives us $\hat{\lambda} = \frac{\sum z_i x_i}{\sum z_i^2}$. Taking the expectation of this shows it is unbiased.

b. Is $\hat{\lambda}$ the UMVUE estimator for $\lambda$? 

**HINT:** Since the Poisson pdf belongs to an exponential family, the CSS for $\lambda$ can be shown to be $\sum X_i$ (note that our least squares estimator is *not* a function of this statistic). Taking the expectation of this and correcting it, we can see that $T = \frac{\sum X_i}{\sum z_i}$ is the UMVUE for $\lambda$

c. Show that the UMVUE achieves the CRLB for unbiased estimators of $\lambda$.

**HINT:** We can calulate that the information on $\lambda$ contained in the sample is $\frac{\sum z_i}{\lambda}$. Therefore the CRLB is $\frac{\lambda}{\sum z_i}$. The variance of $\frac{\sum X_i}{\sum z_i}$ is equal to this, so the CRLB is met.

d. Suppose that $z_i = i, i = 1, \ldots, n$. Is $\hat{\lambda}$ a consistent estimator?

**HINT:** We are given that \sum_{i = 1}^n \frac{(n + 1)n}{2} so the variance of $\hat{\lambda}$ is $\frac{2\lambda}{(n+1)n}$ which goes to 0 as $n \rightarrow \infty$. Therefore $\hat{\lambda}$ is consistent.

#### Problem 5

**TOPIC:** P-values

We want to test $H_0$ vs $H_1$. We are able to find the results of 5 studies using the test statistics $T_1, \ldots, T_5$
Assume large $T_i$ indicated support for $H_1$.
Under $H_0$, each $T_i$ has a cdf $F_i$.

a. SHow that the p-value for the ith test $P_i$ has a U(0, 1) distribution under $H_0$.

**HINT:** $P_i = 1 - F_i(T_i) = P_{H_0}(1 - F_i(T_i) < \alpha) = P_{H_0}(T_i > F_i^{-1}(1 - \alpha)) = \alpha$, therefore $P_i$ has a U(0, 1) distribution.

b. Find the distribution of $-\sum_{i = 1}^{5} ln(P_i)$ under $H_0$.

**HINT:** Let $Y_i = -ln(P_i) \sim exp(1)$ so $\sum_{i = 1}^5 Y_i \sim \Gamma(5, 1)$

c. How might $-\sum_{i = 1}^{5} ln(P_i)$ be used to test $H_0$ vs $H_1$?

**HINT:** Use $\Gamma(5, 1)$ as a reference distribution for the test statistc $T = -ln(\sum ln(p_i))$

d. Suppose that the researcher is able to locate the results of n studies and calculate the p-value from each study as above. Suppose $n \rightarrow \infty$. How might $-\sum ln(p_i)$ be used to test $H_0$ vs $H_1$ using the large sample property?

**HINT:** By CLT, $\sqrt{n} (\frac{- \sum^n ln(P_i)}{n} - 1) \rightarrow_d N(0, 1)$

## COMPS 2005

#### Problem 1

**TOPIC:** Properties of Standard Normal and Function of Standard Normal r.v.s

$Z_1, Z_2$ are i.i.d. N(0, 1) r.v.s and define $Y_1 = Z_1 + Z_2, Y_2 = Z_2, W = exp(Y_1)$

a. Find $E[Y_1]$, Var[$Y_1$], cov($Y_1, Y_2$)

**HINT:** E[$Y_1$] = 0, Var[$Y_1$] = 1 + 1 = 2, cov($Y_1, Y_2$) = Var($Z_2$) = 1

b. Find the marginal density of $Y_1$

**HINT:** Uh well its the sum of two standard normals so $Y_1 \sim N(0, 2)$

c. Find the joint density function of $Y_1, Y_2$.

**HINT:** $Y_1 = Z_1 + Z_2, Y_2 = Z_2 \rightarrow Z_1 = Y_1 - Y_2, Z_2 - Y_2$. The Jacobian matrix for this is 

\begin{pmatrix}
1 & -1 \\
0 & 1
\end{pmatrix}

Plugging all of this into the original joint distribution function, we get $f_{Y_1, Y_2}(y_1, y_2) = \frac{1}{2\pi} exp(- \frac{(y_1 - y_2)^2 + y_2^2}{2})$

d. Find the density function of W.

**HINT:** Plugging into the formula for a univariate transformation, we should get that $f_w(w) = \frac{1}{w} \frac{1}{\sqrt{4\pi}} exp(- \frac{ln(w)^2}{4})$

e. Find E[W] and Var[W]

**HINT:** Use MGFs. $M_{Y_1}(t) = E[e^{Y_1 t}] = e^{t^2}$ so $E[W] = e$ and $Var[W] = E[e^{2Y_1}] - (E[e^{Y_1}])^2 = e^4 - e^2$

#### Problem 2

**TOPIC:** Inequalities

Let $\bar{X}_1$ and $\bar{X}_2$ be the sample means of two indpendent samples of size n from the same population with mean $\mu$ and variance $\sigma^2$.

a. Use the CLT to determine n s.t. the probability is about .01 that the two sample means will differ by more than $\sigma$

**HINT:**
\begin{align}
P(\bar{X}_1 - \bar{X}_2 > \sigma) = .01 \rightarrow P(\frac{\bar{X}_1 - \bar{X}_2}{\sigma} > 1) = .01 \rightarrow P(\frac{\bar{X}_1 - \bar{X}_2}{\sqrt{\frac{2\sigma^2}{n}}} > \sqrt{\frac{n}{2\sigma^2}}) = .01
\end{align}

b. Use Chebyshev's Inequality to determine n s.t. that probability that the means differ by more than $\sigma$ is no greater than .01

**HINT:** Let Y = $\bar{X}_1 - \bar{X}_2$. Then $P(Y^2 \geq \sigma^2) \leq \frac{E[Y^2]}{\sigma^2} = \frac{2\sigma^2 / n}{\sigma^2} = \frac{2}{n} = .01$

#### Problem 3

**TOPIC:** UMVUEs, MLEs with for Normal r.v.s with different variances

Let $X_1, \ldots, X_n$ be i.i.d. with $X_i \sim N(\theta, \frac{\sigma^2}{\lambda_i})$ where $\lambda_i$ are known positive numbers and $\theta, \sigma^2$ are unknown.

a. Find a CSS for ($\theta, \sigma^2$)

**HINT:** Putting the pdf into exponential family form, we see that the CSS is $T = (\sum X_i, \sum X_i^2)$.

b. Find the UMVUE of $\theta$

**HINT:** $E[\sum X_i] = n\theta$ so $W = frac{\sum X_i}{n}$ is the UMVUE of $\theta$

c. Give a sufficient condition in terms of the $\lambda_i$ for the consistency of the estimator.

**HINT:** We need the variance of our UMVUE to converge to 0. Doing the math, we see that $\frac{\sum \frac{1}{\lambda_i}}{n^2} \rightarrow 0$ is the necessary condition.

d. Find the MLE of $\sigma^2$

**HINT:** Differentiating the log-likelihood gives us $\hat{\sigma^2} = \frac{\sum \lambda_i(x_i - \theta)^2}{n}$.

#### Problem 4

**TOPIC:** Large sample Asymptotic tests with Bernoulli r.v.s

Let $X_1, \ldots, X_n$ be i.i.d. Bernoulli(p) r.v.s where 0 < p < 1 is the unknown parameter. Find the following three asymptotic tests for testing $H_0: p = 0.5$ vs $H_1: p \neq 0.5$

a. Asymptotic likelihood ratio test

**HINT:** $\Lambda(p = .5) = -2n ln(2) + ln(\bar{X})(\sum X_i) + ln(1 - \bar{X})(n - \sum X_i) \sim \chi^2_1$

b. Asymptotic Wald Test

**HINT:** $W(p_0) = \frac{(p_{MLE} - p_0)^2}{1 / I_{X}(p_{MLE})} = \frac{n(\bar{X} - .5)^2}{\bar{X}(1 - \bar{X})} \sim \chi_1^2$

c. Asymptotic Score Test

**HINT:** $S(p_0) = \frac{U(p_0)^2}{I_{X}(p_0)} = \frac{(4\sum X_i - 2n)^2}{4n} \sim \chi^2_1$

#### Problem 5

**TOPIC:** UMP tests for Gamma r.v.s

$Y_1, \ldots, Y_n$ are i.i.d. observations from $f(y|\theta) = 2\theta \sqrt{\frac{\theta}{\pi}} \sqrt{y} exp(-\theta y), y > 0$

a. Derive a UMP test at level $\alpha$ of $H_0: \theta \leq 1$ vs $H_1: \theta > 1$

**HINT:** You can see that the monotone likelihood ratio here is increasing w.r.t. $\sum y_i$

b. Express the critical value k in tersm of a critical value from a known distribution

**HINT:** Since $Y_i \sim \Gamma(\frac{3}{2}, \frac{1}{\theta})$, $\sum Y_i \sim \Gamma(\frac{3n}{2}, \frac{1}{\theta})$

c. Describe how to calculate the power of the test in part (a) against the alternative $\theta = 2$

**HINT:** $P_{\theta=2}(\sum y_i < F^{-1}_{\Gamma(3n/2, 1/2)}(\alpha))$

e. Find a function of T that is a pivot

**HINT:** $\theta \sum y_i \sim \Gamma(\frac{3n}{2}, 1)$

d. Use the pivot to derive a two sided confidence interval for $\theta$

## COMPS 2006

#### Problem 1

**TOPIC:** Basic Properties of Probability Distributions

Consider $f(x) = cx^2, 0 < x< 1$ where c is some constant

a. Find the value of c

**HINT:** c = 3

b. Find the mean of the distribution

**HINT:** $E[X] = \frac{3}{4}$

c. Suppose $X_1, X_2$ are independent observations from the distribution. Let Y = min($X_1, X_2$). Find $P(Y \leq .5)$

**HINT:** $P(Y \leq .5) = 1 - P(X_1 > y)P(X_2 > y) = 1 - (1 - .5^3)^2 = .234$

d. Find E[Y]

**HINT:** $f_y(y) = 6y^2 - 6y^5$ so $E[Y] = \frac{9}{14}$

e. Which is bigger, the mean of Y or the median of Y?

**HINT:** Just plug the mean into the CDF of Y

f. Let $Z = exp(X)$ where $X \sim f(x)$. Find the density of Z.

**HINT:** $f_z(z) = \frac{1}{z}3(ln(z))^2, -\infty < z < 0$

g. Is E[Z] smaller than, equal to, or bigger than 2.117?

**HINT:** Use Jensen's inequality. Since the exponential function is convex, $E[exp(X)] \geq exp(E[X]) = 2.117$

#### Problem 2

**TOPIC:** Tests on the Normal Distribution

$X_1, \ldots X_n \sim N(\mu_0, \sigma)$

a. Derive the LRT for testing $H_0: \sigma = \sigma_0$ vs $H_1: \sigma \neq \sigma_0$

b. Describe the asymptotic null distribution of the test statistic in part (a).

c. Suppose n = 20, $\sum X_i = 588$, $\sum X_i^2 = 17700, \mu_0 = 30, H_0: \sigma = 3, H_1: \sigma \neq 3$

d. Specify the exact distribution of the MLE of $\sigma$

**HINT:** $\frac{\sigma^2}{n} \sum \left( \frac{X_i - \mu_0}{\sigma}\right)^2 \sim \frac{\sigma^2}{n} \chi^2_n$

e. Use the distribution in (d) to obtain the test of $\sigma = \sigma_0$ vs $\sigma \neq \sigma_0$

#### Problem 3

Didn't do this one.

#### Problem 4

Didn't do this one.

#### Problem 5

**TOPIC:** Word Problem about Flowers!

There are 40 red flowers. Red flowers can have either an RR or RW genotype. Let $\theta$ be the proportion of RR red-flowered plants.

Our experiment is to have the 40 red flowers produce 2 offspring flowers apiece.
For a RW parent, 50% of their offspring will be red and 50% will be white.

a. If one red flower is collected at random, what is the probability that both offspring plants are red flowers.

**HINT:** P(both red) = P(both red | RR)P(RR) + P(both red | RW)P(RW) = $\theta + \frac{1}{2} \frac{1}{2}(1 - \theta)$

b. What is the expted number of red flower offpsring in part (a)?

**HINT:** $E[X_i] = 0 + 1\frac{1}{2}(1 - \theta) + 2(\frac{1}{4} + \frac{3}{4}\theta) = 1 + \theta$

c. Use MOM to obtain estimator of $\theta$. Express as a function of $Y_0, Y_1, Y_2$ where $Y_j$ is the number of plants that produced j red flowered plants.

**HINT:** Solve $1 + \theta = \frac{Y_1 + 2Y_2}{40}$ for the MOM estimator.

d. Is your MOM unbiased?

**HINT:** Yep.

## COMPS 2007

#### Problem 1

**TOPIC:** MLEs and MSE for weird exponential family

$X_1, \ldots, X_n$ be i.i.d. $f(x|\theta) = \frac{4x^3}{\theta^2}, 0 < c < \sqrt{\theta}$

a. Find the MLE of $\theta$

**HINT:** $\theta_{MLE} = (X_{(n)})^2$

b. Show the bias of the MLE is $-\frac{\theta}{2n + 1}$

**HINT:** $E[X_{(n)}^2] = \int_0^{\sqrt{\theta}} x^2 \frac{4n}{\theta^{2n}} x^{4n-1} dx = \frac{2n}{2n+1}\theta$

c. Find an unbiased estimator of $\theta$ that is based on the MLE.

d. Show the MSE of the estimator in (c) is $\frac{\theta^2}{4n(n+1)}$

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2008

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2009

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2010

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2010

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2011

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2012

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2013

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2014

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2015

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2016

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2017

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

## COMPS 2018

#### Problem 1

#### Problem 2

#### Problem 3

#### Problem 4

#### Problem 5

 2000 Q1: $\lambda$ is chosen from a distribution with density $f(t) = e^{-t} \text{ where } 0 < t < \infty$. Let N be a Poisson random variable with parameter $\lambda$.

 2000 1a. Find the unconditional probabilities $P[N = x]$ for $x = 0, 1, 2, \ldots$.

 2000 1b. Find the unconditional expected value of $N$

 2000 1c. Is the unconditional variance of N less than 1, equal to 1, or greater than 1? Why?

 2000 Q2: Suppose that $X_1, \ldots, X_n$ is i.i.d. with pdf

$$
f(x | \alpha, \beta) =
\begin{cases}
\frac{1}{\beta} exp\left( -\frac{x-\alpha}{\beta} \right) & \text{ for } x > \alpha \\
0 & \text{ o.w. }
\end{cases}
$$

 2000 2a. Find a two-dimensional sufficient statistic for $(\alpha, \beta)$. Provide justiciation for your answer here as well as in all subsequent parts.

 2000 2b. Find the MLEs for $\alpha$ and $\beta$

 2000 2c. Find a minimal sufficient statistic for $\beta$

 2000 2d. Find the UMVUE for $\beta$

 2000 2e. Find the UMVUE for $\beta^2$

 2000 Q3: A component has an exponential lifetime with an expected life of 10 years. A unit consists of 4 identical, independent components.

 2000 3a. A unit has 4 components "in series" if the failure of any single component makes the unit fail. What is the distribution of the units lifetime if the unit has its components in series?

 2000 3b. What is the units expected lifetime if the unit has its components in series?

 2000 3c. A unit has 4 components "in parallel" if the unit fails only if all the components fail. What is the distribution of the units lifetime if the unit has its components in parallel?

 2000 3d. What is the unit's expected lifetime if the unit has its components in parallel?

 2000 Q4: Let $X_1, \ldots, X_n$ be i.i.d. $f(x | \theta) = \theta x^{\theta - 1}$ for $0 < x < 1$ and some $\theta > 0$. Let $W = -ln \left(\prod_{i=1}^n X_i \right)$

 2000 4a. Find the UMP of size $\alpha$ test for testing $H_0: \theta = 1$ vs. $H_1: \theta > 1$

 2000 4b. Find the MLE of $\theta$.

 2000 4c. Find the LRT for testing $H_0: \theta = 1$ vs. $H_1: \theta \neq 1$. Show that it rejects if $W$ is too large or too small.

 2000 4d. Find a $1 - \alpha$ CI based on the LRT in part (c). Specifically, find constraints which would define the lower bound and upper bound of the interval.

 2000 Q5: Suppose that $X_1, \ldots, X_n$ is a random sample of independent observations from a $N(\mu, \sigma^2)$ distribution where $\mu$ and $\sigma^2$ are unknown parameters.

 2000 5a. What is the distribution of $\bar{X}$?

 2000 5b. What is the distribution of $S^2$?

 2000 5c. Is the correlation between $\bar{X}$ and $S$ positive, negative, or 0?

 2000 5d. Suppose that $Y_1, \ldots, Y_n$ is a random sample of m independent observations from a $N(0, \sigma^2)$ distribution where $\sigma^2$ is the same unknown parameter as above. Using only the $Y$'s, find an unbiased estimator of $\sigma^2$ with variance $\frac{2\sigma^4}{m}$

 2000 5e. Let $\mu_0$ be a hypothesized value for $\mu$. Suppose the sample of $X$'s and the sample of $Y$'s are independent of one another. Using both samples, construct a test statistic $T$ whose distribution when $\mu = \mu_0$ is a t-distribution with $n+m-1$ degrees of freedom.

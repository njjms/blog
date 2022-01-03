---
layout: post
title: "Common misinterpretations of frequentist statistics"
date:   2022-01-01 15:08:28 +0000
categories: statistics
---

# "Required reading for statisticians and data scientists"

This paper [*Greenland et al.*](https://link.springer.com/article/10.1007/s10654-016-0149-3#Abs1) has been floating around for the last few years on Reddit, LinkedIn, etc. with such titles as "mandatory reading" and "the most important paper for burgeoning statisticians".
Naturally, I'm just getting around to reading it.
What better way to start off the new year than with playing some catch up :)

The paper details 25 common misinterpretations associated with Null Hypothesis Significance Testing, e.g. p-values, confidence intervals, and power calculations.
I'll list them all out here and we can see how many of these I'm guilty of.

# The List

Note that the paper makes use of the terminology "test hypothesis" to refer to what is commonly called the null hypothesis in introductory statistical textbooks and "size" in reference to the effect or association of a specific treatment.

1. The P value is the probability that the test hypothesis is true

I think anyone who has taken Stats 101 should know this is incorrect, but I have actually heard this in job interviews before so there is good reason this is number 1 on this list.
Frequentist P values are *not* hypothesis probabilities.
There's a reason why people are advocating Bayesian frameworks!

2. The P value for the null hypothesis is the probability that chance alone produced the observed association

I have heard this one too.
Greenland et al. claims this is just a restatement of number 1.
I personally think it's an ambiguous statement and doesn't get at the actual definition of a P value.
The P value is a probability calculated assuming every assumption of the statistical test and the null hypothesis is true.
If that's your definition of "chance alone", just say that instead.
It's way more clear.

3. A significant test result (P $\leq$ .05) means that the test hypothesis is false or should be rejected.

A small P value simply flags the data as being unusual if all the assumptions used to compute it, including the null hypothesis, are correct.
There is no differentiation from which of these assumptions are incorrect, based solely on the p-value. 

4. A nonsignificant test result (P > .05) means that the test hypothesis is true or should be respected.

Important point here: the same data we observed would not be unusual under many other hypotheses, not just our chosen null hypothesis.
This is why NHST doesn't *prove* a null hypothesis.

5. A large P value is evidence in favor of the test hypothesis.

Technically, any P value less than 1 implies that the null hypothesis is not the hypothesis most compatible with the data, since ostenisibly there exists infinite hypotheses with P value equal to 1 that we did not select.

6. A null hypothesis P value greater than .05 means that no efect was observed, or that absence of an effect was shown or demonstrated.

Wrong for the same reason as 4.

7. Statistical signficance indicates a scientifically or substantively important relation has been detected.

When a study is large, even minor effects or small assumption violations can lead to significant test results of the null hypothesis.

8. Lack of statistical signficance indicates that the effect size is small.

When a study is small, even large effects might get drowned out by noise.
Looking at the confidence interval to determine plausible ranges for the effect size needs to be examined.

9. The P value is the chance of our data occurring if the test hypothesis is true

Stats 101.
The P value refers to observations *at least as extreme* as what we observed in our study, experiment, etc.

10. If you reject the test hypothesis because P $\leq$ .05, the chance you are in error is 5\%.

The 5\% refers to how often you incorrectly reject the test over many uses of the test across different studies.

11. P = .05 and P $\leq$ .05 mean the same thing.

I didn't even know people though this.

12. P values are properly reported as inequalities (e.g. report P > .05 when P = .06 or P = .70)

??? What??? No.

13. Statistical significance is a property of the phenomenon being studied, and thus statistical tests detect significance. 

Statistical significance is a dichotomous description of a P value and is therefore a property of the statistical test with some arbitrarily chosen cut off.

14. One should always use two-sided P values.

No.

15. When the same hypothesis is tested in different studies and none or a minority are statistically significant, the overall evidence supports the hypothesis.

If there were five studies all with borderline evidence, I think any reasonable person would say that there is more investigation to be done.

16. When the same hypothesis is tested in two different populations and the resulting P values are on the opposite sides of .05, the results are conflicting.

Statistical tests are sensitive to many differences between study populations that are irrelevant to whether their results are in agreement, such as the size of the compared groups.
Two studies may provide very different P values for the same test hypothesis and yet be in perfect agreement.

17. When the same hypothesis is tested in two different populations and the same P values are obtained, the results are in agreement.

Tests are sensitive to many differences between populations that are irrelevant to whether their results are in agreement.

18. If one observes a small P value, there is a good chance that the next study will produce a P value at least as small for the same hypothesis.

I don't even know where this comes from.
If the null hypothesis is correct and you run the experiement again, the chance you will observe a P value smaller than your first is equal to your P value since P values should be uniformly distributed when your null hypothesis is true.

19. The 95\% confidence interval presented by a study has a 95\% chance of containing the true effect size

Another Stats 101 misconception.
A confidence interval either contains the true effect or it doesn't.

20. An effect size outside the 95\% confidence interval has been refuted (or excluded) by the data

A confidence interval is computed from many assumptions, the violation of which may have led to this final confidence interval.

21. If two confidence intervals overlap, the difference between two estimates or studies is not significant

No, and I have personally seen counterexamples of this where the CIs overlap and the P value between the groups is small.

22. An observed 95\% confidence interval predicts that 95\% of the estimates from future studies will fall inside the observed interval.

Again a confidence interval is a statement on other unobserved confidence intervals, not on future observations.

23. If one 95\% confidence interval includes the null value and another excludes that value, the interval excluding the null is the more precise one.

Precision of statistical estimation is measured directly by confidence interval width.

24. If you accept the null hypothesis because the null P value exceeds .05 and the power of your test is 90\%, the chance you are in error is 10\%.

The 10\% refers only to how often you would be in error over very many uses of the test across different studies.

25. If the null P value exceeds .05 and the power of this test is 90\% at an alternative, the results support the null over the alternative.

This is not a given - it's possible to come up with counterexamples where this is not true.

# Final Score

Thankfully, I have never claimed any of the above in a professional setting (am I real statistician now?).
That being said, I have definitely thought some of these things at some point and have heard others in our field state something similar.

Required reading indeed.

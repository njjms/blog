---
layout: page
title: Research
permalink: /research/
---

<center>
	<p><h4>A haiku on a seminal geostatistical textbook</h4></p>
	<p>
	<i>
	A comprehensive <br />
	Incomprehensible work<br />
	Cressie 93<br />
	</i>
	</p>
</center>

# Hol' up... I finished!

My advisor just cleared the penultimate draft of my Masters report, with only some minor edits.
It's sad actually, working on this project was one of the only things keeping me sane during lockdown.
I'm quite fond of it now.

You can find the paper [here](/assets/sunn_ms_report.pdf) and the code used is on my [Github](https://github.com/njjms/MS).

# Introduction

From April-June 2020 I will be working on a project for my MSc.
This page is intended to be running document and central repository for all resources and notes related to that project.

My project is about comparing different methods in **small area estimation** with zero-inflated data.

# Literature Reviews

<div id="research">
	{% for post in site.categories.research %}
	<p></p>
	<a href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a>
	<p></p>
	{% else %}
		No posts found.
	{% endfor %}
</div>

# Why is this in the docs???

Hengl uses `GSIF::buffer.dist()` to compute the Euclidean distance between points to use in the spatial random forests.
The issue is that for some reason I need to convert my points from a `SpatialPointsDataFrame` to a `SpatialPixelsDataFrame`, and this would throw errors often since the points are not regularly spaced.
The results would be that I would have to keep randomly splitting my datasets until I got a partition that worked which is **super gross** to me.
Running the spatial random forest would take like a whole minute, which compared to kriging and copula was **astronomically** high.

The fix? Use `raster::pointDistances` instead. **Much** faster -- not it takes a second or so to train a random forest, about the same as the kriging and copula models.
Weird thing is that the distances calculated are slightly different than the ones returned by `buffer.dist()` but the documentation is quite hazy as to why this would be.

# Some fun errors

+ 5/7 Ran into this pretty boy today when running universal kriging using `automap` package:

```
 Error in vgm_list[[which.min(SSerr_list)]] : 
  attempt to select less than one element in get1index 
```

If you look at the semivariogram, the semivariance actually decreases with variance! Crazy...
Hiemstra has the following suggestion ![here](https://stackoverflow.com/questions/41941010/r-error-with-autofitvariogram-automap-package) but this doesn't seem to apply to me since I have 300 valeus in my training set.

Only way I can think of reasonably handling this error within my framework simulation is a `tryCatch` call with the following:

{% highlight R %}
uk_preds <- tryCatch({
        suppressWarnings({
            uk_preds <- autoKrige(resp ~ annpre, training_data.cpy, test_data.cpy)$krige_output$var1.pred
            return(uk_preds)
        })
    }, error = function(e){
        print(e)
        uk_preds <- rep(0, nrow(tmp$test))
        return(uk_preds)
    })
{% endhighlight %}

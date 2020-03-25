---
layout: post
title: "Analyzing Reddit Comments with GCP and Spark"
date: 2020-03-09 010:07:28 +0000
categories: cs
---

This quarter I signed up for a class called "Data Science Tools and Programming".
Thus far, the class has only been marginally useful -- a lot of the topics are pretty beginner oriented (not that I'm a pro or anything, but I know enough Python and SQL to get by).
For the final project though, we get to kind of cut loose and pick a topic that we are interested in, then try to answer questions we picked using tools we covered in class, namely Google Cloud Platform and Spark.

For my final project, I found a great repository of reddit comment and post information (courtesy of Jason at `pushshift.io`) that I decided to tackle in a VM instance.
I will be taking a month's worth of Reddit comments and answering the following questions:

+ What are the most active subreddits?
+ Where should a redditor spend the most time if they want to maximize karma?
+ Which subreddits are the most controversial?

This was my second real exposure to GCP, so I still have a lot to learn.
The platform is broken into many different tools which perform different stages of the data analysis, from ingestion to storage to prep to analysis.
The workflow that we used was this:

1. Create a VM instance with sufficient disk storage to hold the unzipped json files
2. Copy those json files from the instance to a Google Cloud Storage bucket.
3. Prep the data using Dataprep
4. Load the cleaned data into Google BigQuery to run a SQL

## Creating a VM Instance and Getting the Data

Creating the GCP instance is pretty straightforward using the GCP console!
As a student, I got $300 in free credits, which I naturally burned through pretty quickly throughout the term by leaving things on when I didn't have to.

As of starting this final, I have $140 left which adds an element of *drama* and *~suspense~* to this final.
What's a data science assignment without some budgetary restrictions??

Now we can download the 15GB zipped file.
I chose to download the most recent month available in September of 2019.

```
wget http://files.pushshift.io/reddit/comments/RC_2019-09.zst
```

A .zst file is a zip file in the Zstandard compression program (thanks Facebook).
In order to get at the goodness inside, we will have to download `zstd`.

Thankfully, this is pretty easy on an Ubuntu/Debian Instance.

```
sudo apt-get update
sudo apt-get install zstd

unzstd RC_2019-09.zst
```

The .zst file uncompressed is pretty huge!
I had to try this part a few times with different instance disk sizes before I got it to work.
Eventually, I found that creating an instance with a 200GB disk was enough.
When unzipped, the file was 168GB.

One useful thing I learned is that the `unzip` utility can actually output the uncompressed size of a zipped file using the `-l` flag.

```
unzip -l yourzipfile.zip
```

## Copying over to a GCS bucket

This part is pretty easy, but as you can imagine, pretty time-consuming.
Essentially, GCP requires that we use a storage bucket as a staging area to hold data that we'll analyze later with BigQuery and Spark.

I created a bucket using the **Storage** tab of the GCP console called `cs512-reddit`.
I can then copy over the big 168GB to this bucket using `gsutil`.

```
gsutil -m cp RC_2019-09 gs://cs512-reddit
```

Remembering the `-m` flag is important for huge files since this parallelizes the operation.
Additionally, if my file was instead a bunch of **separate files**, I would have to make sure that I moved these files into a single directory and then call `cp` on the directory.
This is because to load the data into later tools, we need to check individual files and there is no handy `select all` type button.
It is almost impossible to change files once they are in storage, so we need to do this in the instance before we move it into the bucket.

For me, copying this over on an instance with 2 cores and 8GB of RAM takes over an hour.

## Dataprep

TODO

## BigQuery!

TODO

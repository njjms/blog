---
layout: post
title:  "Setting up a blog with Jekyll and Ubuntu (for non-engineers)"
date:   2018-12-14 23:07:28 +0000
categories: linux
---

Having completed my first quarter of graduate school, I've met some really fascinating and brilliant people.
 I consider myself lucky to be associated with some really genuine individuals -- both students and faculty -- who care about what they do.

Statisticians by nature I think often tread a line between theory and application.
In my cohort, everyone has a really strong background in math (even if they are too humble to admit it!) and everyone has had at least some exposure to computer science.
 That being said, people come in with different levels of programming experience.
One thing that some folks have asked me about though is how to set up a blog.

## I am not an expert

As a caveat, I am nowhere near a software engineer, nor do I really desire to be.
There's a reason I joined a statistics department.
I have had some prior interactions with some terrific software engineers who taught me a lot, although when I say that keep in mind that that's a relative measure. 
I was starting at level 0 and they brought me up to level 2. That being said, you can still set up a website in a few hours with the right tutorials!

## Why have a website?

Honestly, I made this website mostly so I can talk about projects I am working on.
Might be a good idea if you're planning to go into industry!
Some other reasons which I think are relevant to grad students:

+ It is pretty darn fun. Taking a break from watching anime and doing other quasi-nerd stuff is good for you. For the purposes of this sentence, I count Bojack as anime.
+ Despite what you might think sometimes, you are an interesting individual and your thoughts are worth sharing! Having a twitter is nice, but having a medium to share longer, more thought out articles is sometimes better.
+ Once you know how to do it once, you can do it *ad infinitum*. I have a couple of joke sites for very niche topics that I like to show friends and family. I will definitely do more, contributing in some small part to the beautiful turd salad that is the internet.

## Couple different ways to do this

I think a lot of folks use a service like Wix (i.e. "I just made this **dope** website with WIX *lip bite*") or Weebly (which for the record I think is a hilarious name for a company).
Totally nothing wrong with that. 
I've never done it because I think those sites look too polished, but I'm sure it's more or less straightforward.
I wanted my websites to have more of a campy, geocities (i.e. **bad**) vibe.

## Flask

This is how I made my first website. It was perfect aesthetics-wise, it was a shitty static site with bare HTML and a dash of CSS and light dusting of early 90s gifs.
You can host it on something like Heroku, which is what I did. Heroku is pretty straightforward, I have nothing against the company.
For a beginner like me, they did quite a bit of handholding and it was much appreciated.
However, the steps for logging into Heroku (I used their CLI) and then pushing your code changes was kind of hard to remember.
So I decided to try something that was even more straightforward in my opion.

## Jekyll on a VPS

This is what I'm using right now for this very site. For those who aren't aware
**Jekyll** is tool for making static sites (aka sites that basically just dump some formatted HTML in your browser).
It uses Ruby, but you don't really need to know Ruby to get started, the tutorial on the Jekyll website really holds your hand. 
I can say that as a fact, because I don't know Ruby but I made this website today in a few hours.

You will need a few things:

+ A virtual private server (VPS). I personally use Vultr since I think it is the cheapest, but Digitalocean I'm sure is just as valid.
+ Jekyll. The tutorial is all you really need to get started! 
+ A web server, I am currently using nginx

Naturally, you will need to have some familiarity with the command line to get all this working!
You will also need some familiarity with Markdown and also preferably HTML/CSS etc. but to just get content up without worrying about formatting, the latter is optional.

*Note:* you can also use Github Pages which also uses Jekyll but I like having my own VPS.

The tutorial instructs you to use `bundle` which makes things pretty easy.
You build your jekyll site using `bundle exec jekyll build` which creates a `_site` directory.

Since I am using nginx, the only thing to keep in mind during configuration is changing the directory with all the files.
By default, nginx is pointed at `/var/www/html` and we want to instead point it towards our new `_site` directory.
All we have to do is `sudo vim /etc/nginx/site-enabled/default` and change the line `root /var/www/html;` to `root /path/to/_site;`.

Once you have all this stuff set up, you can start writing blog posts right out of the gate!
By default, the blog posts are in the `_posts` directory.
There should already be an example post in there which you can copy.

Once you have built your jekyll site using `bundle` all that's left to do is restart nginx, which you can do using `sudo nginx -s reload`!

Now all you have to really worry about is getting a cool domain name.
I purchased mine from `namecheap` and then configured the advanced DNS options to point to the IP address of my VPS.


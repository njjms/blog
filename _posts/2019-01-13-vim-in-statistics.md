---
layout: post
title:  "Using Vim as a statistician"
date:   2019-01-13 07:07:28 +0000
categories: vim
---

I was introduced to Vim about a year and a half ago by one of the engineers I used to work with.
I was pretty fascinated by the idea of an editor that was notorious for turning people off and for a while, I used it solely to be an elitist hipster.

Once I actually started to learn more about it, I realized as many have before me that Vim is actually an amazing tool.
There's a reason that it continues to consistently by one of the top editors and now it's hard for me to NOT use it.
I can't count the number of times that I have left a stray `:w` in a Word document.
Nowadays, my text processing consists almost exclusively of Vim, Markdown, pandoc, and occasionally Overleaf.

I won't really write about Vim's features, but I did want to write about when it might be useful to know Vim as a statistician.
From my experience, statistics folks are pretty immune from editor/IDE wars; if you use R, you use Rstudio.
If you use Python, you use Jupyter (maybe Spyder or Pycharm).
I guess you could use RStudio as well since it supports Python, but I don't know of anyone personally who actually does that.
I think this actually a detriment: not only do a lot of folks get deprived of of the fun of exploring new editors, they also don't get to try new workflows.
Who knows if there's a more efficient way to do your work out there waiting for you?

In fact, recently I found that RStudio has a Vim mode built into it.
It's a bit limited - notably you can't configure anything like you would in your standard `.vimrc` file, but all the essential ingredients are there: macros, marks, dot commands, and registers.
While in Vim mode, RStudio shortcuts for the most part still work, so for example you can still use `Alt+-` to make a `<-` operator.

**awk**, **sed**, and regular bash scripting are great tools to have at your disposal as a statistician -- you don't have to be an expert at them, but there may very well be situations where your data is given to you as plaintext (FASTA output immediately comes to mind) and you need a swiss army knife to massage it and pull usable information out.
Not only will you need a command line text editor to be really efficient, but Bash actually has a built in Vim mode that for me has really streamlined typing in shell commands.

If you put this in your `.bashrc`: **set -o vi**

You will automatically open up in Vim mode as soon as Bash starts.
Now as your typing commands and realize you messed up somewhere, you can exit "Insert mode" in your terminal using `<Esc>` and move around the text you have typed out.
I can't tell you how much time I have saved by avoiding have to arrow key through my lines at the command prompt!
The only caveat is that I instinctively hit `CTRL-C` when I'm in insert mode, which cancels what you are doing in the terminal.

Finally, if you want to do any kind of sysadmin/server stuff or doing any work on a remote server, having knowledge of a command line text editor is essential.
Since we're statisticians, this usually won't be necessary BUT if you wanted to do something like maintaining your own website on a virtual private server, Vim might be a **really** helpful skill to pickup!


---
layout: post
title: "Setting up conda environments with tmux on macOS"
date:   2020-10-07 23:07:28 +0000
categories: [linux]
---

<center>
<img src="/assets/tmux_macos.png">
</center>

# What is tmux?

I have been using the tmux program (short for **terminal multiplexer**) for a few years now, but relatively recently moved to using it as my primary IDE for both R and Python using the vim-slime plugin ([see here](https://github.com/jpalardy/vim-slime)).
 In a sentence, tmux makes it easy to have multiple terminals running at once.
It's a lot like GNU screen, but in my opinion it is easier to learn out of the box as well as easily customizable by editing  `~/.tmux.conf` like you would for any other common Linux tool.

In short, my workflow is opening tmux from whatever terminal you are using.
Then I create two split horizontal panes; the top is to write code, the bottom is to run code in a REPL.
The nice thing about this set up is that it is language agnostic.
All I have to do is start a REPL in a tmux pane - it can be R, Python, Julia, Lisp (idk who programs in LISP but apparently that is where slime comes from), etc.
The only thing vim-slime is doing is sending text from one tmux pane to another.
This way, I can have a consistent IDE across all languages instead of jumping from RStudio to Pycharm or whatever.
Really simplifies working imo!

# The problem?

The problem is that my company gave me a macbook to work on!

The tricky part here which I didn't have to contend with on my personal laptop (which runs WSL) is that conda environments don't seem to work by default in tmux on macOS.
You can activate your environments without any errors, but when you actually run Python, it will be the base version instead of whatever conda version you wanted.
From digging around, this appears to be some kind of issue with `$PATH` variable getting overwritten when tmux starts up so that which python returns `/usr/bin/python` instead of whatever conda environment you want (by default in August 2020, it seems that `/usr/bin/python` is still Python 2.7 - even if you didn't know it before, I'm sure you'll notice right away that your conda env isn't working).

I had to make the following changes to my `.bash_profile`:

If you're like me and already have a .bashrc from Github or whatever, you are going to want to include source `~/.bashrc` somewhere in here
Include the following chunk:

```
if [ -f /etc/profile ]; then
    PATH=""
    source /etc/profile
fi
```

Every time you open a new tmux pane, this sources your `/etc/profile` again so that your $PATH doesn't get weirdly messed up.

Also include this chunk:

```
if [ -z ${TMUX+x} ]; then
    conda deactivate && conda activate base
fi

```

When the `$TMUX` variable is nonempty, this automatically runs what is inside the if statement. Honestly, I'm not entirely sure why this line is necessary, but without it, conda environments still don't seem to register.

Once you have all this setup and you source `~/.bash_profile`, you should now be able to activate conda environments in your tmux session.



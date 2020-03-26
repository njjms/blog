---
layout: post
title: "Spring cleaning my .vimrc"
date: 2019-02-20 07:06:22 +0000
categories: vim
---

For a while, I've been thinking about slimming down my .vimrc, in part because I read a thought-provoking post on Reddit about relying less on dependencies and "training wheel" shortcuts..
I particularly like the idea of relying less on custom mappings that are not immediately transferrable between machines, say if you are trying to log in to a new school server.
If you rely too much on mappings that you used when you started learning, you're going to keep needing to `git clone` your dotfiles into different machines.
There may be circumstances where you can't do that, so I think it's good practice now to get comfortable with Vim out of the box as possible.

The biggest one for many folks obviously is leaving Insert mode to go back into Normal mode.
For me, I used `:inoremap jj <Esc>` which I think is very popular.
However, since this didn't work in RStudio's Vim mode, that left me with a bunch of extraneous "jj" characters all over my document.
My solution was reteaching myself the standard mappings that ship with Vim.
The first way folks are taught to exit Insert mode is using the Escape key, and I don't hate myself enough to stretch my pinky finger everytime I want to move around my document.
An alternative is `CTRL-[` but I felt like this was almost as cumbersome.
What's more useful I think is `CTRL-c` (Or `C-c` as it's often written).
This keeps everything on your left hand and at least for my workstation it's pretty easy to press without too much hand movement.

One of the big benefits for me in using standard mappings for me is that I can now move pretty easily between RStudio, Overleaf, other apps that have Vim keybindings, and editing text in the terminal.
Muscle memory is important and the more practice you have with easily transferrable keybindings, the better off I think you will be in the long run.


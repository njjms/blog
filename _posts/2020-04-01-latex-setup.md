---
layout: post
title:  Friendship Ended with Overleaf! Now Linux is My Best Friend!
date:   2020-04-01 23:07:28 +0000
categories: linux
---

Something that I've finally had to do now that I'm in my last quarter of my MSc is get my LaTeX environment set up.
I've somehow managed to make it this far in graduate school with only markdown and its mathJaX support, but now that I'll be juggling all kinds of references, it's probably a good idea to finally learn some lay-tecks.
Plus, I'm always looking for an actual productive excuse to mess around with my .vimrc!

# Setup Goals

In the past, I've used `Overleaf` as my TeX editor which was awesome since I could basically grab other people's templates.
Also, since it's in the cloud, I could edit my files from anywhere with an internet connection.
However, I don't want to rely on Overleaf for my MSc report for the following reasons:

+ While Overleaf does have a Vim mode, it doesn't have all the features that even base Vim does (for example, all the nice autocompletion functions or custom mappings), much less the features found in vim plugins
+ I've personally experienced a lot of issues with Overleaf being down at inopportune times, so my productivity would really be at the mercy of some unreliable server
+ Since the pandemic lockdown closed my department, there is really no reason for me to leave my apartment so there's no advantage in having my TeX douments in the cloud. It's more efficient for me to have a local TeX repo and then push everything to github to save it.

I wanted a TeX setup that was similar in functionality and appearance to Overleaf, namely a text editor (in my case, vim) and a pdf reader.
When edits were made to the .tex file, the file could be recompiled **without leaving** any applications and appear in the reader.
I also wanted the reader to have basic functionality, like scrolling, zooming, search, etc.

While all the cool kids love automatic TeX compilation as they are editing, I was fine with manually executing compilation, preferably when saving my .tex file using `:w`.

# Ingredients

After a day of [finagling](www.merriam-webster.com/dictionary/finagle), my set up is actually at a place that I really like and I think will serve me pretty well in the next 10 weeks.
Here's all the ingredients that I used to bake this savory text formatting brioche:

+ vim with the the excellent [vimtex](https://github.com/lervag/vimtex) plugin
+ [zathura](https://pwmt.org/projects/zathura/), a pdf reader that supports a lot of things, including auto reloading
+ [latexmk](https://mg.readthedocs.io/latexmk.html) for compilation
+ and since I use WSL, I'll also need an X server like [Xming](https://sourceforge.net/projects/xming/)

| ![text_setup.PNG](/assets/tex_setup.PNG) |
|:--:|
| *zathura (in xming) and vim working together in WSL!* |

# Installation

This should be pretty straightforward if you're doing everything in the terminal.
To get zathura and latexmk, you can type the following right into the shell if you're on a Debian OS (I use Ubuntu).

{% highlight bash %}
sudo apt install zathura
sudo apt install latexmk
{% endhighlight %}

Then for vim, use your favorite plugin manager (I use vim-plug since I am otaku for Junegunn Choi) to download vimtex.

# Setup

Now we have all the pieces... how to we assemble them into what we need?

Let's start with vimtex first.
In addition to its many additional TeX editing features, notably new text objects, it also has a built-in command to compile TeX **without leaving vim**: `\ll`.
They should also automatically open in a pdf reader.
However, by default vimtex uses evince (I believe) or something like it.
This is a perfectly fine reader, but I wanted something a little more customizable.

This is where zathura comes in.
If you enter the following in your .vimrc:

```
let g:vimtex_view_method = 'zathura'
```

Then vimtex will open documents in zathura after they have been compiled.

Now what's specifically so great about zathura?
First, it supports autoloading so when pdfs are recompiled, they will appear in zathura without the application needing to restart.
Second, zathura has its own `zathurarc` file for custom mappings!

By default, the zathura configuration file is in `~/.config/zathura/zathurarc`.
A lot of default keybindings in zathura are similar to vim, for example, pressing `j` will scroll you down a little.
I mapped other basic pdf reader functionality to common vim keybindings, for example pressing `d` will scroll down half a page and `u` will scroll up half a page.

Some other mappings that I thought might be useful are using `J` and `K` for zooming in and out respectively.
My entire zathurarc file is provided below:

```
map J zoom in
map K zoom out
map p print
map u scroll half-up
map d scroll half-down
map r reload
map R rotate
```

Awesome, we're almost done assembling all the pieces.
Now all that's needed is a mechanism to "catch" document saves as we make them and recompile the .tex file so that they show up in zathura.
This is actually pretty easy.

So if we call latexmk on a .tex document in the terminal, it will compile it into a pdf document.
However, if you read the man page for latexmk, you'll find that there is an option flag `-pvc` which stands for "preview continuously".
If you run latexmk with that flag enabled, the program will continuously monitor for changes in your .tex file (which happen everytime you save using `:w`) and recompile the document when it does.

The downside to this is that we need to have a second terminal open running `latexmk -pvc` while we do our actual text editing in a separate terminal.
Thankfully, having two shells in Windows Terminal isn't too bad, and I figure an inelegant solution is better than no solution at all.
One of the cool side benefits of this is that if I close my vim session for some reason but *don't* turn off latexmk in the other terminal, I can reoopen the .tex file and start editing again and latexmk will still be on since it's not tied to the vim session.
As a final piece, I have a function saved in my .bashrc so I don't have to type out the entire command every time I want continuous previewing for a .tex file:

{% highlight bash %}
pvc () {
	latexmk -pdf -pvc $1
}
{% endhighlight %}

Lastly, make sure you have you X server running if you are using WSL so zathura can actually be displayed to you.
I have the following line in my .bashrc which you may or may not need, depending on your system:

```
export DISPLAY=localhost:0.0
```

# End result?

I can edit my TeX files on a local setup with a full-featured and extensible text editor in vim+vimtex and continuously view those files in a pdf reader whose major keybindings are now essentially the same as vim.
When I have them open side by side, I can switch between them and use both applications without ever having to touch a mouse or trackpad or remember different bindings.

Beats Overleaf, imo :)

---
layout: post
title: "slime time: Replacing RStudio/Jupyter with vim-slime/tmux?"
date:   2020-07-06 23:07:28 +0000
categories: [linux]
---

# Introduction

It's no personal secret that I am a big fan of vim and terminal tools.
However, my work as a statistician often required experimenting with different tools, reading help docs, and playing around with visualizations.
The process of writing code in a text file and then running said code in a terminal was too slow and too tedious.
So I stuck to my ways of the past, relying on large programs like RStudio, Spyder, and more recently Jupyter notebooks.

What I really wanted though was to be able to edit code in the terminal and then run said code immediately like one would do in a typical IDE.
I had read about the `vim-slime` plugin for a while but it wasn't until this past weekend that I finally got around to setting it up and adding it to my rc files.
Boy, is it fun.
But is it useful? Let's play around with it and find out.

![](/assets/slime_setup.PNG)
<center>
Tmux window with vim on the left, a Python and R REPL on the right, and some plot outputs!
</center>

# Setup

Installing `vim-slime` itself is pretty easy.
I use `vim-plug` and just added the plugin to my `.vimrc`

However, that's just scratching the surface of what we need to do.
`vim-slime` in essence just sends text from one terminal to another.
Therefore, we need a multiplexer like GNU screen or tmux to get it operational.
I have used tmux on and off before, so that's what I decided to go with.

Setting up `vim-slime` and setting up `.tmux.conf` can be tricky if you haven't done it before (it was for me).
Thankfully, there is a lot of documentation for both tools.

By default, `vim-slime` sends code from one window to another using `<C-c><C-c>`.
However, this doesn't seem to work on WSL.
So I changed the slime mappings to something that worked a little better for my workflow.

```
let g:slime_target = "tmux"
let g:slime_paste_file = "$HOME/.slime_paste"

let g:slime_cell_delimiter = "```"
nmap <leader>ss <Plug>SlimeLineSend
nmap <leader>sc <Plug>SlimeSendCell
nmap <leader>sr <Plug>SlimeParagraphSend                                                             xmap <leader>sr <Plug>SlimeRegionSend
nmap <leader>sf <Plug>SlimeConfig
```

Note that `vim-slime` includes a delimiter which I set to three backticks.
The cool thing about having a delimiter is that I can emulate the code chunks from RMarkdown and RStudio.
I also added several vim shortcuts to emulate some built in shortcuts in RStudio.
Note that my `<leader>` key is mapped to the spacebar.

```
noremap __<leader> <Space><-<Space>
inoremap <C-S-n> %>%<Space>
inoremap ``<leader> <++>```<CR>```<++><C-c>kA<CR>
inoremap `<leader> ```
```

.tmux.conf takes a lot of work to setup and there were some additional issues that I ran into because of WSL.
Notably, copy-pasting is pretty tough on tmux to begin with and getting it to work on WSL is even more of a headache.
What worked for me was adding this line to my `.tmux.conf`
```
bind P paste-buffer
bind-key -T copy-mode-vi v send-keys -X begin-selection
bind-key -T copy-mode-vi y send-keys -X copy-selection
bind-key -T copy-mode-vi r send-keys -X rectangle-toggle
bind -T copy-mode-vi Enter send-keys -X copy-pipe-and-cancel "xclip -i -f -selection primary | xclip -i -selection clipboard"

set -g mouse on
```
and then using mouse-select by holding `<Shift>` and using the usual right click copy from WSL.

A lot of lines from my `.tmux.conf` is stolen from various stack overflow posts, blogs, and videos.
I have posted all dotfiles on my [github](https://github.com/njjms), so feel free to steal it if you'd like.

The other big part of a data analysis IDE is begin able to see plots right away. 
Running this in WSL requires an X server like Xming so the plots appear in your desktop.

# Advantages... Disadvantages...

I would say the main disadvantage is setup cost.
At the end of the day, I am basically getting a very raw IDE.
For a lot of people, especially those in fields like mine, this just isn't necessary.

![](/assets/slime_setup2.PNG)
<center>
Same as above but the REPLs are moved to other tmux windows so they are out of sight
</center>

The advantages will appeal mostly to people who love vim.
I can now use vim for **everything**, including my statistics work in R or Python.
While RStudio supports a vim mode that has a lot of features (registers, marks, etc.), it's also missing a lot of things that I like.
Notably missing are the jump list and vim's powerful autocomplete functions.
RStudio's vim mode also freaks out a lot and I find myself needing to restart it consistently.

Also, since all `vim-slime` is doing is sending text from one terminal to another, I can send text from vim on my local machine to a REPL running on a remote server.
AND it can really be in any language, not just R and Python.
For example, in future work I might need to use SAS on a big server.
This would be where getting slimy is a huge advantage.

I'll add that a cool side effect of using `vim-slime` is that I can type R and Python code in the same document and run them in their separate REPLs.
This is not going to replace a package like `reticulate` since the REPLs can't interact with one another and can't use the same objects, but man is it fun!

So am I going to move full time to using Vim?
*Sort of yes*.
I'm don't plan on uninstalling RStudio, but I think for a lot of analyses, it's no longer necessary to run a big IDE.
However, if I need to knit an RMarkdown PDF, I would probably best be served by going back to RStudio (at least for now!).
I'll need to play around more with this setup, but I think it is absolutely promising.

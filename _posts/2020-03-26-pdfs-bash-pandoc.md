---
layout: post
title: "Making PDF documents using Bash and Pandoc"
date:   2020-03-26 23:07:28 +0000
categories: linux
---

Like most of the industrialized world, I like reading and formatting documents in PDF form.
However, after using Linux and various command line utilities, I've grown dissatisfied with using MS Word, RStudio, and Jupyter to format quick PDF documents.
After some encouragement from watching [Luke Smith videos](https://www.youtube.com/c/lukesmithxyz) and reading the Linux docs, I decided to move almost completely to creating PDF documents in the terminal.

To do this, I needed the following tools:

+ Vim
+ Bash scripting
+ Pandoc

The first two tools come with any Linux distribution (I'm running Ubuntu on WSL).
The last tool is a Haskell utility that you can `sudo apt-get` or build from source.
In a sentence, this tool just converts documents of one format into another format.

### Markdown to PDF

The way we use `pandoc` in the command line is to call it like any program.
It has a few flags, notably the `-o` function where we specify the output file, `-t` flag where we specifc the output format, `-f` where we specify the input format, and `-s` which specifies a standalone file.
See this great [demo](https://pandoc.org/demos.html) page provided by the Pandoc team.

Given a markdown file, say `test.md`, we can convert it into a pdf file using `pandoc test.md -f markdown -t pdf -s -o test.pdf`, although the `-f` flag is unnecessary here since by default it accepts markdown documents.
However, typing this over and over again is kind of tedious.

Let's come up with an easier way to do this using Bash!

### Let's put this in a script

I will make a bash script to do this instead of a bash function although I could really do either for this quick project.
First, we should make sure that the script is in our `$PATH` somewhere, so make sure to `$ echo $PATH` and put the file in someplace like `/usr/local/bin`.

The script `md2pdf` I wrote to simplify the above `pandoc` command into is provided below.

The first line of course is the shebang line `#!/bin/sh` so that we can make sure that the script is run in a shell (by default and for my machine, it's Bash).

The third line is creating a variable called `file`.
This would be the markdown file that we give our script.

The fifth line is creating a new string variable which takes the name of the markdown file without the extension using [parameter expansion](https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html#Shell-Parameter-Expansion).
I could have also used the `$(basename test.md .md)` Bash built-in function, but I thought this was a good way to practice parameter expansion!

Finally I call the `pandoc` line I wrote above with an additional option to set the margins and if that command is successful, then we echo a success!

{% highlight bash linenos %}
#!/bin/sh

file=$1

filename="${file%.*}"

`pandoc $file -o $filename.pdf -V geometry:margin=1in` && echo "Successfully converted $file to $filename.pdf"
{% endhighlight %}

Lastly, don't forget to `chmod +x` this file so that we can execute it from the command line.

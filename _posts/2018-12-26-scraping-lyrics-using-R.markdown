---
layout: post
title:  "Scraping Lyrics with R"
date:   2018-12-26 07:07:28 +0000
categories: jekyll update
---

This winter break I got to see one of my favorite bands **The Menzingers** in their hometown of Scranton PA for their annual holiday show.
As always, they put on a great concert and it was a bonus that it was in Scranton since I'm a pretty big fan of The Office.

If you are not familiar with the 'zingers, essentially their music is quasi-punk rock mixed with various bits of americana where they sing sad songs about growing old and feeling nostaligic.
I've always admired their lyricism.
Even though they got their start in basements and Catholic school assemblies, they don't shy away from throwing in words like "waxwing" or referencing Kafka.
On the drive back from Scranton PA to my parents' place, I got the idea to analyze their lyrics.

Obviously the first goal is getting a corpus of lyrics to work with.
There are a few APIs out there specifically for analyzing music and lyrics, but I thought it might be a useful exercise to practice web scraping using R.

To do this, we'll need a few things:

+ A lyrics website. I used [azlyrics.com](https://www.azlyrics.com/m/menzingers.html "Menzingers lyrics")
+ The `rvest` package in R
+ Some knowledge of DOM and using CSS selectors or XPath queries

First thing's first is installing `rvest` on your machine if your don't already have it.
I really like this package; it's pretty easy to use and works well in the tidyverse which makes sense because it is written by patron saint Hadley Wickham.
Once you have it downloaded, there are a few important functions to know right off the bat: `read_html()` and `html_nodes()`.

`read_html()` takes our URL as a string.
Here I am inputting the Menzingers' arists page.
This artist page basically has links to a bunch of individual pages for each of the Menzingers' songs. 
What I eventually want is a vector of these individual URLs, so to begin I will grab the HTML of the artist page.

`html_nodes()` takes either a CSS selector or XPath query as input.
I am more used to XPath, so I will use that.
The output of this is a list of XML elements that I can grab attributes from.

```
library(rvest)
main_url <- "https://www.azlyrics.com/m/menzingers.html"

zings <- read_html(main_url)

zings %>% html_nodes(xpath = '//*[@id="listAlbum"]/a') -> songs
```

To extract the actual URL links, we note that the link text are essentially the same except for the end.
This is great for us since the `href` attribute in each of the elements in our `songs` XML list only contains the last part of the link.
We will simply strip the bits of the `href` that we don't need and paste the rest on to our base URL.

We can use the `html_attr()` function to grab the value of an attribute.

```
base_url <- "https://www.azlyrics.com/lyrics/menzingers/"

songs %>% html_attr(name = "href") -> links

links <- links[!is.na(links)]
links <- gsub("../lyrics/menzingers/", "", links)
song_links <- paste0(base_url, links)
```

Now that we have a vector of URLs for the individual song lyrics, we can write a function that will return the body of the text.
For this website, mine looks like the following:

```
get_lyrics <- function(page_url) {
  page_url %>% read_html() %>% html_nodes(xpath = '/html/body/div[3]/div/div[2]/div[5]') %>% 
    html_text() %>% { gsub("\r", "", .) } %>%
    { gsub("\n", " ", .) } %>%
    { gsub("[[:punct:]]", "", .) } %>%
    str_trim() %>% tolower() -> body
  Sys.sleep(10)
  return(body)
}
```

Couple things here: first, we have to make sure we use some kind of `sleep()` function since a lot of sites will block us if we request from their site to quickly!
Second, I make use of the `html_text()` function to grab just the text of an HTML node as well as `stringr::str_trim()`.
Lastly, I am stripping out newlines and carriage return characters.
You may want to keep newlines in since line breaks really are part of the structure of the lyrics!
I only removed them because I care more about the acutal words being used.

Running this function on our `song_links` vector, we end up with a tidy corpus of lyrics data!

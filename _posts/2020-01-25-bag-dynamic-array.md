---
layout: post
title: "Adventures in Data Structures Vol. 2.5: You Old Bag"
date: 2020-01-25 010:07:28 +0000
categories: cs
---

Previously in this series we explored using a dynamic array to implement a stack.
This was pretty straightforward, and only required four functions which made use of the preexisting dynamic array functions

Today, I realized that I forgot to mention anything about bags and how easy they are to implement using a dynamic array.
This is pretty quick and will be more like a mini-episode.

The bag is an abstract data type which, well, resembles a physical bag (the classic example is a bag of marbles).
There is no order to the elements in the bag, but the bag does support basic operations such as:

1. **add** (a marble to the bag)
2. **remove** (a marble from the bag)
3. **contains** (is this marble in this bag?)

Adding an element to a bag is the same as the prior implemention with the stack.
Again, since order doesn't matter in the bag, we can just `push` the element into the bag.

What the stack didn't have was the `contains` and `remove` functions.

Let's implement them here~

```
int containsDynArr(DynArr* v, TYPE val)
{
	for (int i = 0; i < sizeDynArr(v); i++)
	{
		if (v->data[i] == val)
		{
			return 1;
		}
	}
	return 0;
}
```

All the `contains` function does is iterate through the dynamic array until it finds the element that we're looking for and returns a $1$ (or doesn't and returns a $0$!)

```
void removeDynArr(DynArr* v, TYPE val)
{
	assert(v != NULL);
	assert(v->size > 0);

	for (int i = 0; i < sizeDynArr(v); i++)
	{
		if (v->data[i] == val)
		{
			removeAtDynArr(v, i);
			return;
		}
	}
}
```

The `remove` function is slightly spicier, but not by much.
Again, the main logic is to iterate through the dynamic array until it finds an element that matches $val$ and then removes it.
The function then has to exit, which since it returns **void** means we just use a simple `return;` call.

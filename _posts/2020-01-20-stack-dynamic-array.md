---
layout: post
title: "Adventures in Data Structures Vol. 2: $TACKED (ft. Dynamic Arrays)"
date: 2020-01-15 010:07:28 +0000
permalink: /cs/
categories: cs
---

In the first episode of adventures in data structures, I wrote out all the code for implenting the dynamic array.
That was great and all, but what can we actually **do** with it?
More importantly in the context of data structures, what abstract data structures can we **build** with it?

Today, I wanted to go over implementing the stack using a dynamic array.
The stack is a classic data structure and is often thought of as a stack of plates.
The key fact to know is that it's FIFO (first in first out), so much like you might have a stack of dishes next to your desk after yet another week of making Easy Mac every night, you clean the top first, then the second, then the third, all the way down to the 12th or whatever (Easy Mac is awesome).

Implementing the stack means implementing 3 basic functions:

1. **push** (which adds an element on top)
2. **pop** (which takes the top element off)
3. **top** (which looks at the top element)

and an **isEmpty** function (while we're at it).

Using the functions we wrote before for the dynamic array, this implementation is pretty straightforward!

Let's start with `isEmpty` which is not too bad.

{% highlight c %}
int isEmptyDynArr(DynArr* v)
{
	assert(v != NULL);
	if(sizeDynArr(v) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
{% endhighlight %}

The `push` function is almost as simple!

{% highlight c %}
void pushDynArr(DynArr* v, TYPE val)
{
	assert(v != NULL);
	addDynArr(v, val);
}
{% endhighlight %}

Again, `addDynArr(v, val)` adds $val$ to the back of $v$.
So we can kind of treat the back of $v$ as being the **top of the stack**.
Let's segue into `top` and `pop` now:

{% highlight c %}
TYPE topDynArr(DynArr* v)
{
	assert(v != NULL);
	assert(v->size > 0);
	return getDynArr(v, sizeDynArr(v) - 1);
}
{% endhighlight %}

Again, notice that the top element of $v$ is located at the index $size - 1$.
The `pop` function is very similar to `top`.

{% highlight c %}
void popDynArr(DynArr* v)
{
	assert(v != NULL);
	assert(v->size > 0);
	removeAtDynArr(v, sizeDynArr(v) - 1);
}
{% endhighlight %}

And boom, just like that we have all the functions needed to implement a stack using a dynamic array!

In our next episode, I'll talk about implementing a bag using a dynamic array.

I'm so lonely.

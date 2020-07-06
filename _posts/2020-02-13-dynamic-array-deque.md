---
layout: post
title: "Adventures in Data Structures Vol 7: The Dynamic Deque"
date: 2020-02-13 010:07:28 +0000
categories: cs
---

It's almost midterms for CS261 at Oregon State (as of writing this, mine is tomorrow)!

While I was reviewing my data structures notes, I realized I had forgotten to talk about a pretty interesting and tricky data structure: the **dynamic array deque**.

Strictly speaking, the data structure we will use to implement this deque is not technically a dynamic array since a dynamic array is fixed to start at index 0 within a block of allocated memory.
However, this is a big handicap when it comes to implementing the deque, since everytime we add to the front we will have to shift down resulting in an O(n) operation and everytime we remove from the front, we have to shift everything else up resulting in another O(n) operation.

However, if we allow the beginning index to float around from 0 to any arbitrary integer that's less than the capacity **and** also let entries wrap around the ends of the block of memory, this dynamic array deque is much more efficient.
In order to do this, we will need to maintain two values:

1. The starting index of the data within the memory block
2. The total size of the deque

As always, let's start off with the struct:

{% highlight c %}
struct deque
{
	TYPE* data;
	int capacity;
	int size;
	int beg;
};
{% endhighlight %}

The two values `beg` and `size` are the respective integers we stated up above.


Setting the capacity for the dynamic array deque will be similar to the regular dynamic array stack, but with some tweaks.

{% highlight c %}
void _dequeSetCapacity(struct deque* d, int newCap)
{
	assert(d != NULL);
	assert(newCap >= d->size);

	TYPE* newData = (TYPE *)malloc(sizeof(TYPE)*newCap);
	assert(newData != NULL);

	int j = d->beg;
	for (int i = 0; i < d->size; i++)
	{
		newData[i] = d->data[j];
		j = j+1;
		if (j >= d->capacity)
		{
			j = 0;
		}
	}

	free(d->data);
	d->data = newData;
	d->capacity = newCap;
	d->beg = 0;
}
{% endhighlight %}

Notice here that when we copy over to the new array, **we start at 0** even if the current beginning is some other integer.
Also notice that if $j$ exceeds the current capacity of the deque, that means we have to wrap around the end of the deque and start at 0.

Now that we have our first function, let's initialize this bad boy.

{% highlight c %}
void dequeInit(struct deque* d, int initCapacity)
{
	assert(initCapacity > 0);
	d->size = 0;
	d->beg = 0;
	d->capacity = initCapacity;
	d->data = (TYPE *)malloc(sizeof(TYPE)*initCapacity);
	assert(d->data != NULL);
}
{% endhighlight %}

Now we can implement the `add`, `remove`, `Front`, and `Back` functions!
The only trick that we have to remember is catching the condition when we have to wrap around the ends of the memory block.

{% highlight c %}
int dequeSize(struct deque* d)
{
	return d->size;
}

void dequeAddFront(struct deque* d, TYPE newValue)
{
	assert(d != NULL);
	if(d->size >= d->capacity)
	{
		_dequeSetCapacity(d, 2*d->capacity);
	}
	
	d->beg--;
	if (d->beg < 0)
	{
		d->beg = d->capacity - 1;
	}
	d->data[d->beg] = newValue;
	d->size++;
}

void dequeAddBack(struct deque* d, TYPE newValue)
{
	assert(d != NULL);
	if(d->size >= d->capacity)
	{
		_dequeSetCapacity(d, 2*d->capacity);
	}
	
	int index = d->beg + d->size;
	if (index >= d->capacity)
	{
		index = index - d->capacity;
	}

	d->data[index] = newValue;
	d->size++;
}
{% endhighlight %}

For the `addFront` function, the key was decrementing the `d->beg` value first and checking to see if it was negative, meaning `d->beg` was 0.
If it was, that means we have to wrap around to the end of the memory block.

For the `addBack` function, we had to define an integer `index` which was equal to `d->beg + d->size` since this would give us the index of the next open spot in the memory block.
However, if this `index` is greater than the capacity of the array, we have to wrap around to the front of the block.

{% highlight c %}
void dequeRemoveFront(struct deque* d)
{
	assert(d != NULL);
	assert(d->size > 0);
	d->beg++;
	if(d->beg >= d->capacity)
	{
		d->beg = 0;
	}
	d->size--;
}

void dequeRemoveBack(struct deque* d)
{
	assert(d != NULL);
	assert(d->size > 0);
	d->size--;	
}
{% endhighlight %}

The `remove` functions are also slightly different depending on whether we are removing from the front or removing from the back.

`RemoveFront` means incrementing `d->beg`.
However, in the case that `d->beg` is in the last spot of the block, we can't let `d->beg` be bigger than the current capacity so we set it back to 0.

`RemoveBack` is simpler!
We can just decrement `d->size`.

With how we have defined this structure, these are clever ways of deleting elements in this array-like structure that doesn't involve freeing memory or anything complicated.
If we know how to work with `d->beg` and `d->size` to clip the front or back of the deque, then as far as the deque itself is concerned those values have been removed!

Finally, we have `Front` and `Back`, which are pretty easy!

{% highlight c %}
TYPE dequeFront(struct deque* d)
{
	assert(d != NULL);
	assert(d->size > 0);
	return d->data[d->beg];
}

TYPE dequeBack(struct deque* d)
{
	assert(d != NULL);
	assert(d->size > 0);
	int index = d->beg + d->size;
	if (index > d->capacity)
	{
		index = index - d->capacity;
	}

	return d->data[index];
}
{% endhighlight %}

And there we have it!
A *dynamic array deque*!

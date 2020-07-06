---
layout: post
title: "Adventures in Data Structures Vol 9: Ordered Arrays and Binary Search"
date: 2020-02-24 010:07:28 +0000
categories: cs
---

Exam review time already?? 
Time really flies.

Tonight, instead of spending the final day of the quarter at the bars, I'll be spending it at home with a big thing of soup.
Being in the midst of a pandemic isn't great to say the least, but I suppose if I'm going to self-isolate, I can at least be a little productive haha.

# Binary Search in C

Today, I really wanted to go over ordered arrays and the binary search.

The main benefit to having *ordered collections* is that the **contains** operation is no longer a linear search!
Therefore, instead of being an O(n) operation, it is instead O(log n) which is **much faster**.
After all, consider that $log_2 1000000 \approx 20$.

The requirements for performing a binary search are that:

+ The collection is ordered
+ Random access to the elements is allowed

The binary search function in C will probably look something like this:

{% highlight c %}
int _binarySearch(TYPE* data, int size, TYPE val)
{
	int low = 0;
	int high = size;
	int mid;
	
	while (low < high)
	{
		mid = (low + high) / 2;
		if (LT(data[mid], val))
		{
			low = mid + 1;
		}
		else
		{
			high = mid;
		}
	}
	return low;
}
{% endhighlight %}

We have two integers `low` and `high` which will be the boundaries of the indices we are seraching for `val`.
We start off by defining the `low` and `high` to be the indices at the ends of the collection.

Essentially what this function is doing is first finding the middle index of the sorted collection and assigning that to the variable `mid`.
If the element at that middle index is *less than* the value we are searching for, then we can reassign `low` to be `mid + 1` since we know that the value we are searching for in contained somehwere inside that interval.

If that is not the case, then the value we are searching for is instead somewhere between `low` and `mid`, so we can change `high` to `mid`.
We then repeat this step until `low == high`, at which point, we return an integer for the index where either `val` is located **OR** where `val` could be located if we were to insert it.

# Implementing an Ordered Bag

A dynamic array for an ordered bag is a pretty straightforward collection to implement.

Recall that a bag has the following operations: add, contains, and remove.
If we enforce the bag to keep elements in order, `add` and `remove` get slower and become O(n) since we have to slide elements over.
`Contains` however gets much faster (O(log n) instead of O(n)).

The `add` function doesn't change too much, it just has to make use of the index outputted by the binary search function.
The rest is basically just the same as regular old bag `add` function.

{% highlight c %}
void dynArrayAddAt(struct dynArray* da, int index, TYPE newElement)
{
	int i;
	assert(index >= 0 && index <= da->size);

	if (da->size >= da->capacity)
	{
		_dynArraySetCapacity(da, 2*da->size);
	}

	for (int j = (da->size - 1); j >= index; j--)
	{
		da->data[j+1] = da->data[j];
	}

	da->data[index] = newElement;
	da->size++;
}
{% endhighlight %}

The `contains` function is pretty easy.
In this implementation, I call `_binarySeach` inside the function.

{% highlight c %}
int orderedArrayContains(struct dynArray* da, TYPE testElement)
{
	assert(da != NULL);
	assert(da->size != 0);
	int contains = 0;

	int index = _binarySeach(da->data, da->size, testElement);

	if (index <= da->size-1 && da->data[index] == testElement)
	{
		contains = 1;
	}
	return contains;
}
{% endhighlight %}

Finally, the `remove` function is almost no different than the original implementation.
What we have to make sure of though is that the element at the index location is equal to the element we want to remove.

{% highlight c %}
void orderedArrayRemove(struct dynArray* da, TYPE testElement)
{
	assert(da != NULL);
	assert(da->size != 0);
	int index = _binarySearch(da->data, da->size, testElement);

	if (index <= da->size - 1 && da->data[index] == testElement)
	{
		removeAtDynArr(da, index);
	}
}
{% endhighlight %}

#### Last little note... Fast Merge

Merging two ordered arrays into a single new ordered array is also relatively fast at O(n).
We basically compare the two ordered arrays pairwise to add elements into the single larger array.
At the end, the larger array will be automatically sorted!


---
layout: post
title: "Adventures in Data Structures Vol. 1: The Dynamic Array"
date: 2020-01-15 010:07:28 +0000
permalink: /cs/
categories: cs
---

One big academic sword that always hung over my head was my lack of formal computer science knowledge.
All the programming that I've learned up to this point has been mostly self-taught, with occasionally the assistance of a kind-hearted and patient engineer.

This quarter I decided to change that by taking **my first computer science course ever!**.

I opted not to take the introductory sequence taught here at Oregon State, and instead skipped right to data structures.
I figured that if I'm going to work in statistics, having some foundational knowledge about the different primitive ways we store data is probably useful!

Today I wanted to begin by talking about our familiar friend **the array**.
The array is one of the first data structures people learn about in school and most people are at least familiar with the general logic.
It's basically a column of data where you can randomly access any of the elements inside of it.

The costs of basic operations using an array are:

+ **Adding** is O(1) most cases since we can add elements to the end of an array (but this is assuming there is still room in the array!)
+ **Removing** is also O(n) since we might have to remove the front element and shift all the remaining elements down from their current addresses
+ **Contains** is O(n) since this might involve checking every element in the array

There are advantages and disadvantages to using the array, but one of the big issues is that the capacity of the array is **fixed**.
If you add data to an array that's already full to capacity, you are going to run into problems.
This is where the **dynamic array** comes in handy.

The **dynamic array** is basically an array that can grow in size.
In the implementation we use, everytime the dynamic array reaches capacity, it:

1. Allocates space for a new array *twice* the original capacity
2. Copies all the elements from the new array over to the old array
3. Gets rid of the old array

In C, the basic struct of the Dynamic Array is fairly simple:

```
struct DynArr
{
	TYPE *data;
	int size;
	int capacity;
};
```

The dynamic array consists of three things: a pointer to the beginning of a contiguoys block of memory which we will use to store the data of type *TYPE*, an integer for the current size, and another integer for the capacity of the array.
The functions which implement the behavior of the dynamic array are also fairly straightforward.
Let's talk about initializing the array first:

```
void initDynArr(DynArr* v, int capacity)
{
	assert(capacity > 0);
	assert(v != NULL);

	v->data = (TYPE *)malloc(sizeof(TYPE) * capacity);
	assert(v->data != NULL);

	v->size = 0;
	v->capacity = capacity;
}
```

Here, this is where an empty array of positive capacity is allocated from the heap (but not returned).
We would call this init function in another function like:

```
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr* r = (DynArr *)malloc(sizeof(DynArr));
	assert(r != NULL);

	initDynArr(r, cap);
	return r;
}
```

This function returns a pointer to our new dynamic array with specified capacity.
We'll be using this function as we add data, grow, and require a new block of memory.

Some other important functions include freeing and deleting the dynamic array and getting the current size:

```
void freeDynArr(DynArr* v)
{
	if(v->data != NULL)
	{
		free(v->data);
		v->data = NULL;
	}
	v->size = 0;
	v->capacity = 0;
}

void deleteDynArr(DynArr* v)
{
	freeDynArr(v);
	free(v);
}

int sizeDynArr(DynArr* v)
{
	return v->size;
}
```

Finally to the *piece de resistance*: resizing the dynamic array.
This function is probably the most complicated in the entire implementation, but it mostly just follows from the pseudocode I wrote above:

```
void _dynArrSetCapacity(DynArr* v, int newCap)
{
	assert(v != NULL);
	assert(newCap >= v->size);

	TYPE *newArray = (TYPE *)malloc(newCap*sizeof(TYPE));
	assert(newArray != NULL);

	for (int i = 0; i < v->size; i++)
	{
		newArray[i] = v->data[i];
	}
	
	free(v->data);
	v->data = newArray;
	v->capacity = newCap;
}
```

So again, there are a couple piece to this function.
First is allocating the necessary memory to fit a `newCap` number of elements with type *TYPE* and giving us a pointer to that block of memory.

We can then iterate through that block of new memory using a for loop and move all the elements from the first array into the new array.

Finally, we free the old array and make our dynamic array struct $v$ point to our new, bigger array.
We also set the capacity of $v$ to be the new cap!

Now that we have the core functionality of the dynamic array down, what can we do with it?

Let's write functions to add elements, get elements, put elements, and remove elements!

```
void addDynArr(DynArr* v, TYPE val)
{
	if(v->size >= v->capacity)
	{
		_dynArrSetCapacity(v, 2*v->capacity);
	}
	v->data[(v->size)] = val;
	v->size++;
}
```

Here, it's important to remember that the element at index **v->size** is actually empty (well, techncially its garbage because this is C, but in any event we want to put the new element at the end.

This function will return the value at a particular position inside the dynamic array, of course assuming that the position is valid. 

```
TYPE getDynArr(DynArr* v, int pos)
{
	assert(v != NULL);
	assert(v->size > 0);
	assert(pos >= 0 && pos < v->size);
	return v->data[pos];
}
```

The `put` function will replace an element at a specific location in the dynamic array.

```
void putDynArr(DynArr* v, int pos, TYPE val)
{
	assert(v != NULL);
	assert(v->size > 0);
	assert(pos >= 0 && pos < v->size);
	v->data[pos] = val;
}
```

The `swap` function will switch the values held in two different addresses within the dynamic array.

```
void swapDynArr(DynArr* v, int i, int j)
{
	TYPE temp = getDynArr(v, i);
	assert(i < v->size && i > 0);
	assert(j < v->size && j > 0);
	putDynArr(v, i, getDynArr(v, j));
	putDynArr(v, j, temp);	
}
```

Notice that we had to save the value in the *ith* index before we started using `put`, otherwise we would overwrite it and then when we would call `put` a second time on the *jth index*, we'd be putting back the same value that was already there!

Finally, we have the `remove` function which takes out an element at a specified location and then moves all the elements back to fill in the gap.

```
void removeAtDynArr(DynArr* v, int idx)
{
	assert(v != NULL);
	assert(v->size > 0);
	assert(idx >= 0 && idx < v->size);

	for (int i = idx; i < v->size - 1; i++)
	{
		putDynArr(v, i, getDynArr(v, i+1));
	}
	v->size--;
}
```

Using these function, we can do all sorts of cool implementations using dynamic arrays.
For example, we can use dynamic arrays to implement abstract data types like bags, stacks, queues, and deques.
We'll explore these more next time!

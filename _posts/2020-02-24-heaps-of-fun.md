---
layout: post
title: "Adventures in Data Structures Vol 8: Heaps of Fun"
date: 2020-02-24 010:07:28 +0000
categories: cs
---

So a great update! Aced the data structures exam :)

Had a great week off and now it's back to work.
Today, I wanted to go over **heaps**.
Heaps are basically a type of binary tree that preserve **heap order**, that is, each node's value is less than or equal to the value of its child nodes.
Consequently, they are *partially ordered*, but not completely.

Later on, we will see that this property of *heap order* is very useful for implementing the priority queue ADT, which is essentially a collection designed to make it easy to find the element with the highest priority. 

We can implement a heap using our friend the *dynamic array*.
Recall that we represent trees in a dynamic array by the following:

+ Children of node $i$ are found in positions $2i + 1$ and $2i + 2$
+ The parent of node $i$ is found in position $(i - 1)/2$

The two main operations we are concerned with are `addition` and `removal`.
In both operations, we want to **first** preserve completeness first and **afterwards** fix heap order.

+ When adding values to a heap, we first *add it to the end* of the array to preserve completeness, and then *percolate up* to preserve heap order. 
+ When removing values, we remove the root and then replace that value with the last filled position, thereby preserving completeness of the tree. We then fix heap order by *percolating down* to the appropritae node.

For both these operations, we will need to employ functions which compare the value with its parent node; if it is smaller, we swap the two values.
In writing the API functions for the heap, we can make use of helpful dynamic array functions that we wrote earlier, including the `swap` function we wrote for the dynamic array!

# C implementation of Heap

Here are some useful functions!

```
int indexSmallest(struct dynArray* v, int i, int j)
{
	if (compare(getDynArr(i, j), getDynArr(v, j)) == -1)
	{
		return i;
	}
	return j
}

void swap(struct dynArray* v, int i , int j)
{
	TYPE temp = dynArrayGet(v, i);
	dynArrayPut(v, i, dynArrayGet(v, j));
	dynArrayPut(v, j, temp);
}
```

The `getMin` and `removeMin` functions are pretty straightforward, following the pseudocode:

```
TYPE heapGetFirst(struct dynArray* heap)
{
	assert(dynArraySize(heap) > 0);
	return dynArrayGet(heap, 0);
}

void heapRemoveFirst(struct dynArray* heap)
{
	assert(dynArraySize(heap) > 0);
	int last = dynArraySize(heap) - 1;

	dynArrayPut(heap, 0, dynArrayGet(heap, last));
	dynArrayRemoveAt(heap, last);
	_adjustHeap(heap, last, 0);
}
```

Adding a value to the heap can be done using this function:

```
void heapAdd(struct dynArray* heap, TYPE newValue)
{
	assert(heap != NULL);
	int parent;
	int pos = sizeDynArr(heap);
	addDynArr(heap, newValue); // adds the value to the end

	while(pos != 0)
	{
		parent = (pos - 1)/2;
		if (compare(getDynArr(heap, pos), getDynArr(heap, parent)) == -1)
		{
			//switch current position with parent node
			swapDynArr(heap, parent, pos);
			pos = parent;
		}
		else
		{
			//no more swaps have to be done
			return;
		}
	}
}
```

Preserving the heap order can be done using this handy `adjustHeap` function:

```
void adjustHeap(struct dynArray* heap, int max, int pos)
{
	assert(heap != NULL);
	int leftIdx = pos*2 + 1;
	int rightIdx = pos*2 + 2;	

	if (rightIdx < max)
	{
		int minIdx = indexSmallest(heap, leftIdx, rightIdx);
		if (compare(getDynArr(heap, minIdx), getDynArr(heap, pos)) == -1)
		{
			swap(heap, minIdx, pos);
			adjustHeap(heap, max, minIdx);
		}
	}
	else if (leftIdx < max)
	{
		if (compare(getDynArr(heap, leftIdx), getDynArr(heap, pos)) == -1)
		{
			swap(heap, leftIdx, pos);
			adjust(heap, max, leftIdx);
		}
	}
	else
	{
		return;
	}
}
```

In the first `if` condition, the node has two children.
We get the index of the smallest child using `indexSmallest` and then compare the smallest child to the value at the position `pos`.
If needed, we can swap those values and call `adjustHeap` again recursively.

Similarly, for the second `if` condition, we only have one child node and simply compare that child to the parent.
We can do the same type of checking and if necessary, swap and call `adjustHeap` recursively.

# Priority Queue Implementation

Recall that a priority queue has three operations:

1. `void add(newValue)`
2. `TYPE getMin()`
3. `void removeMin()`

We have 4 (2 of which are technically the same, just in opposite order) implementations for the priority queue, including the heap.
Here are the execution times for these implementations:

|           | Sorted Array | Reverse Sorted Array | Sorted List | Heap     |
|-----------|--------------|----------------------|-------------|----------|
| Add       | O(n)         | O(n)                 | O(n)        | O(log n) |
| getMin    | O(1)         | O(1)                 | O(1)        | O(1)     |
| removeMin | O(n)         | O(1)                 | O(1)        | O(log n) |

We can see that are tradeoffs between the heap and the other implementations.
How do we decide which implementation fits our applications needs?

Well, here's an example.
Consider a case where you have to insert and then remove n elements.

For the sorted vector and list, we need to have $n$ insertions that are $n$ execution time apiece and $n$ removals that are constant time, then we have $n^2 + n$ operations to perform, or in other words, $O(n^2)$.

For the heap, if we have $n$ insertions that are $log(n)$ time apiece and then $n$ removals that are also $log(n)$ time apiece, then our total time is $2nlog(n)$ or in other words, $O(nlogn)$.
So in that reasonable scenario, the heap does better than the sorted vector or list.

# BuildHeap and HeapSort

The last topics of heaps that I wanted to touch on was the idea of building a heap from an arbitrary vector and using a heap to sort values.

The pseudocode for the buildHeap process is:

1. Put the values in a complete binary tree.
2. Calculate first non-leaf node *not* guaranteed to be a proper heap at (size/2 - 1) and call this value i
3. _adjustHeap(heap, max, i)
4. Decrement the index i until we get to the root node

The end product of this will be a heap.

The pseudocode for the heapSort is:

1. Call buildHeap on the data
2. Swap the first and last values
3. adjust heap from index 0 to the last position (note, this doesn't include the last position)
4. Repeat steps 2 and 3, but in decrement the last position until you get to the root

The end product of this process will be an array in reverse sorted array.
Heap sort has some advantages!
For starters, it sorts in-place so there is no need to allocate additional memory.
Both buildHeap and heapSort are $O(n logn)$, so heapSort is comparable to quicksort, merge sort, etc.

---
layout: post
title: "Adventures in Data Structures Vol 8: c u l8r, iter8r"
date: 2020-02-13 010:07:28 +0000
categories: cs
---

Never ceases to amaze me how much a few weeks of college can cover and how much I can forget until the night before an exam.

In these twilight hours, I'd like to take a few minutes and discuss **iterators**.
An iterator is a facilitator object that provides an interface for working with elements in a collection.
This interface is important in data structures developement, since it hides the functionality and inner workings of the container to the user (they don't need to know about linked list or dynamic arrays or any of that stuff!)

An iterator is characterized by four functions:

1. An `init` function to associate it with a container
2. `hasNext` which returns 1 if there is another element in the container
3. `next` returns the current element
4. `remove` removes the element last returned by `next`

In the end use case, we will use these iterators in code blocks like these:

```
dynArrayIterator itr;
TYPE current;
dynArray data;

dynArrayIteratorInit(&data, &itr);
while(dynArryHasNext(&itr))
{
	current = dynArrayNext(&itr);
	// stuff happens here...
}
```

What's important to remember is that the iterator maintains a pointer to a specific element in the collection and `hasNext` and `Next` are used in combination to move that pointer forward.
Additionally, after `remove` is used, the next element in the sequence will be produced.

# Iterator with a Dynamic Array

The iterator for a dynamic array will work by maintaining an index into the array representing the current location, initialized to 0.
Let's start by defining the struct for a `dynArrayIterator` and initializing it.

```
struct dynArrayIterator
{
	struct dynArr* da;
	int currentIndex;
};

void dynArrayIteratorInit(struct dynArr* da, struct dynArrayIterator* itr)
{
	assert(da != NULL);
	assert(itr != NULL);

	itr->da = da;
	itr->currentIndex = -1;
}
```

Notice that in our init function, we set the currentIndex = -1.
Again, this is because the first thing we're going to do is use the `hasNext` and `next` functions which will increment index
Therefore, we want to make sure we're not skipping the first element at index 0.

Let's write the `hasNext` and `next` functions now.

```
int dynArrayIteratorHasNext(struct dynArrayIterator* itr)
{
	assert(itr != NULL);

	int hasNext = 0;
	if(itr->currentIndex < itr->da->size -1)
	{
		hasNext = 1;
	}
	return hasNext;
}

TYPE dynArrayIteratorNext(struct dynArrayIterator* itr)
{
	assert(itr != NULL);
	itr->currentIndex++;
	return itr->da->data[itr->currentIndex];
}
```

For the `remove` function, we will make use of the fact that we already have a handy `dynArrayRemoveAt` function written to take out elements at a specific index.

```
void dynArrayIteratorRemove(struct dynArrayIterator* itr)
{
	assert(itr != NULL);
	dynArrayRemoveAt(itr->da, itr->currentIndex);
	itr->currentIndex--;
}
```

Note that we remove the element at the current index of the iterator and then we **decrement** said index.
We have to decrement in order to avoid skipping elements in the array the next time we call `next`.

# Iterator with a Linked List

Let's implement these functions on a linked list!

Whereas the dynamic array iterator kept track of an index, our linked list iterator will keep track of a current link.
The struct will look like this:

```
struct linkedListIterator
{
	struct linkedList* lst;
	struct dLink* currentLink;
};

void linkedListIteratorInit(struct linkedList* lst, struct linkedListIterator* itr)
{
	itr->lst = lst;
	itr->currentLink = lst->lst->frontSentinel;
}
```

The above explanation of the functions was a little confusing, but once we demonstrate how to implement this in code, it will hopefully become more clear.
Let's start with the `hasNext` function.

```
int linkedListIteratorHasNext(struct linkedListIterator* itr)
{
	assert(itr != NULL);
	int hasNext = 0;
	if(itr->currentLink->next != itr->lst->backSentinel)
	{
		hasNext = 1;
	}
	return hasNext;
}
```

All the `hasNext` function really does is check to see if the pointer `currentLink->next` is equal to the back sentinel.
If it is, then there are no more elements and we return 0, otherwise we return 1.

Nice and easy :)

Let's do another one, the `next` function.

```
TYPE linkedListIteratorNext(struct linkedListIterator* itr)
{
	itr->currentLink = itr->currentLink->next;
	return int->currentLink->value;
}
```

We can see here that `next` moves the pointer forward in the first line, then returns whatever value is in that link.

For the `remove` function, we are going to make use of the `_removeLink` function we wrote for our doubly linked lists.
We have to keep in mind that after the `remove` function is called, the pointer `itr->currentLink` should on the link **before** the link that was removed.
If we move it forward, then we will actually be skipping a link because `hasNext` and `next` always move the pointer forwards from whatever the current node is.

```
void linkedListIteratorRemove(struct linkedListIterator* itr)
{
	struct dLink* temp = itr->currentLink;
	itr->currentLink = itr->currentLink->prev;

	_removeLink(itr->lst, temp);
}
```

We use the classic little trick of defining a `temp` variable and then freeing it.
`itr->currentLink` essentially moves backwards one link to `itr->currentLink->prev`, and the handy `_removeLink` function cleans up all our pointers for us.

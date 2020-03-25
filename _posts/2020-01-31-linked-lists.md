---
layout: post
title: "Adventures in Data Structures Vol 4: Linked Lists"
date: 2020-01-31 010:07:28 +0000
categories: cs
---

Welcome welcome to another volume of my misguided adventures in data structures.
Today, I would like to talk about the classic linked list, specfically the doubly linked list, and how we can use it to implement a deque.

## Doubly Linked List Implementation

To start, **what is a linked list?**
The past few posts have all centered around a data structure called the dynamic array.
We used the dynamic array to implement different abstract data types, like bags and stacks.
A linked list is a different kind of data structure that has certain advantages and disadvantagesover the dynamic array.

Let's first understand the logic of a linked list.
Where as a dynamic array represents a contiguous block of memory that holds values together, a linked list is more like a chain of disparate links that just point to one another.
In C, the linked list struct is nothing more than a bunch of node structs which look like this:

```
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
}
```

Each link essentially has three components: a value that it holds, a pointer to the next link in the linked list, and a pointer to the previous link in the linked list.
When we want to *traverse* a linked list, we simply start on one end and keep following the links from the next one to the next one.
In a classical linked list, one end is designated as the starting link.

In what's called a doubly linked list, we can start at either the front or the back of the linked list.
That's what we'll be discussing today, since it's slightly more interesting (and we need a doubly linked list to implement a deque abstract data type!)

```
struct LinkedList
{
	struct Link* frontSentinel;
	struct Link* backSentinel;
	int size;
}
```

The special links on ends of the doubly linked list are called **sentinels** and have no value.
In fact, they're not technically considered *part* of the data-bearing component linked list.
Their only job is to point to the first and last actual links within the list.
The linked list also has an integer to keep track of size.

Let's write a function to initialize everything in the doubly linked list.

```
static void init(struct LinkedList* list)
{
	list->frontSentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->frontSentinel != NULL);
	
	list->backSentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->backSentinel != NULL);
	
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->size = 0;
}

sturct LinkedList* linkedListCreate()
{
	struct LinkedList* list = malloc(sizeof(struct LinkedList));
	init(list);
	return list;
}
```

This function creates our front and back sentinel and has them point to one another.
Also since there is no data in the list yet, we set the size equal to 0.

One of the great advantages of linked lists is that adding a new value (aka adding a new link) will always be O(1) since there is no requirement to shift elements around in a contiguous block of memory.
All that we have to do is configure some pointers to point to our new link!
Here is a function that will create a new link containing a given value and add it before a link in the specified linked list.

```
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE val)
{
	assert(list != NULL);
	
	struct Link* newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != NULL);
	
	newLink->value = val;
	newLink->next = link;
	newLink->prev = link->prev;
	
	link->prev->next = newLink;
	link->prev = newLink;

	list->size++;
}
```

There's a couple parts to unpack here.
The first and the simplest is just allocating the space for the new link and setting its value.
Then in the pointers for the new link, since we are placing it *before* the specified existing link, we need `newLink->next = link;`.
Similarly, we need the new link to also point to the current link's previous link, so we need `newLink->prev = link->prev;`
Think of it like we smushing this new link between two occupied seats on a crowded subway car.
This new link will now be pointing to the two existing links!

Next we have to make sure that the previous link of the existing link also points to our new link.
That is why we need `link->prev->next = newLink;`.
We also need the existing link to point back to our new link, so let's add `link->prev = newLink;`
Finally, we increase the linked list's total size by 1 and we've successfully added a link to our doubly linked list!

The `removeLink` function is slightly simpler, all we have to do is configure the pointers of the surrounding links to skip over the link we are removing.
Then we free that link.

```
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != NULL);
	link->prev->next = link->next;
	link->next->prev = link->prev;
	free(link);
	list->size--;
}
```

The input `link` is the link in the list we are getting rid of, and we are simply *skipping* over it now in the linked list!
Then we free `link` and decrement the size by 1.
A nice straightforward function :)

Let's write two more useful functions for implementing a doubly linked list: `isEmpty` and `Print`.
`isEmpty` will return 1 if the linked list is empty and `Print` will... well... print the values in the linked list.

```
int linkedListIsEmpty(struct LinkedList* deque)
{
	assert(deque != NULL);	
	return deque->size == 0;
}

void linkedListPrint(struct LinkedList* deque)
{
	assert(deque != NULL);
	struct Link* current;

	if (deque->size > 0)
	{
		current = deque->frontSentinel->next;
		while (current != deque->backSentinel)
		{
			printf("%d\n", current->value);
			current = current->next;
		}
	}
	else
	{
		printf("List is empty\n");
	}
}
```

The `isEmpty` is fairly straightforward, but `Print` requires using a pointer (here I called it $current$) to a link and then while iterating through the linked list, moving the pointer along and printing the value.

## Implementing a Deque using a Doubly Linked List

The **deque** (pronounced 'deck' and not 'dee queue', but hey, it's a free country) is very similar to a stack but instead of only being able to add and pop from one end, you can add and pop from both ends.
It's confusing that it's not more like a queue given that the names are so similar, but I'm not in charge of the naming.

Using the `add` function, we can write some convenient wrapper functions for the deque implementation.

```
void linkedListAddFront(struct LinkedList* deque, TYPE value)
{
	assert(deque != 0);
	addLinkBefore(deque, deque->frontSentinel->next, value);
}

void linkedListAddBack(struct LinkedList* deque, TYPE value)
{
	assert(deque != 0);
	addLinkBefore(deque, deque->backSentinel, value);
}
```

We should also have two `remove` functions for the deque, which again is pretty easy given the helpful doubly linked list functions we've written already.
Remember that a deque is like a double ended stack, so we can only remove from the front and the back.

```
void linkedListRemoveFront(struct LinkedList* deque)
{
	assert(deque != NULL);
	removeLink(deque, deque->frontSentinel->next);
}

void linkedListRemoveBack(struct LinkedList* deque)
{
	assert(deque != NULL);
	removeLink(deque, deque->backSentinel->prev);
}
```

Similar to `pop` in the stack implementation, we can look at the front and rear elements of the deque (but not remove them!) with these functions:

```
TYPE linkedListFront(struct LinkedList* deque)
{
	assert(deque != 0);
	assert(!linkedListIsEmpty(deque));
	return deque->frontSentinel->next->value;
}

TYPE linkedListBack(struct LinkedList* deque)
{
	assert(deque != 0);
	assert(!linkedListIsEmpty(deque));
	return deque->backSentinel->prev->value;
}
```

Finally, let's write a function for destroying the linked list.
Destroying a linked list is easy now with this `linkedListIsEmpty` function.

```
void linkedListDestroy(struct LinkedList* list)
{
	assert(list != NULL);
	while(!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}

	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
	list = NULL;
}
```

## Bag Implementation using a Doubly Linked List

As a bonus, let's also implement a bag using a doubly linked list.
You may remember that a bag has 3 basic functions:

1. `add`
2. `remove`
3. `contains`

We have already implemented `add` with our previous functions, in fact, we can use either of the add functions we wrote for the deque implementation.

Here I basically just rewrote `addFront`, just giving it a different name.

```
void linkedListAdd(struct LinkedList* bag, TYPE val)
{
	assert(bag != NULL);
	addLinkBefore(bag, bag->frontSentinel->next, value);
}
```

The `remove` and `contains` function however still need to be implemented.
They are a little tricky, but we should be able to tackle them!

Let's begin by writing the `contains` function.

```
int linkedListContains(struct LinkedList* bag, TYPE value)
{
 	assert(bag != NULL);
	struct Link* current = bag->frontSentinel->next;

	while(current != bag->backSentinel)
	{
		if(EQ(current->value, val))
		{
			return 1;
		}

		current = current->next;
	}
	return 0;
}
```

Note the use of a `while` loop to iterate through the entire linked list.
I also make use of a function I defined in the preprocessor `EQ(a, b)` which returns 1 if the elements are equal and 0 if they are not.
Essentially we iterate through until we find the value we are looking for.

If we find it, we return a 1.
If we reach the end of the linked list and don't find the value, we return a 0.
Good stuff!

Let's implement the `remove` function next.
It's pretty close in terms of structure.

```
void linkedListRemove(struct LinkedList* bag, TYPE value)
{
	assert(bag != NULL);
	struct Link* current = bag->frontSentinel->next;
	
	while(current != bag->backSentinel)
	{
		if(EQ(current->value, val))
		{
			removeLink(bag, current);
			return;
		}
		current = current->next;
	}

	printf("Value not found\n");
	return;
}
```

Note that in this implementation of `remove`, we remove the first instance of the value that we find, **not** all the links in the list that have that value.
That's why we call `return;` after the `removeLink(bag, current);` line.
If we iterate through the entire list and don't find the value we are looking for, this function prints that the value was not in the list and exits.
I suppose that we don't actually need the last `return;`, but I kind of like the semantic finality of having a return there.

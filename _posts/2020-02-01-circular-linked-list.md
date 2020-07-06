---
layout: post
title: "Adventures in Data Structures Vol 5: In Circles"
date: 2020-02-01 010:07:28 +0000
categories: cs
---

Hi again, welcome to another episode of my suffering in CS261 at Oregon State University :)

Today, I actually wanted to talk about a pretty fun (but frustrating) problem: implementing a circular doubly linked list in C!

# A Circular Doubly Linked List???

So we implemented a doubly linked list in the prior post.
What is the difference between that and a circular doubly linked list?

As the name implies, the circular doubly linked list is *circular*, which is to say that there is **one sentinel** as opposed to two, and the single sentinel points to both the beginning and end of the circular linked list.
If you started at the sentinel (or theoretically any link for that matter) and started traversing in either direction, eventually, you would get back to where you started!

# Ok... how do we do this?

Let's define the structs first:

{% highlight c %}
struct Link 
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

struct circularList
{
	int size;
	struct Link* sentinel;
}; 
{% endhighlight %}

Pretty familiar stuff.
In fact, this is "simpler" than the doubly linked list we already implemented since we only have to deal with one sentinel!

Initializing and creating the circular linked list is also pretty familiar:

{% highlight c %}
static void inti(struct CircularList* deque)
{
	assert(deque != NULL);
	struct Link* sentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(sentinel != NULL);
	deque->sentinel = sentinel;

	deque->sentinel->prev = deque->sentinel;
	deque->sentinel->next = deque->sentinel;

	deque->size = 0;
}

struct CircularList* circularListCreate()
{
	struct CircularList* deque = malloc(sizeof(struct CircularList));
	init(deque);
	return deque;
}
{% endhighlight %}

The key difference here with the circular doubly linked list is that the single sentinel begins by pointing **to itself** in both directions.
So if you go to the `next` or `prev` pointer, you end up back at the sentinel.

Let's write a function to create a link (**but not add it**) to the circular linked list.

{% highlight c %}
static struct Link* createLink(TYPE val)
{
	struct Link* newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != NULL);

	newLink->value = value;
	newLink->next = NULL;
	newLink->prev = NULL;
	
	return newLink;
}
{% endhighlight %}

Now that we have this function, we can write a general function to add a new link to the circular linked list.
We will call this function `addLinkAfter`, which will create a new link containing a specified value and add it *after* a specified link in the list.

{% highlight c %}
static void addLinkAfter(struct CircularList* deque, struct Link* link, TYPE value)
{
	assert(deque != NULL);
	assert(link != NULL);
	
	struct Link* newLink = createLink(value);
	newLink->prev = link;
	newLink->next = link->next;

	link->next->prev = newLink;
	link->next = newLink;

	deque->size++;
}
{% endhighlight %}

The first chunk of code is creating a new link and specifying the pointers of the new link so that it points backwards to the exisiting link we are adding after and points forwards to the existing links `next` link.

The second chunk is making sure that the currently existing link and the current link that is after it play nicely with the new link and point towards it in the circular linked list.

So far, pretty straightforward!

The last function we want to implement is the `remove` function.
This function is a little spicier.

{% highlight c %}
static void removeLink(struct CircularList* deque, struct Link* link)
{
	assert(deque != NULL);
	assert(link != NULL);
	assert(deque->size > 0);

	struct Link* tmp = link;
	
	tmp->prev->next = link->next;
	tmp->next->prev = link->prev;
	free(link);

	deque->size--;
}
{% endhighlight %}

A practice that I have been using in CS261 is to create temporary pointer variables such as `tmp` here that allows me to manipulate values while still having a copy of the original (since C is pass by value).
I could have just skipped the line defining `tmp` and just used `link` instead for moving the pointers, but in more complicated functions I think this runs the risk of changing something you don't necessarily want to change.

Finally, let's write a function to destroy the circular list after we are done with it:

{% highlight c %}
void circularListDestroy(struct CircularList* deque)
{
	assert(deque != NULL);
	struct Link* current = deque->sentinel->next;

	while(deque->size > 0)
	{
		struct Link* tmp = current;
		current = current->next;
		removeLink(deque, tmp);
	}

	free(deque->sentinel);
}
{% endhighlight %}

Here is an example of where it is helpful to have a `tmp` variable defined since we don't want to call `removeLink` on our `current` pointer since that will free all the memory, including the pointer to the next link.
If we instead keep `current` to keep iterating along the circular list and `tmp` for removal and freeing memory and make sure the `current` is always ahead of `tmp`, we won't run into this issue.

Finally, let's write two useful helper functions like we did for the regular doubly linked list: `isEmpty` and `Print`:

{% highlight c %}
int circularListIsEmpty(struct CircularList* deque)
{
	assert(deque != NULL);
	return deque->size == 0;
}

void circularListPrint(struct CircularList* deque)
{
	assert(deque != NULL);
	struct Link* current = deque->sentinel->next;

	if(current == deque->sentinel)
	{
		printf("Circular linked list is empty\n");
		return;
	}

	printf("Printing circular linked list...\n");
	while(current != deque->sentinel)
	{
		printf("%f\n", current->value);
		current = current->next;
	}
}
{% endhighlight %}

Instead of using an `assert` in the `Print` function, I instead opted to output a message that the list was empty and exit.
Some implementations might be different though!

We've finished implementing all the basic functions of the circular linked list!

## Deques with a Circular Doubly Linked list

As we've done for previous data structures, we can now use the circular linked list to implement some abstract data structures.A
Let's start off by implementing a deque.
Recall that the deque needs several functions:

+ `addFront`
+ `addBack` 
+ `removeFront`
+ `removeBack`
+ `Front` (just look at the front element)
+ `Back` (just look at the back element)

Thankfully, most of these are pretty easy since we can just use the functions we've already written!

{% highlight c %}
void circularListAddFront(struct CircularList* deque, TYPE value)
{
	assert(deque != NULL);
	addLinkAfter(deque, deque->sentinel, value);
}

void circularListAddBack(struct CircularList* deque, TYPE value)
{
	assert(deque != NULL);
	addLinkAfter(deque, deque->sentinel->prev, value);
}
{% endhighlight %}

For the `add` functions, the positioning is all based around the sentinel.
When we add to the front of the deque we are adding a link right after our sentinel.
When we add to the back, we are adding a link right after the previous link of the sentinel.

We can follow the same logic for the other functions!

{% highlight c %}
TYPE circularListFront(struct CircularList* deque)
{
	assert(deque != NULL);
	return deque->sentinel->next->value;
}

TYPE circularListBack(struct CircularList* deque)
{
	assert(deque != NULL);
	return deque->sentinel->prev->value;
}

void circularListRemoveFront(struct CircularList* deque)
{
	assert(deque != NULL);
	assert(deque->size > 0);
	removeLink(deque, deque->sentinel->next);
}

void circularListRemoveBack(struct CircularList* deque)
{
	assert(deque != NULL);
	assert(deque->size > 0);
	removeLink(deque, deque->sentinel->prev);
}
{% endhighlight %}

The key bit with the remove functions is that we have to make sure the size of the circular linked list is greater than 0.
Otherwise, we'll end up removing the sentinel itself and that would be bad news for us!

## Reversing a circular doubly linked list

Now we get to the **real** fun part: reversing the list!

What is our goal with this?
We know that with our circular linked list, if we start in one direction from the sentinel, say forward, we can access all the elements in the list in a certain order before returning back to the sentinel.
After we reverse it, now if we travel in the *opposite direction*, we'll now access the elements in the same order as when we traversed it forwards.

This sounds tricky because it is.
But it's not impossible, and the function itself is actually pretty short!
The trick is to define a `tmp` and a `current`, kind of like what we did when we wrote the `destroy` function above.
This time, `tmp` stays one link **ahead** of current.

As we traverse the circular list, our goal at every link (defined as `current`) is to switch the `prev` and `next` pointers with one another.
However, if we don't have another pointer variable like `tmp`, we'll end up overwriting pointers in the link that we need.

After defining `current` to point to the current link, the basic flow for each link is this:

1. Define `tmp` to be the pointer `current->next`
2. Change `current->next` to be `current->prev`
3. Change `current->prev` to be `tmp` which is equal to the address `current->next`
4. Move on to the next link by setting `current` to `tmp`

Steps 2 and 3 are what switch the `next` and `prev` pointers for each link.
In code, these steps look like:

{% highlight c %}
tmp = current->next;
current->next = current->prev;
current->prev = tmp;

current = tmp;
{% endhighlight %}

Now all the function is inserting this code block inside a `while` loop so we can iterate through the entire circular list!

{% highlight c %}
void circularListReverse(struct CircularList* deque)
{
	assert(deque != NULL);
	assert(deque->size > 0);

	struct Link* current = deque->sentinel;
	struct Link* tmp = current->next;
	
	while(tmp != deque->sentinel)
	{
		tmp = current->next;
		current->next = current->prev;
		current->prev = tmp;

		current = tmp;
	}
}
{% endhighlight %}

Easy peeze when you finally look at it :)


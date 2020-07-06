---
layout: post
title: "Adventures in Data Structures Vol 6: Qup Stackin'"
date: 2020-02-10 010:07:28 +0000
categories: cs
---

Hello me, nice to see you again.
In case you had forgotten about the joys of implementing a **stack using two queues**, let' me offer you some *pointers* (little C joke for you there).

Stacks and queues are already familiar concepts at this point, and you probably already know the difference between them.
Namely, a stack is a FIFO data structure while a queue is LIFO.
Previously we've implemented a stack using a dynamic array and a linked list, but how about implementing a stack using two queues?

The advantage of using queues to implement a stack is that a queue has O(1) access to the front, so the `pop` and `top` methods of the stack are actually very easy, compared to say a stack implementation with a normal singly linked list.

## First thing's first: A queue using a singly linked list

This implementation is pretty tricky at first, so let's start by just defining our structs:

{% highlight c %}
struct Link
{
	TYPE value;
	struct Link* next;
};

struct Queue
{
	struct Link* head;
	struct Link* tail;
};

struct Stack
{
	struct Queue* q1;
	struct Queue* q2;
};
{% endhighlight %}

We have a couple building blocks here.
We have queues which are composed of single links and two pointers, one sentinel link in the front and another pointer to the last link in the back.
Then the stack itself is made of two queues, which we will explain why further down.

Initializing the queues is somewhat familiar from previous work that we've done!

{% highlight c %}
void listQueueInit(struct Queue* queue)
{
	assert(queue != NULL);
	struct Link* sentinel = (struct Link)*malloc(sizeof(struct Link));
	assert(sentinel != NULL);

	queue->head = sentinel;
	queue->tail = sentinel;
	
	sentinel->next = NULL;
}

struct Queue* listQueueCreate()
{
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	listQueueInit(queue);

	return queue;
}
{% endhighlight %}

When we create a queue, our `head` and `tail` pointers both go to the sentinel since our queue is empty.
Similarly to before, the `next` pointer in the sentinel starts at pointing to $NULL$.

Let's implement some more functions for the queue!
We haven't explored this yet in this series, but now is as good as any to start.

A queue has a couple basic functions:
+ **Enqueuing** (for us, that's adding a new link at the end of the linked list)
+ **Dequeuing** (this would be removing the link right after the sentinel)
+ **Front** (returning the value right after the sentinel node)

Let's start by writing our `enqueuing` function:

{% highlight c %}
void listQueueAddBack(struct Queue* queue, TYPE value)
{
	assert(queue != NULL);
	struct Link* newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != NULL);
	
	queue->tail->next = newLink;
	queue->tail = newLink;

	newLink->value = value;
	newLink->next = NULL;
}
{% endhighlight %}

Pretty straightforward function, just need to make sure that our queue's tail pointer now points to this new link and that the current last link's next pointer also points to the new link.

Let's take a look at the `dequeuing` function now which will remove and free the link after the sentinel.
The actual output of this function will be the value that we are removing from the queue, which will come in handy later.

{% highlight c %}
TYPE listQueueRemoveFront(struct Queue* queue)
{
	assert(queue != NULL);
	assert(queue->head != queue->tail);

	struct Link* rm = queue->head->next;
	
	if(rm == queue->tail)
	{
		queue->tail = queue->head;
		queue->head->next = NULL;
	}
	else
	{
		queue->head->next = queue->head->next->next;
	}
	
	TYPE val = rm->value;
	free(rm);

	return val;
}
{% endhighlight %}

One important part is defining pointer variable `rm`.
If the queue only has one link, then `rm` is that one link and removing it is essentially making queue's tail pointer equal to the head pointer, which is the queue's sentinel.
We then free the first link.

The other is making sure to properly handle the case when there is only one link in the list.
In that case, we have to make sure that the tail pointer and the head pointer are equal to each other.
We *also* have to make sure that the pointer `queue->head->next = NULL` like in the initialized linked list queue.

The `Front` function is pretty straightforward.

{% highlight c %}
TYPE listQueueFront(struct Queue* queue)
{
	assert(queue != NULL);
	assert(queue->head->next != NULL);

	return queue->head->next->value;
}
{% endhighlight %}

So are the `isEmpty` and `Destroy` functions!

{% highlight c %}
int listQueueIsEmpty(struct Queue* queue)
{
	assert(queue != NULL);
	if(queue->head->next == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void listQueueDestroy(struct Queue* queue)
{
	assert(queue != NULL);
	
	while(!listQueueIsEmpty(queue))
	{
		listQueueRemoveFront(queue);
	}

	free(queue->head);
	free(queue);
	queue = NULL;
}
{% endhighlight %}

Note that even though `Remove` return a value of TYPE, we don't necessarily have to capture that value using some throwaway variable.

Now we are ready to start implementing the stack!

## 2 Queues, 1 Stack

The basic idea is that we have one queue which holds all the values and then another queue which we will use as a container to help move elements around in the first queue.
Here's the general idea:

+ When we add an element to the stack, we want to add it on queue 1. However, since queues are FIFO and stacks have to be FIFO, we basically have to remove all the existing elements in queue 1 first and copy them over to queue 2 in order.
+ Once queue 1 is empty, we add the new element to it
+ We then take queue 2 and empty it, taking all the values we remove and sticking them on the back end of queue 1.

When the two queues work together, the first queue will behave like a stack!
And since it's still a stack, `pop` and `top` are O(1).

Let's start by writing the function to initialize the stack, which again is just two queues stuck together in a struct.

{% highlight c %}
struct Stack* listStackFromQueuesCreate()
{
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	assert(stack != NULL);

	struct Queue* q1 = listQueueCreate();
	struct Queue* q2 = listQueueCreate();

	stack->q1 = q1;
	stack->q2 = q2;

	return stack;
}
{% endhighlight %}

Let's write some other basic functions: `Destroy` and `isEmpty`.
These are pretty easy since it's basically just doing functions on queues which we've already written!

{% highlight c %}
void listStackDestroy(struct Stack* stack)
{
	assert(stack != NULL);
	assert(stack->q1 != NULL && stack->q2 != NULL);

	listQueueDestroy(stack->q1);
	listQueueDestory(stack->q2);
	
	free(stack);
	stack = NULL;
}

int listStackIsEmpty(struct Stack* stack)
{
	assert(stack != NULL);
	return listQueueIsEmpty(stack->q1);
}
{% endhighlight %}

So now we get into some spicier stuff.
In the pseudocode I wrote above, I said that we would copy over elements from queue 1 and put them in queue 2 when we wanted to add a new element to the top of the stack.
A slightly easier way to do this is to just have a function that swaps the two queues with each other.

{% highlight c %}
void listSwapStackQueue(struct Stack* stack)
{
	assert(stack != NULL);
	struct Queue* tmp = stack->q1;
	stack->q1 = stack->q2;
	stack->q2 = tmp;
}
{% endhighlight %}

`Push` will be our most complex function (but that means we're almost done!)

Remember that we are basically treating queue 1 as our stack, so in the end of this push, we should have the new value at the front of queue 1.

To do this, we actually begin by pushing the new value to queue 2 (which is empty) and then moving everything from queue 1 to queue 2.

We will then use the `swap` function **AFTER** we have added the new value to queue 2 **AND** have copied everything from queue 1 over to queue 2.
After we swap queue 2 and queue 1, queue 1 will have all the elements and queue 2 will be empty.

{% highlight c %}
void listStackPush(struct Stack* stack, TYPE value)
{
	assert(stack != NULL);
	
	if(listStackIsEmpty(stack) == 1)
	{
		listQueueAddBack(stack->q1, value);
	}
	else
	{
		listQueueAddBack(stack->q2, value);
		while(!listQueueIsEmpty(stack->q1))
		{
			TYPE tmp = listQueueRemoveFront(stack->q1);
			listQueueAddBack(stack->q2, tmp);
		}
		listSwapStackQueue(stack);	
	}
}
{% endhighlight %}

Our last functions are `pop` and `top`, but like I said, those are easy!

{% highlight c %}
TYPE listStackPop(struct Stack* stack)
{
	assert(stack != NULL);	
	assert(!listQueueIsEmpty(stack));
	
	return listQueueRemoveFront(stack->q1);
}

TYPE listStackTop(struct Stack* stack)
{
	assert(stack != NULL);
	assert(!listQueueIsEmpty(stack));
	
	return listQueueFront(stack->q1);
}
{% endhighlight %}

We finally made it!

You can test the above stack implementation using this code provided by the Oregon State Department of Computer Science or something like that.

{% highlight c %}
void assertTrue(int pred, char* msg)
{
	printf("%s: ", msg);
	if(pred)
		printf("\tPASSED\n");
	else
		printf("\tFAILED\n");
}

int main()
{
	struct Stack* s = listStackFromQueuesCreate();
	assertTrue(listStackIsEmpty(s) == 1, "stackIsEmpty == 1");

	printf("\npushing 4, 5, -300...\n");
	printf("test\n");
	listStackPush(s, 4);
	printf("Pushed 1\n");
	listStackPush(s, 5);
	printf("Pushed 2\n");
	listStackPush(s, -300);
	printf("Pushed 3\n");

	assertTrue(listStackIsEmpty(s) == 0, "stackIsEmpty == 0");
	assertTrue(listStackPop(s) == -300, "\npopping; val == -300");
	assertTrue(listStackPop(s) == 5, "popping; val == 5");
	assertTrue(listStackTop(s) == 4, "top val == 4\t");
	assertTrue(listStackPop(s) == 4, "popping; val == 4");
	assertTrue(listStackIsEmpty(s) == 1, "stackIsEmpty == 1");
	// listStackPop(s); 	// should fail assert
	// listStackTop(s); 	// should fail assert

	printf("\npushing 0-9...\n");
	for(int i = 0; i < 10; i++) {
		listStackPush(s, i);
	}
	assertTrue(listStackTop(s) == 9, "top val == 9\t");

	listStackDestroy(s);

	return 0;
}
{% endhighlight %}

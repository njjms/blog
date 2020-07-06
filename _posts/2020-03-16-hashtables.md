---
layout: post
title: "Adventures in Data Structures Vol 13: Hash Tables (more like Ca$h Tables)"
date: 2020-03-16 010:07:28 +0000
categories: cs
---

# Introduction to Hashes

In today's post, I wanted to go over the basics of hash tables and how we implement them in C.
They're a super useful data structure that appear a lot, so this is really one the building blocks for advanced applications.

So far, the most well rounded data structure we've explored for adding, removing, and checking data is the AVL tree which has $O(log n)$ performance for all those operations.
However, is there a data structure that can perform even better?
If we think back to our first lecture, arrays have some really nice properties, one of them being random access.
What if instead of the positions of values inside the array being based on consecutive integers, it was instead based on the value itself?

That is the basic idea of hash tables.
It is essentially based on an array except the position where a value is stored is dictated on a **hash function**.
The **hash function** takes input (like a key or value) and returns an integer index which we can then use as the location to store the value.

**Hash functions** should satisfy the following properties:

+ Minimal collisions (not a lot of inputs should map to the same index)
+ Uniformly distributed hash output
+ Repeatable (the same input again will produce the same hash output)
+ Fast! (constant time to compute)

Creating a hash function is really an art, but common hash functions can be based around ideas like mapping chars to numbers, using aggregate functions, shifting numbers by certain values, casting types to other types, etc.

What are the benefits of using hash functions?
Assuming that computing a hash function is $O(1)$, then all map/bag operations theoretically have constant execution time!

Think about a common example, such as the `contains` function.
Normally in an unordered dynamic array or linked list bag, this would be an $O(n)$ operation.
However, for a hash table, it is $O(1)$ since all we have to do is hash the value we are searching for and then check that position to see if it's equal!

There are two different methods for implementing hash tables that I wanted to go over: open address hashing and chaining.
Each represent a different way to dealing with inevitable collisions.

# Open Address Hashing

Open address hashing handles collisions by *probing* forward in the until we find an open spot and placing the new value there.
The initial hash output is just the initial index to try.
If we reach the end, we loop back to the beginning of the array and continue searching.

The `contains` operation similarly starts looking at the initial hashing index and proves forward until either the value is found **or** an empty location is found.

The `removal` operation is a little tricky, because removing a value can mess up the contains operation if we're not careful.
We either disallow removals or use a *tombstone special value* which means that the contains operation can skip over it and the add operation can paste over it.

For open address hashing, the execution time is:

+ Worst case: $O(n)$
+ Best case: $O(1)$
+ Average case: $O\left(\frac{1}{1-\lambda}\right)$ where $\lambda$ is the load factor = (# of elements/size of table)

If the load factor gets too big, this means we need to make a new array with double capacity. 

The implementation of open address hashing in C is provided below:

{% highlight c %}
struct openHashTable {
	TYPE** table;
	int tablesize;
	int count;
};

void initOpenHashTable(struct openHashTable* ht, int size)
{
	int i;
	assert(size > 0);
	ht->table = (TYPE**)malloc(size*sizeof(TYPE *));
	assert(ht->table != NULL);

	for (i = 0; i < size; i++)
	{
		//initialize each entry as null
		ht->table[i] = 0; 
	}

	ht->tablesize = size;
	ht->count = 0;
}

int openHashTableSize(struct openHashTable* ht)
{
	return ht->count;
}

void _resizeOpenHashTable(struct openHashTable* ht)
{
	int i;
	int oldSize = ht->tablesize;
	int newSize = 2*oldSize;
	TYPE** temp = ht->table;
	initOpenHashTable(ht, newSize);

	for (i = 0; i < oldSize; i++)
	{
		if (temp[i] != NULL)
		{
			openHashTableAdd(ht, temp[i]);
		}
	}
	free(temp);
}
{% endhighlight %}

The main operations we have to implement are `add` and `contains` since we're avoiding the `remove` operation.

{% highlight c %}
void openHashTableAdd(struct openHashTable* ht, TYPE* newValue)
{
	ht->count++;
	if((ht->count/(double)ht->tablesize) > .75)
	{
		_resizeOpenHashTable(ht);
	}

	int idx = HASH(newValue) % ht->tablesize;
	if (idx < 0)
	{
		idx += ht->tablesize;
	}

	while (idx >= 0)
	{
		if (idx == ht->tablesize)
		{
			idx = 0;
		}

		if (ht->table[idx] == 0)
		{
			ht->table[idx] = newValue;
			idx = -1;
		}
		else
		{
			idx++;
		}
	}
}
{% endhighlight %}

The `idx = -1;` line breaks the loop.
We could have also just called `return`.

The `contains` function is provided below:

{% highlight c %}
int openHashTableContains(struct openHashTable* ht, TYPE newValue)
{
	int idx = HASH(newValue) % ht->tablesize;
	if (idx < 0)
	{
		idx += ht->tablesize;
	}

	while (ht->table[idx] != NULL)
	{
		if (compare(ht->table[idx], newValue) == 0)
		{
			return 1;
		}
		idx++;

		if (idx == ht->tableSize)
		{
			idx = 0;
		}
	}
	return 0;
}
{% endhighlight %}

# Chaining Hashing

Also called buckets, this strategy basically means maintaining a linked list at each table entry.
The load factor $\lambda = \text{average # of elements in each bucket}$

For chaining, the execution time is:

+ Worst case: $O(n)$
+ Best case: $O(1)$
+ Average case: $O(\lambda)$ where $\lambda$ is the load factor

Each operation on the hash table is divided into two steps.
First, the element is hashed and the remainder taken after dividing by the table size which returns the table index.
Second, the corresponding linked list is examined.

{% highlight c %}
struct hlink {
	TYPE value;
	struct hlink* next;
};

struct hashTable {
	struct hlink** table;
	int tablesize;
	int count;
};

void initHashTable(struct hashTable* ht, int size)
{
	assert(size > 0);

	ht->table = (struct hlink**)malloc(sizeof(struct hlink*)*size);
	assert(ht->table != NULL);

	for (int i = 0; i < size; i++)
	{
		ht->table[i] = 0;
	}
	ht->tablesize = size;
	ht->count = 0;
}

int hashTableSize(struct hashTable* ht)
{
	return ht->count;
}

void resizeTable(struct hashTable* ht)
{
	struct hashTable* newTable;
	initHashTable(newTable, ht->tablesize*2);
	struct hlink* current;

	for (int i = 0; i < ht->tablesize; i++)
	{
		current = ht->table[i];
		while (current != NULL)
		{
			hashTableAdd(newTable, current->value);
			current = current->next;
		}
	}

	free(ht->table);
	free(ht);
	ht = newTable;
	newTable = 0;
}
{% endhighlight %}

Let's implement the `add` function first!

{% highlight c %}
void hashTableAdd(struct hashTable* ht, TYPE newValue)
{
	int hashIndex = HASH(newValue) % ht->tablesize;
	if (hashIndex < 0)
	{
		hashIndex += ht->tablesize;
	}

	struct hlink* newLink = (struct hlink*)malloc(sizeof(struct hlink));
	assert(newLink != NULL);

	newLink->value = newValue;
	newLink->next = ht->table[hashIndex];
	ht->table[hashIndex] = newLink;

	ht->count++;
	if ((ht->count)/(double)ht->tablesize) > 8.0)
	{
		_resizeHashTable(ht);
	}
}
{% endhighlight %}

Notice that the `add` operation switches the head of the linked list and the new link so that the new link is at the head of the linked list!

Let's do the `contains` function next.

{% highlight c %}
int hashTableContains(struct hashTable* ht, TYPE testElement)
{
	assert(ht != NULL);
	assert(value != 0);
	
	int hashIndex = HASH(newValue) % ht->tablesize;
	struct hlink* current = ht->table[hashIndex];

	while (current != NULL)
	{
		if(strcmp(current->value, testElement) == 0)
		{
			return 1;
		}
		current = current->next;
	}
	return 0;
}
{% endhighlight %}

Finally, let's do the `remove` function!

{% highlight c %}
void hashTableRemove(struct hashTable* ht, TYPE testElement)
{
	int hashIndex = HASH(newValue) % ht->tablesize;
	if (hashIndex < 0)
	{
		hashIndex += ht->tablesize;
	}

	struct hlink* current = ht->table[hashIndex];
	struct hlink* prev = 0;

	while (current != NULL)
	{
		if (strcmp(current->value, testElement) == 0)
		{
			if (prev == 0)
			{
				ht->table[hashIndex] = current->next;
			}
			else
			{
				prev->next = current->next;
			}

			free(current);
			ht->count--;
			return;
		}
	prev = current;
	current = current->next;
	}
}
{% endhighlight %}

The `remove` function has a special case when the `prev` node is `NULL`.
In that case, the value we want to remove is at the first node in the list and the linked list head is the set to `current->next`.
If that's not the case, then `prev->next` is set to `current->next` so that it skips `current`.

# Sorting with Hash Functions

Hash-like sorting can be used in certain contexts!

One useful example of this is the *counting sort* in which we have a bunch of integers from a limited range (say, 0 through 20).
The general idea is that:

+ Create buckets for each unique possible value
+ Iterate through all the elements we want to sort, incrementing the appropritae buckets as we go
+ Our output is a printed enumerated list of all the buckets in order, which will automatically be sorted

The C code for something like this would look like:

{% highlight c %}
void countSort(int data[], int n, int max)
{
	int i, j, k
	int* cnt = malloc((max + 1)*sizeof(int));

	for (i = 0; i < n, i++)
	{
		cnt[data[i]]++;
	}

	int i = 0;
	for (j = 0; j <= max; j++)
	{
		for (k = cnt[j]; k > 0; k--)
		{
			data[i++] = j;
		}
	}
}
{% endhighlight %}

In the first for loop, we iterate through all of the buckets in the hash table.
In the second loop, we iterate through all the values in the bucket.
Therefore, the complexity depends both on the number of buckets and the number of elements to be sorted.
The complexity of the sort is $O(n + \text{max})$, which is equivalent to $O(max(n, max))$.

---
layout: post
title: "Adventures in Data Structures Vol 14: Dictionaries"
date: 2020-03-16 010:07:28 +0000
categories: cs
---

# Introduction to Dictionaries

The last ADT that we will be discussing in this class is the *dictionary* or the *map*.

Dictionaries are pretty common data structures since a common situation that arises is if we want to store key-value pairs.
In C, this can be defined using a struct like:

```
struct Association 
{
	KT key;
	VT value;
};
```

The dictionary stores these key-value pairs and allows for quick look up of values *using* their associated keys.

The operations which a dictionary supports is:

+ void put(key, value)
+ void get(KT key, VT *ptr)
+ int containsKey(KT key) 
+ void removeKey(KT key)

We can implement a dictionary in C using a dynamic array where each element is a pointer to an association struct we defined above:

# Function Implementations

The `get` function finds the value associated with a key and puts that value inside of a pointer variable called `valptr`.

```
void dynArrayDictionaryGet(struct dynArray* da, KEYTYPE key, VALUETYPE* valptr)
{
	int i;
	for (i = 0; i < da->size; i++)
	{
		if (strcmp(da->data[i]->key, key) == 0)
		{
			*valptr = da->data[i]->value;
		}
	}
}
```

The `put` function places a value in the position associated with a particular key.
If an association is already there with that key, it is removed.

```
void dynArrayDictionaryPut(struct dynArray* da, KEYTYPE key, VALUETYPE val)
{
	struct association* ap;
	if (dynArrayDictionaryContainsKey(da, key))
	{
		dynArrayDictionaryRemove(da, key);
	}

	ap = (struct association*)malloc(sizeof(struct association));
	assert(ap != NULL);

	ap->key = key;
	ap->value = val;
	dynArrayAdd(da, ap);
}
```

The `contains` function is also very helpful.

```
int dynArrayDictionaryContainsKey(struct dynArray* da, KEYTYPE key)
{
	int i;

	for (i = 0; i < da->size; i++)
	{
		if (strcmp(key, da->data[i]->key == 0))
		{
			return 1;
		}
	}
	return 0;
}
```

Finally, let's implement the `remove` function.

```
void dynArrayDictionaryRemoveKey(struct dynArray* da, KEYTYPE key)
{
	int i;
	struct association* ap;

	for (i = 0; i < da->szie; i++)
	{
		if (strcmp(key, da->data[i]->key) == 0)
		{
			struct association* temp;
			temp = da->data[i];
			removeAtDynArr(da, i);
			free(temp);
			break;
		}
	}
}
```

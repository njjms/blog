/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Nick Sun
 * Date: 3/5/2020
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
   HashLink* iterator;
   HashLink* next;

   for (int i = 0; i < map->capacity; i++)
   {
		next = map->table[i];

		while (next != NULL)
		{
			iterator = next->next;
			
			hashLinkDelete(next);
			next = iterator;
		}
   }
   free(map->table);
   map->size = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
	// First, use HASH_FUNCTION to get index of correct bucket
	// modulus operator will be used to make sure index !greater than capacity
	int index = HASH_FUNCTION(key) % map->capacity;

	if (index < 0)
	{
		index = index + map->capacity;
	}

	HashLink* current = map->table[index];

	while (current != NULL)
	{
		// if string equal, return address of value
		if(strcmp(current->key, key) == 0)
		{
			return &current->value;
		}
		current = current->next;
	}
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	HashLink* linkItr;
	HashMap* newHashMap = hashMapNew(capacity);

	for (int i = 0; i < map->capacity; i++)
	{
		linkItr = map->table[i];

		while (linkItr != NULL)
		{
			hashMapPut(newHashMap, linkItr->key, linkItr->value);
			linkItr = linkItr->next;
		}
	}

	hashMapCleanUp(map);
	map->table = newHashMap->table;
	map->size = newHashMap->size;
	map->capacity = capacity;

	// newHashMap and map now have a pointer to the same table -- bad idea
	newHashMap->table = NULL;
	free(newHashMap);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
	assert(map != NULL);
	assert(key != NULL);

	int index = HASH_FUNCTION(key) % map->capacity;
	if (index < 0)
	{
		index = index + map->capacity;
	}

	HashLink* linkIterator = map->table[index];
	int* currentValue = hashMapGet(map, key);

	if (currentValue != NULL)
	{
		*currentValue += value;
	}
	else
	{
		HashLink* newLinkToAdd = hashLinkNew(key, value, 0);
		if (map->table[index] == NULL)
		{
			map->table[index] = newLinkToAdd;
		}
		else
		{
			while (linkIterator->next != NULL)
			{
				linkIterator = linkIterator->next;
			}
			linkIterator->next = newLinkToAdd;
		}
		map->size = map->size +1;
	}

	/*
	HashLink* current = map->table[index];
	HashLink* prev = NULL;

	if (current != NULL)
	{
		// no bucket yet, just add new link
		map->table[index] = hashLinkNew(key, value, NULL);
		map->size++;
	}
	else
	{
		// add to preexisting bucket
		// first check if we can just replace value
		while(current != NULL)
		{
			if (strcmp(current->key, key) == 0)
			{
				current->value = value;
				return;
			}
			prev = current;
			current = current->next;
		}
			
		// if we get here, means we have to make a new link
		if (current == NULL)
		{
			prev->next = hashLinkNew(key, value, NULL);
			map->size++;
		}
	}
	*/
	float currentLoad = hashMapTableLoad(map);
	if (currentLoad >= MAX_TABLE_LOAD)
	{
		resizeTable(map, 2*map->capacity);
	}
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
	int index = HASH_FUNCTION(key) % map->capacity;
	if (index < 0)
	{
		index = index + map->capacity;
	}

	HashLink* current = map->table[index];
	HashLink* prev = NULL;

	if (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			map->table[index] = map->table[index]->next;
			hashLinkDelete(current);
			map->size--;
		}
		else
		{
			// need to traverse linked list
			prev = current;
			current = current->next;

			while (current != NULL)
			{
				if (strcmp(current->key, key) == 0)
				{
					prev->next = current->next;
					hashLinkDelete(current);
					map->size--;
				}

				prev = current;
				current = current->next;
			}
		}
	}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
	if (hashMapGet(map, key) != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
	int count = 0;

	for (int i = 0; i < map->capacity; i++)
	{
		if (map->table[i] == NULL)
		{
			count++;
		}
	}

	return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
	float load = ((float)(map->size))/((float)(map->capacity));
	return load;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
	for (int i = 0; i < map->capacity; i++)
	{
		HashLink* current = map->table[i];

		if (current != NULL)
		{
			printf("\nBucket Number: %i\n", i);

			while (current != NULL)
			{
				printf(" (%s, %d) \n", current->key, current->value);
				current = current->next;
			}
		}
	}	
	printf("\n");
}

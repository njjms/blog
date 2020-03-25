#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
	char* word = nextWord(file);
	while (word != NULL)
	{
		hashMapPut(map, word, 1);
		free(word);
		word = nextWord(file);
	}
}

// as well as the wikipedia page for the Levenshtein distance
// This function is fairly slow since it is recursive, but it DOES run!
int levenshtein(const char* s, int ls, const char* t, int lt)
{
	int a, b, c;

	if (!ls)
	{
		return lt;
	}

	if (!lt)
	{
		return ls;
	}

	if (s[ls - 1] == t[lt - 1])
	{
		return levenshtein(s, ls-1, t, lt-1);
	}

	a = levenshtein(s, ls-1, t, lt-1);
	b = levenshtein(s, ls, t, lt-1);
	c = levenshtein(s, ls-1, t, lt);

	if (a > b)
	{
		a = b;
	}

	if (a > c)
	{
		a = c;
	}

	return a + 1;
}

// Second levenshtein distance implementation, this time with caching
// Source: https://rosettacode.org/wiki/Levenshtein_distance#C

int c_levenshtein(const char *s, const char *t)
{
		int ls = strlen(s), lt = strlen(t);
		int d[ls + 1][lt + 1];
			 
		for (int i = 0; i <= ls; i++)
			for (int j = 0; j <= lt; j++)
				d[i][j] = -1;

		int dist(int i, int j) 
		{
			if (d[i][j] >= 0) return d[i][j];

			int x;
			if (i == ls)
				x = lt - j;
			else if (j == lt)
				x = ls - i;
			else if (s[i] == t[j])
				x = dist(i + 1, j + 1);
			else
		   	{
				x = dist(i + 1, j + 1);

				int y;
				if ((y = dist(i, j + 1)) < x) x = y;
				if ((y = dist(i + 1, j)) < x) x = y;
				x++;
			}
			return d[i][j] = x;
		}
	return dist(0, 0);
}
/**
 * Checks the spelling of the word provded by the user. If the word is spelled incorrectly,
 * print the 5 closest words as determined by a metric like the Levenshtein distance.
 * Otherwise, indicate that the provded word is spelled correctly. Use dictionary.txt to
 * create the dictionary.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    HashMap* map = hashMapNew(1000);

    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);

    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);

        for (int i = 0; i < 255; i++)
		{
			// if uppercase, convert to lowercase
			if (inputBuffer[i] > 64 && inputBuffer[i] < 91)
			{
				inputBuffer[i] += 32;
			}
		}

        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
		else if (hashMapContainsKey(map, inputBuffer))
		{
			printf("The inputted word %s is spelled correctly.\n", inputBuffer);
		}
		else
		{
			HashLink* current;
			//int len1 = strlen(inputBuffer);
			//int len2;
			int lev_d;
			char* word;
			int lowest = 200;

			printf("The inputted word is spelled incorrectly.\n");
			printf("\nPerhaps you meant:\n");
			
			for (int i = 0; i < map->capacity; i++)
			{
				current = map->table[i];
				while (current != NULL)
				{
					word = current->key;
					//len2 = strlen(word);

					lev_d = c_levenshtein(inputBuffer, word);
					if (lev_d < lowest)
					{
						lowest = lev_d;
					}
					current = current->next;
				}
			}

			int printCount = 0;
			int printMax = 5;

			clock_t timer2 = clock();

			for (int i = 0; i < map->capacity; i++)
			{
				current = map->table[i];
				while (current != NULL)
				{
					if (printCount == printMax)
					{
						break;
					}
					word = current->key;
					//len2 = strlen(word);
					lev_d = c_levenshtein(inputBuffer, word);

					if (lev_d == lowest)
					{
						printf("%s\n", word);
						printCount++;
					}
					current = current->next;
				}
			}
			timer2 = clock() - timer2;
			printf("Levenshtein calculation took %f seconds to complete.\n", (float)timer2 / (float)CLOCKS_PER_SEC);
		}
    }

    hashMapDelete(map);
    return 0;
}

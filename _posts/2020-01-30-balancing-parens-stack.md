---
layout: post
title: "Adventures in Data Structures Vol. 3: Classic Balancing Act"
date: 2020-01-30 010:07:28 +0000
categories: cs
---

Today I wanted to talk about a fun assignment I had in my data structures class which is also a classic application of the stack data structure.
A common functionality in linters is to highlight when the user has typed an expression that has unmatched parentheses, curly braces, and square brackets.
For example: `some_function([1, 2, 3]){TODO}` would have balanced parentheses but `some_function([4,5,6]{}` would not since it has an unmatched `(`.

Unmatching can also occur when different parentheses sets are not nested in one another.
It would also not be balanced to have something like `some_function([7,8,9)]` since the square brackets and parentheses are not completely contained in one another.

How can we write a program that takes in a string containing parentheses, square brackets, and curly braces, and output a 1 if it's balanced or a 0 if it's imbalanced.

It's actually easy to do if you know a little bit about stacks!

The basic pseudocode is:
1. Iterate along the string. If an opening parenthesis `(`, opening bracket `[`, or curly brace `{`is found, then add the corresponding **closing** parenthesis, bracket, or brace to the stack.
2. Keep iterating. If a closing parenthesis `)`, closing bracket `]`, or closing brace `}` is found, check the top of the stack.
3. If the top of the stack matches the current character, pop that character off the stack. If it is not equal, the string is not balanced.
4. If you finish iterating through the string and the stack is nonempty, the string is not balanced.

This process is actually pretty simple, but probably requires some thinking to process it fully the first time around.

Let's code this pseudocode up in C.
First thing we need is a helper function to iterate through the characters in the string.

```
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}
```

We'll be using this function in our main balancing function!

```
int isBalanced(char* s)
{
	assert(s != 0);

	struct DynArr* v;
	v = newDynArr(50);

	char* ch;
	ch = s;
	char currentCh = nextChar(ch);

	while (currentCh != '\0')
	{
		if (currentCh == '[')
		{
			addDynArr(v, ']');
		}

		if (currentCh == '(')
		{
			addDynArr(v, ')');
		}

		if (currentCh == '{')
		{
			addDynArr(v, '}');
		}

		if (currentCh == ']' && sizeDynArr(v) > 0)
		{
			if (topDynArr(v) == ']')
			{
				popDynArr(v);
			}
			else
			{
				return 0;
			}
		}
		else if (currentCh == ']' && sizeDynArr(v) == 0)
		{
			return 0;
		}
		else
		{
		}
		
		if (currentCh== ')' && sizeDynArr(v) > 0)
		{
			if (topDynArr(v) == ')')
			{
				popDynArr(v);
			}
			else
			{
				return 0;
			}
		}
		else if (currentCh == ')' && sizeDynArr(v) == 0)
		{
			return 0;
		}
		else
		{
		}

		if (currentCh == '}' && sizeDynArr(v) > 0)
		{
			if (topDynArr(v) == '}')
			{
				popDynArr(v);
			}
			else
			{
				return 0;
			}
		}
		else if (currentCh == '}' && sizeDynArr(v) == 0)
		{
			return 0;
		}
		else
		{
		}

		currentCh = nextChar(ch);
	}

	if (sizeDynArr(v) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
```

This function is pretty long!
Let's break it up into parts.

The first part of the function is pretty straightforward; we get a pointer to an array (aka a pointer to a block of memory that we can iterate through) of max size 50.
We get the first character of that array using the `nextChar` function.

Then we start iterating through the array until we reach the end of array character `\0`.
If we run into any of the opening parentheses, brackets, or braces, we add the corresponding closing character to the stack.

If the current character is a closing character **AND** and the stack is not empty, we then check if the top of the stack is equal to that character.
If it is, we pop it.
If not, or if the stack is empty, we return 0 immediately.

If we make it to the end, we check the size of the stack.
If it is 0, then we have a balanced string and we can return 1!
Otherwise, we must solemnly return 0.

This is a classic stack application, and a great exercise.

Here is a main function you can use to test this code.
Try inputting different strings and see what you get!

```
int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;

	if (argc < 2)
	{
		printf("Null string\n");
		printf("Defaults to balanced.\n");
		return 0;
	}
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}
```



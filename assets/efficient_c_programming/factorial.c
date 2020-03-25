/* This function takes N, an unsigned integer, and reports N! */

#include <stdio.h>

unsigned long int factorial(unsigned int N)
{
	unsigned long int Answer;

	if(N == 0)
	{
		Answer = 1;
	}
	else
	{
		if( N == 1 )
		{
			Answer = 1;
		}
		else
			Answer = N*factorial(N-1);
	}
}

unsigned long int main(void)
{
	unsigned long int N;
	unsigned long int output;

	printf("Enter an integer:\n");
	scanf("%lu", &N);

	output = factorial(N);
	printf("Result of %lu! is %lu\n", N, output);
}

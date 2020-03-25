#include <stdio.h>

/* unsigned long int; */

long unsigned int Factorial( unsigned long int N )
{
	int i;
	unsigned long int Answer = 1;

	for( i = 1; i <= N; i++ )
		Answer *= i;			/* Treated as one block so no braces */

	return Answer;
}
int main( void ) 
{
	int i;
	const int MaxNum = 12;

	printf(" N         N!\n");
	for( i = 0; i <= MaxNum; i++ )
		printf( "%2d %10lu\n", i, Factorial(i));

	return 0;
}


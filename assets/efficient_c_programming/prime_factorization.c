/* Prints the prime factorization of a number */

#include <stdio.h>

long unsigned int main( void )
{
	unsigned long NumberToFactor, PossibleFactor, UnfactoredPart;

	printf("Enter a number to factor: ");
	scanf("%lu", &NumberToFactor);

	PossibleFactor = 2;
	UnfactoredPart = NumberToFactor;

	while( PossibleFactor * PossibleFactor <= UnfactoredPart )
	{
		if( UnfactoredPart % PossibleFactor == 0 )
		{
			printf("%lu\n", PossibleFactor);
			UnfactoredPart /= PossibleFactor;
		}
		else
		{
			if( PossibleFactor == 2 )
				PossibleFactor = 3;
			else
				PossibleFactor += 2;
		}
	}

	printf( "%lu\n", UnfactoredPart);
}


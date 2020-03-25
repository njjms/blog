#include <stdio.h>

/* Compute frequency of Lottery Numbers */

#define MaxNum 49 /* Numbers Range from 1 to 49 */

int main( void )
{
	int Count[MaxNum + 1]; /* Frequency of Each Number */
	int Number;
	int i;

	for( i = 0; i <= MaxNum; i++ )
		Count[i] = 0;

	/* No input prompt needed */
	while(scanf( "%d", &Number) == 1)
		if(Number < 1 || Number > MaxNum)
			printf("Out of range number ignored\n");
		else
			Count[Number]++;
	
	/* Output the data, seven numbers per line */
	for( i = 1; i <= MaxNum; i++)
	{
		printf( "%3d:%4d", i, Count[i]);
		if( i % 7 == 0)
			printf("\n");
		else
			printf("    ");
	}

	return 0;
}

	

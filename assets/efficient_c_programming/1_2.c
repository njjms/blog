#include <stdio.h>

/* read items, compute their average */

char main ( void )
{
	int ItemsRead = 0;
	double ThisItem, Sum = 0;

	printf( "Enter as many items as you want\n" );
	printf( "Terminate with a non-double or EOF marker\n");

	while( scanf( "%lf", &ThisItem ) == 1)
	{
		ItemsRead++;
		Sum += ThisItem;
	}

	printf("The average of %d items was %f\n",
			ItemsRead, Sum / ItemsRead );

	return 0;
}


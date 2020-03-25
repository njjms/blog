/* This program calculates the area of certain shapes given dimensions*/

#include <stdio.h>

#define Pi 3.1415
#define Circle 1
#define Rectangle 2
#define Square 3

int main( void )
{
	int Choice;
	double Dim1, Dim2;

	while( 1 )
	{
		printf("Enter %d for circle.\n", Circle);
		printf("Enter %d for rectangle.\n", Rectangle);
		printf("Enter %d for square.\n", Square);

		if( scanf("%d", &Choice) != 1)
			break;

		if(Choice == Circle)
		{
			printf("Enter radius: ");
			if( scanf("%lf", &Dim1) != 1 )
				break;
			printf("Shape is circle radius %.2f;", Dim1);
			printf("and the area is %.2f\n", Dim1 * Dim1 * Pi);
		}
		else if( Choice == Square )
		{
			printf("Enter side: ");
			if( scanf("%lf", &Dim1) != 1)
				break;
			printf("Shape is a square with side length %.2f", Dim1);
			printf(" and the area is %.2f.\n", Dim1 * Dim1);
		}
		else if( Choice == Rectangle )
		{
			printf("Enter length and width:\n");
			if( scanf("%lf %lf", &Dim1, &Dim2) != 1 )
				break;
			printf("Shape is a rectangle.\n");
			printf("The length and width are %lf and %lf with area %lf", Dim1, Dim2, Dim1 * Dim2);
		}
		else
		{
			printf("Illegal choice");
			break;
		}
	}
}



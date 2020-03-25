/* This function takes X, a float, and N and unsigned integer and reports X^N */

#include <stdio.h>

double exponentiate( double X, unsigned int N )
{
	double Answer;
	if( N == 0)
		Answer = 1;
	else
		if( N == 1 )
			Answer = X;
		else
			Answer = X*exponentiate(X, N-1);
}

double main(void)
{
	double X;
	unsigned int N;
	double output;

	printf("Enter a decimal and an integer, separated by a space:\n");
	scanf("%lf %u", &X, &N);

	output = exponentiate(X, N);
	printf("Result of %lf raised to the %u is %lf\n", X, N, output);
}


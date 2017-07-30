/*
n! = 1 (n= 0, 1)
     n * (n - 1) (n > 1)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long factorial(int n)
{
	long result;

	if (n == 0 || n == 1) {
		result = 1;
	} else {
		result = factorial(n - 1) * n;
	}
	return result;
}

int main()
{
	printf("%d\n", factorial(5));
}

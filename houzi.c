#include <stdio.h>

int total(int n)
{
	int sum;
	if (n == 10) {
		printf("10\t1\n");
		return 1;
	}
	sum = total(n + 1) * 2;
	printf("%d\t%d\n", n, sum);
	return sum;
}

int main()
{
	total(1);
}

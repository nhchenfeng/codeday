#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	long a;
	long b;
	while (scanf("%lx %lx", &a, &b) != EOF) {
		scanf("%lx %lx", &a, &b);
		if (1 <= a && a <= 100 && b <= 100 && b >= 1) {
			printf("%d\n", (int)(a + b));
		} else
			return 0;
	}
}

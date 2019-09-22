#include <stdio.h>

int ret_dec()
{
	int a = 3;
	int b = a--;
	return (b);
}

void print(int (*a)[2]) {
	int i, j;
	printf("%lx\n", a);
	for(i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			printf("%d\n", a[i][j]);
		}
	}
}

int main()
{
	int a[2][2] = {
		{1, 2},
		{2, 2}
	};
	printf("%lx\n", a);
	int (*b)[2] = &a[0];
	print(a);
	printf("%lx\n", b);
	printf("%d\n", ret_dec());
}

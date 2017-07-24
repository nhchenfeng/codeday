#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(int *arrary, int len, int max)
{
	int num = 0;
	int i = 0;
	int j = len - 1;
	while (i < j) {
		if (arrary[j] == max) {
			num++;
			j--;
		}
		if (arrary[i] + arrary[j] <= max) {
			num++;
			i++;
			j--;
		} else {
			j--;
		}
	}
	return num;
}

int main()
{
	int a[] = {20, 20, 30, 50, 60, 70, 80, 90, 90, 100};
	printf("%d\n", match(a, 10, 100));
}

#include <stdio.h>
#include <stdlib.h>

static int arrary[] = {5, 4, 2, 1, 8, 7, 9, 0, 6, 3};

void print_arrary(int a[])
{
        int n = sizeof(arrary) / sizeof(int);
        int i;
        for (i = 0; i < n; i++) {
                printf("%d ", a[i]);
        }
        printf("\n");
}

void swap_sort(int a[], int low, int high)
{
	int temp;
	int i, j;
	/* 每次将最大的数放到末尾 */
	for (j = high; j >=0; j --) {
		for(i = 0; i <= j; i++) {
			if (a[i] > a[j]) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

int main()
{
	print_arrary(arrary);
	swap_sort(arrary, 0, 9);
	print_arrary(arrary);
	return 0;
}

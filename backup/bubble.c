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

void bubble_sort(int a[], int low, int high)
{
	int temp;
	int i, j;
	for(i = low; i < high; i ++) {
		for (j = low; j < high - i; j ++) {
			if (a[j] > a[j + 1]) {
				temp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = temp;
			}
		}
	}
}

int main()
{
	print_arrary(arrary);
	bubble_sort(arrary, 0, 9);
	print_arrary(arrary);
	return 0;
}

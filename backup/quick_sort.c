#include <stdio.h>
#include <stdlib.h>

/*
 * 快速排序：
 * 找一个基准Key，一般为数组首
 * 然后从high遍历找比key小的值，与从low遍历找比key大的值，交换
 * 知道low和high相逢
 * 此时相逢的位置，即为key应该所在的位置
 * 这样分割成3部分，已经在正确位置的key和key的左边比key小,可以的右边比key大
 * 然后递归即可
 */

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

void swap(int arrary[], int low, int high)
{
	int temp;
	temp = arrary[low];
	arrary[low] = arrary[high];
	arrary[high] = temp;
}

int division(int arrary[], int low, int high)
{
	int position = low;
	int key = arrary[position];

	/*printf("before low %d high %d\n", low, high);*/
	/* find the true position of key */
	while (low < high) {
		/* 过滤掉右边比key大的值,右边都比key大 */
		while (low < high && arrary[high] >= key)
				high --;
		/* 过滤掉左边比key小的只，左边都比key小 */
		while (low < high && arrary[low] <= key)
				low ++;
		/* 最后low和high必然相等, 即key应该在的位置 */
		swap(arrary, low, high);
		print_arrary(arrary);
	}

	/*printf("after low %d high %d\n", low, high);*/
	swap(arrary, low, position);
	print_arrary(arrary);
	return low;
}

void quick_sort(int arrary[], int low, int high)
{
	int div;
	if (low < high) {
		div = division(arrary, low, high);
		quick_sort(arrary, low, div - 1);
		quick_sort(arrary, div + 1, high);
	}
}

int main()
{
	print_arrary(arrary);
	quick_sort(arrary, 0, 9);
	print_arrary(arrary);
	return 0;
}

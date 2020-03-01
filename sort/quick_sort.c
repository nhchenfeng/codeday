#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(X) (sizeof(X) / sizeof((X)[0]))

int partition(int *data, int left, int right)
{
	int loop;
	int tmp;
	int pivot = data[left];
	int store_index = left + 1; /* store_index 右边的相互交换，先不带基准 */

	if (left >= right)
		return left;

	for (loop = left + 1; loop <= right; loop++) {
		if (data[loop] < pivot) {
			tmp = data[loop];
			data[loop] = data[store_index];
			data[store_index] = tmp;
			store_index++;
		}
	}
	data[left] = data[store_index - 1];
	data[store_index - 1] = pivot;
	return store_index - 1;
}

void sort(int *data, int left, int right)
{
	int index;
	if (right <= left)
		return;
	index = partition(data, left, right);
	sort(data, left, index - 1);
	sort(data, index + 1, right);
}

void show(int *data, int left, int right)
{
	int loop;;
	for (loop = left; loop <= right; loop++) {
		printf("%d ", data[loop]);
	}
	printf("\n");
}

int main()
{
	int data1[] = {10,9,8,7,6,5,4,3,2,1};
	int data2[] = {1,9,8,2,5,6,4,3,7,10};
	int data3[] = {1,5,8,2,5,6,4,5,7,10};
	int data4[] = {5,5,5,2,5,6,4,5,7,10};
	int data5[] = {1,2,3,4,5,6,7,8,9,10};
	int data6[] = {4, 7, 6, 5, 3, 2, 8, 1};
	int data7[] = {4, 5, 7, 8, 3, 10};
	sort(data1, 0, ARRAY_SIZE(data1) - 1);
	show(data1, 0, ARRAY_SIZE(data1) - 1);
	sort(data2, 0, ARRAY_SIZE(data2) - 1);
	show(data2, 0, ARRAY_SIZE(data2) - 1);
	sort(data3, 0, ARRAY_SIZE(data3) - 1);
	show(data3, 0, ARRAY_SIZE(data3) - 1);
	sort(data4, 0, ARRAY_SIZE(data4) - 1);
	show(data4, 0, ARRAY_SIZE(data4) - 1);
	sort(data5, 0, ARRAY_SIZE(data5) - 1);
	show(data5, 0, ARRAY_SIZE(data5) - 1);

	sort(data5, 0, ARRAY_SIZE(data6) - 1);
	show(data5, 0, ARRAY_SIZE(data6) - 1);

	sort(data7, 0, ARRAY_SIZE(data7) - 1);
	show(data7, 0, ARRAY_SIZE(data7) - 1);
	return 0;
}
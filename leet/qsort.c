#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(X) (sizeof(X) / sizeof((X)[0]))

/*
快速排序，从数组中找一个基准点，一般就选择开头
遍历数组，将比它小的放到它前边去，比它大的放到它后边去
每次确定了一个位置
然后递归
问题的关键就在于如何遍历，把比它小的和比它大的做好, 这里采用算法：
遍历把比基准小的都放到放到它前边，最后的右值于基准交换
left作为pivot, store_index作为返回的pivot所在的地方
从left + 1到right，如果小于等于pivot的化，则放到store_index的地方，store_index++
结束时，store_index - 1所在的地方，就是pivot应该放的地方，此时store_index前边的都小于等于pivot
因此store_index - 1为left的最右值，此时交换pivot和最右值，即store_index - 1
考虑store_index有3个可能:
最左边，即没有比pivot大的，此时store_index - 1即为本身，都比pivot大，没有发生交换
最右边，都比pivot小，此时store_index为right + 1, store_index - 1也一样为最右值
中间，则store_index - 1为left的右值
*/

int partition(int *data, int left, int right)
{
	int loop;
	int tmp;
	int store_index = left + 1;
	int start = left;
	if (left >= right)
		return left;
	int pivot = data[left];
	for (loop = left + 1; loop <= right; loop++) {
		if (data[loop] <= pivot) {
			tmp = data[store_index];
			data[store_index] = data[loop];
			data[loop] = tmp;
			store_index++;
		}
	}
	data[start] = data[store_index - 1];
	data[store_index - 1] = pivot;
	return store_index - 1;
	printf("pivot %d index %d\n", pivot, store_index);
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
	sort(data1, 0, ARRAY_SIZE(data1) - 1);
	show(data1, 0, ARRAY_SIZE(data1) - 1);
	sort(data2, 0, ARRAY_SIZE(data2) - 1);
	show(data2, 0, ARRAY_SIZE(data2) - 1);
	sort(data3, 0, ARRAY_SIZE(data3) - 1);
	show(data3, 0, ARRAY_SIZE(data3) - 1);
	sort(data4, 0, ARRAY_SIZE(data3) - 1);
	show(data4, 0, ARRAY_SIZE(data3) - 1);
	sort(data5, 0, ARRAY_SIZE(data3) - 1);
	show(data5, 0, ARRAY_SIZE(data3) - 1);
	return 0;
}
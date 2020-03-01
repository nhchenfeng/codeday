#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(X) (sizeof(X) / sizeof((X)[0]))
/*
利用数组实现二叉堆，主要包括原地堆排序
top-k, 优先队列3个场景
堆排序：
1、构造大顶堆
2、将root交换到最后一个位置，size--.此时最大的元素已经归位
3、重复1，2

沉底，优先将下方所有元素沉底，最后上边
*/

/* 将index 沉到下去 */
void heap_down(int *data, int index, int size)
{
	int tmp;
	int dad = index;
	int left = dad * 2 + 1;
	int right= dad * 2 + 2;
	int max = dad;
	if (left < size && data[left] > data[max]) {
		max = left;
	}
	if (right < size && data[right] > data[max]) {
		max = right;
	}
	if (max != dad) {
		tmp = data[max];
		data[max] = data[dad];
		data[dad] = tmp;
		heap_down(data, max, size);
	}
}

void heap_sort(int *data, int len)
{
	int loop;
	int tmp;
	/* heapify */
	for (loop = len - 1; loop >=0; loop--) {
		heap_down(data, loop, len);
	}
	/* move the root to the last, then heapify */
	for (loop = len - 1; loop >= 0 ; loop--) {
		tmp = data[0];
		data[0] = data[loop];
		data[loop] = tmp; /* max to the last */
		len--;
		heap_down(data, 0, len);
	}

}

static int heap_data[1000];
static int heap_size;

void heap_up(int *data, int index, int size)
{
	int tmp;
	int dad = (index - 1) / 2;
	if (dad >= 0 && data[dad] < data[index]) {
		tmp = data[dad];
		data[dad] = data[index];
		data[index] = tmp;
		heap_up(data, dad, size);
	}
}


/*
优先队列：
进来，data[size] = input, 然后冒上来
出去，data[0] = data[size - 1] 冒下去
*/

void heap_add(int data)
{
	heap_data[heap_size] = data;
	heap_size++;
	heap_up(heap_data, heap_size - 1, heap_size);
}

int heap_pop()
{
	int data = -1;
	if (heap_size >= 1) {
		data = heap_data[0];
	}
	heap_data[0] = heap_data[heap_size - 1];
	heap_size--;
	heap_down(heap_data, 0, heap_size);
	return data;
}

/*
top-k:
*/

void max_down(int *data, int index, int size)
{
	int tmp;
	int dad = index;
	int son = dad * 2 + 1;
	int little = dad;
	if (son < size && data[son] < data[little]) {
		little = son;
	}
	if (son + 1 < size && data[son + 1] < data[little]) {
		little = son + 1;
	}
	if (little != dad) {
		tmp = data[little];
		data[little] = data[dad];
		data[dad] = tmp;
		max_down(data, little, size);
	}
}

int top_k(int *data, int size, int k)
{
	int loop;
	memset(heap_data, -1, sizeof(heap_data));
	for (loop = 0; loop < size; loop++) {
		if (data[loop] > heap_data[0]) {
			heap_data[0] = data[loop];
			max_down(heap_data, 0, k);
		}
	}
	return heap_data[0];
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
	int loop;
	int data1[] = {10,9,8,7,6,5,4,3,2,1};
	int data2[] = {1,9,8,2,5,6,4,3,7,10};
	int data3[] = {1,5,8,2,5,6,4,5,7,10};
	int data4[] = {5,5,5,2,5,6,4,5,7,10};
	int data5[] = {2,1};
	heap_sort(data1, ARRAY_SIZE(data1));
	show(data1, 0, ARRAY_SIZE(data1) - 1);
	heap_sort(data2, ARRAY_SIZE(data2));
	show(data2, 0, ARRAY_SIZE(data2) - 1);
	heap_sort(data3,ARRAY_SIZE(data3));
	show(data3, 0, ARRAY_SIZE(data3) - 1);
	heap_sort(data4, ARRAY_SIZE(data3) - 1);
	show(data4, 0, ARRAY_SIZE(data3) - 1);
	heap_sort(data5, ARRAY_SIZE(data5));
	show(data5, 0, ARRAY_SIZE(data5) - 1);

	heap_add(3);
	heap_add(10);
	heap_add(1);
	for (loop = 0; loop < 3; loop++) {
		printf("%d\n", heap_pop());
	}
	printf("top 5 data1 %d\n", top_k(data1, ARRAY_SIZE(data1), 5));
	return 0;
}
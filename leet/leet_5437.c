#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODE    100001

struct node {
	int data;
	int num;
};

static struct node list[MAX_NODE];
static int list_size;

static void insert(int data)
{
	int loop;
	int index = list_size;
	int flag = 0;
	for (loop = 0; loop < list_size; loop++) {
		if (list[loop].data == data) {
			list[loop].num++;
			flag = 1;
		}
	}
	if (!flag) {
		list[index].data = data;
		list[index].num = 1;
		list_size++;
	}
}

static int compare(const void *data1, const void *data2)
{
	struct node node1 = *(const struct node *)data1;
	struct node node2 = *(const struct node *)data2;
	return node1.num - node2.num;
}

int findLeastNumOfUniqueInts(int *arr, int arrSize, int k)
{
	int loop;
	list_size = 0;
	int delete = 0;

	if (!arr || !arrSize)
		return 0;
	
	for (loop = 0; loop < arrSize; loop++) {
		insert(arr[loop]);
	}
	qsort(list, list_size, sizeof(struct node), compare);
	for (loop = 0; loop < list_size; loop++) {
		printf("%d num %d\n", list[loop].data, list[loop].num);
		delete += list[loop].num;
		if (delete == k) {
			return list_size - loop - 1;
		} else if (delete < k) {
			continue;
		} else {
			return list_size - loop;
		}
	}
	return 0;
}
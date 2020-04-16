#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
这题开始首先，讲work和bike做成了一个二维数组，然后每次从二维数组从取出一个最小值，这样超时
优化的算法是，将work,bike,dis存在一个结构体全集数组中，然后排序
从前往后取即可，取的时候，看bike和work有没有分配到，如果分配到了直接下一个，因为这个数组是全集
不用更新，前边用了后，后边自然就用不到了，而且还存在其他的值
*/

#define MAX_NODE 1000

struct node {
	int work;
	int bike;
	int dis;
};

static struct node array[MAX_NODE * MAX_NODE];
static int array_size;

static int ans[MAX_NODE];
static int used_work[MAX_NODE];
static int used_bike[MAX_NODE];

static int compare(const void *p1, const void *p2)
{
	struct node *data1 = (struct node *)p1;
	struct node *data2 = (struct node *)p2;
	if (data1->dis == data2->dis) {
		if (data1->work == data2->work) {
			return data1->bike - data2->bike;
		} else {
			return data1->work - data2->work;
		}
	} else {
		return data1->dis - data2->dis;
	}
}

int *assignBikes(int **workers, int workersSize, int *workersColSize,
		 int **bikes, int bikesSize, int *bikesColSize, int *returnSize)
{
	int w_loop;
	int b_loop;
	int dis;
	int loop;
	int have;

	if (!workers || !workersSize || workersSize > MAX_NODE || bikesSize > MAX_NODE) {
		*returnSize = 0;
		return ans;
	}
	array_size = 0;
	memset(used_work, 0, sizeof(used_work));
	memset(used_bike, 0, sizeof(used_bike));
	for (w_loop = 0; w_loop < workersSize; w_loop++) {
		for (b_loop = 0; b_loop < bikesSize; b_loop++) {
			dis = abs(workers[w_loop][0] - bikes[b_loop][0]) + abs(workers[w_loop][1] - bikes[b_loop][1]);
			array[array_size].work = w_loop;
			array[array_size].bike = b_loop;
			array[array_size].dis = dis;
			array_size++;
		}
	}
	qsort(array, array_size, sizeof(struct node), compare);
	have = 0;
	for (loop = 0; loop < MAX_NODE * MAX_NODE; loop++) {
		if (!used_work[array[loop].work] && !used_bike[array[loop].bike]) {
			ans[array[loop].work] = array[loop].bike;
			used_work[array[loop].work] = 1;
			used_bike[array[loop].bike] = 1;
			have++;
		}
		if (have ==workersSize) {
			break;
		}
	}
	*returnSize = workersSize;
	return ans;
}

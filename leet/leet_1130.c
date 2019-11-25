#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))

#define MAX_NODE  20
#define INF_MAX   16 * 16

static int ans;
static int visit[MAX_NODE];

void get_min2_index(int *arr, int size, int *index1, int *index2)
{
	int loop;
	int min = INF_MAX;
	if (size == 1) {
		*index1 = 0;
		*index2 = 0;
	}
	for (loop = 0; loop < size - 1; loop++) {
		if (arr[loop] * arr[loop + 1] < min) {
			printf("%d * %d\n", loop, loop + 1, arr[loop] * arr[loop + 1]);
			min = arr[loop] * arr[loop + 1];
			if (arr[loop] <= arr[loop + 1]) {
				*index1 = loop;
				*index2 = loop + 1;
			} else {
				*index1 = loop + 1;
				*index2 = loop;
			}
		}
	}
}

void delete_data(int *arr, int index, int *size)
{
	int loop;
	*size = *size - 1;
	for (loop = index; loop < *size; loop++) {
		arr[loop] = arr[loop + 1];
	}
}

void dfs(int *arr, int len, int tmp)
{
	int index1;
	int index2;
	int data;
	int size = len;
	ans += tmp;

	if (len == 1) {
		return;
	}
	get_min2_index(arr, size, &index1, &index2);
	printf("min %d %d size %d\n", index1, index2, size);
	data = arr[index1] * arr[index2];
	delete_data(arr, index1, &size);
	dfs(arr, size, data);
}

int mctFromLeafValues(int *arr, int arrSize)
{
	ans = 0;
	if (!arr || !arrSize)
		return ans;

	dfs(arr, arrSize, 0);
	return ans;
}
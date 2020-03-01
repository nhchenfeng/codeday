#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF_MIN          (-9999999)
#define INF_MAX          (99999999)
#define MAX_NODE          1024
#define ARRAY_SIZE(x)    (sizeof(x) / sizeof((x)[0]))
#define MAX(a, b)        ((a) > (b) ? (a) : (b))

static int tmp_data[MAX_NODE];
static int ret_data[MAX_NODE];

/* 每次结果都存在ret_data中， 从left 到right排好序列了，
 * 借助tmp_data 以免覆盖之前的ret_data,最后拷贝到ret_data
 */
void divide(int *data, int left, int right)
{
	int mid;
	int loop;
	int left_index;
	int right_index;
	int tmp_left;
	int tmp_right;
	if (left == right) {
		ret_data[left] = data[left];
		return;
	}
	mid = (left + right) / 2;
	divide(data, left, mid);
	divide(data, mid + 1, right);
	left_index = left;
	right_index = mid + 1;
	for (loop = left; loop <= right; loop++) {
		if (left_index <= mid)
			tmp_left = ret_data[left_index];
		else
			tmp_left = INF_MAX;
		if (right_index <= right)
			tmp_right = ret_data[right_index];
		else
			tmp_right = INF_MAX;
		if (tmp_left <= tmp_right) {
			left_index ++;
			tmp_data[loop] = tmp_left;
		} else {
			right_index ++;
			tmp_data[loop] = tmp_right;
		}
		printf("[%d %d] [%d] %d %d - > %d\n", left, right, loop, tmp_left, tmp_right, tmp_data[loop]);
	}
	memcpy(ret_data + left, tmp_data + left, (right - left + 1) * sizeof(int));
	return;
}

void divide_sort(int *data, int size)
{
	int loop;
	memset(tmp_data, 0, sizeof(tmp_data));
	memset(ret_data, 0, sizeof(ret_data));
	divide(data, 0, size - 1);
	for(loop = 0; loop < size; loop++) {
		printf("%d ", ret_data[loop]);
	}
	printf("\n");
}

int main()
{
	int local_data[] = {200, 199, 198, 8, 6, 99, 65, 129, 3};
	divide_sort(local_data, ARRAY_SIZE(local_data));
	return 0;
}

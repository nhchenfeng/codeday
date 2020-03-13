# 排序

### 冒泡排序

算法：每次从前往后，比较相邻的2项，位置不对则交换，一遍过后，最后一个的位置确定，然后再来一遍，去掉最后一个，这样大的元素不断的冒到最后。

```
void bubble_sort(int *data, int size)
{
        int i, j;
        int tmp;

        for (i = 0; i < size; i++) {
                for (j = 0; j < size - i - 1; j++) { /* compare data[j] data [j + 1] */
                        if (data[j + 1] < data[j]) {
                                tmp = data[j + 1];
                                data[j + 1] = data[j];
                                data[j] = tmp;
                        }
                }
        }
}
```

### 选择排序

算法：找到数组中最小的元素，和第一个交换，然后找到最小的元素和第二个交换，依次直到结尾

```
void select_sort(int *data, int size)
{
	int i, j;
        int min, tmp;
        for (i = 0; i < size; i++) {
                min = i;
                for (j = i + 1; j < size; j++) {
                        if (data[j] < data[min])
                                min = j;
                }
                tmp = data[min];
                data[min] = data[i];
                data[i] = tmp;
        }
}
```

### 插入排序

算法：考虑手中有一副牌，从第二个开始，第一个一个数天然有序，将每张排依次插入，插入的时候，首先将这个牌保存起来，然后将这个张牌依次从右向左比较，大于则右移，小于直接放入。

```
void insert_sort(int *data, int size)
{
        int i, j;
        int tmp;
        int flag = 0;
        for (i = 1; i < size; i++) {
                flag = 0;
                tmp = data[i];
                for (j = i - 1; j >= 0; j--) { /* from right to left*/
                        if (data[j] > tmp) {
                                data[j + 1] = data[j];
                        } else {
                                data[j + 1] = tmp;
                                flag = 1;
                                break;
                        }
                }
                if (flag == 0) {  /* all bigger than tmp */
                       data[0] = tmp;
                }
        }
}

void insert_sort(int *data, int size)
{
        int i, j;
        int tmp;
        int flag = 0;
        for (i = 1; i < size; i++) {
                flag = 0;
                tmp = data[i];
                for (j = i - 1; j >= 0 && data[j] > tmp; j--) { /* from right to left, only bigger j-- */
                        data[j + 1] = data[j];
                }
                data[j + 1] = tmp;
        }
}
```

### 希尔排序

算法：希尔排序是插入排序的一个变化，首先设置一个步长，从len / 2 到 1，安装步长分别对数据进行插入排序

```
void shell_sort(int *data, int size)
{
        int step;
        int i, j;
        int tmp;
        for (step = size / 2; step > 0; step = step / 2) {
                for (i = step; i < size; i++) { /* 从step开始，往后每相隔step进行插入排序 */
                        tmp = data[i];
                        for (j = i - step; j >= 0 && data[j] > tmp; j -= step) {
                                data[j + step] = data[j]; /* 比较的数，相隔step */
                        }
                        data[j + step] = tmp;
                }
        }
}
```

### 快速排序

算法：快速排序采用的是分治，每次选择一个基准点，一般是排头，遍历数组，比它小的放到它前边，比它大的放到它后边，这个数据所在的最终位置固定下来，并且得到了一个index，然后对于这个index左边和这个index右边的2个部分，分别重复上述过程。

如何将小于这个数的放到前边，大于这个数放到后面，并且返回最终的index。可以选择left作为pivot,  left + 1作为store_index，从left + 1往后，先不带left玩，如果比pivot小，则与store_index交换，store_index++; 最后store_index - 1的地方与pivot交换，返回store_index - 1

```
int partition(int *data, int left, int right)
{
	int loop;
	int tmp;
	int pivot = data[left];
	int store_index = left + 1; /* store_index 右边的相互交换，先不带基准, 最后将基准归位到小于的右边界 */

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
```

### 堆排序

堆排序，首先堆，如最大堆，满足最大的节点在树根，然后每个节点的值大于左右孩子

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* start from 0, left 2 * dad + 1, right 2 * dad + 2, max up */
void max_heap(int *data, int index, int end)
{
        int tmp;
        int dad = index;
        int left =  2 * dad + 1;
        int right = 2 * dad + 2;
        int max = dad;
        if (left <= end && data[left] > data[max])
                max = left;
        if (right <= end && data[right] > data[max])
                max = right;

        if (max != dad) {
                tmp = data[max];
                data[max] = data[dad];
                data[dad] = tmp;
                max_heap(data, max, end);
        }
}

void heap_sort(int *data, int size)
{
        int i;
        int tmp;
        for (i = size - 1; i >= 0; i--) {
                /* 从后往前堆化，这点很重要 */
                max_heap(data, i, size);
        }
        for(i = size - 1; i >= 0; i--) {
                tmp = data[0];
                data[0] = data[i];
                data[i] = tmp; /* swap root to last */
                max_heap(data, 0, i - 1); /* end = i - 1, for next */
        }
}

int main()
{
        int i;
        int data[10] = {3,5,1,-7,4,9,-6,8,10,4};
        heap_sort(data, 10);
        for (i = 0; i < 10; i++) {
                printf("data %d %d\n", i, data[i]);
        }
        return 0;
}
```



### 归并排序

算法：归并排序的核心是分治递归，不断的递的过程中不断拆分，知道只有一个元素返回，归的过程中合并2个有序数组。

```
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
		ret_data[left] = data[left];  /* 只有一个元素 */
		return;
	}
	mid = (left + right) / 2;
	divide(data, left, mid);
	divide(data, mid + 1, right);
	left_index = left;
	right_index = mid + 1;
	for (loop = left; loop <= right; loop++) { /* 这里开始归并，将左右2个有序数组，归并到一起 */
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
```



### 基数排序
算法： 考虑整数或者字符串都是一样的，先将个位的排序，然后将结果按照十位的排序，然后再高位，这样最高的影响权重越大
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ARRAY_SIZE(x)        (sizeof((x)) / sizeof((x)[0]))
#define MAX(a, b)            ((a) > (b) ? (a) : (b))


int max_exp(int *data, int size)
{
	int loop;
	int count = 1;
	int base = 10;
	int max = INT_MIN;

	for (loop = 0; loop < size; loop++) {
		max = MAX(max, data[loop]);
	}
	while(max / base) {
		base = base * 10;
		count++;
	}
	return count;
}

void radix_sort(int *data, int size)
{
	int exp;
	int radix = 1;
	int i, j, z;
	int count[11] = { 0 };
	int index;

	int *tmp = (int *)malloc(sizeof(int) * size);
	exp = max_exp(data, size);
	printf("exp %d\n", exp);
	for (i = 1; i <= exp; i++) {
		memset(count, 0, sizeof(count));
		for (j = 0; j < size; j++) {
			index = (data[j] / radix) % 10; /* %10 is important */
			count[index]++;
		}
		for (z = 1; z <= 9; z++) {
			count[z] += count[z - 1];  /* 每个开始的位置等于前边的个数的和，count[1] = 0, 前边有个偏移 +1 */
		}
		for (j = size - 1; j >= 0; j--) {  /* 这里只能从后往前，让保持稳定 */
			index = (data[j] / radix) % 10;
			tmp[count[index] - 1] = data[j];
			count[index]--;
		}
		memcpy(data, tmp, sizeof(int) * size);
		radix = radix * 10;
		for (j = 0; j < size; j++) {
			printf("%d ", tmp[j]);
		}
		printf("\n");
	}
}

int main()
{
	int loop;
	int a[] = {121, 11, 131, 5, 65, 111, 89, 12, 89, 90, 100, 77, 11111, 99, 89};
	//int a[] = {91, 82, 73, 33, 44, 111};
	radix_sort(a, ARRAY_SIZE(a));
	printf("\n");
}
```

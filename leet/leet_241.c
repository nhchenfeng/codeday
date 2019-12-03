#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
分治算法，定义子问题为运算符左边解的集合，右边为子问题右边解的集合
最终的解，为左边的和右边的正交
定义子问题返回一个集合和集合的长度
*/

#define MAX_NODE  1024 * 2

bool is_number(char *src, int left, int right)
{
	int loop;
	for (loop = left; loop <= right; loop++) {
		if(!isdigit(src[loop]))
			return false;
	}
	return true;
}

int get_number(char *src, int left, int right)
{
	char data[100] = { 0 };
	memcpy(data, src + left, right - left + 1);
	return atoi(data);
}

void get_ops(int *left, int left_size, int *right, int right_size,
                  int *out, int *size, char op)
{
	int loop_left;
	int loop_right;

	//printf("left size %d right size %d\n", left_size, right_size);
	for (loop_left = 0; loop_left < left_size; loop_left++) {
		for (loop_right = 0; loop_right < right_size; loop_right++) {
			switch (op)
			{
			case '+':
				out[*size] = left[loop_left] + right[loop_right];
				*size += 1;
				break;
			case '-':
				out[*size] = left[loop_left] - right[loop_right];
				*size += 1;
				break;
			case '*':
				out[*size] = left[loop_left] * right[loop_right];
				*size += 1;
				break;
			default:
				break;
			}
		}
	}
}

void partition(int left, int right, char *src, int *out, int *size)
{
	long long ret;
	int loop;
	int left_size = 0;
	int right_size = 0;
	int ret_size = 0;
	int *left_out = NULL;
	int *right_out = NULL;
	int *ret_out = NULL;
	//printf("into [%d %d]\n", left, right);
	if (is_number(src, left, right)) {
		ret = get_number(src, left, right);
		*size = 1;
		out[0] = ret;
		return;
	}

	for (loop = left; loop <= right; loop++) {
		if (src[loop] == '+' || src[loop] == '-' ||
		    src[loop] == '*') {
			left_out = malloc(sizeof(int) * MAX_NODE);
			partition(left, loop - 1, src, left_out, &left_size);
			right_out = malloc(sizeof(int) * MAX_NODE);
			partition(loop + 1, right, src, right_out, &right_size);
			get_ops(left_out, left_size, right_out, right_size, out, &ret_size, src[loop]);
			free(left_out);
			free(right_out);
		}
	}
	*size = ret_size;
}

int *diffWaysToCompute(char *input, int *returnSize)
{
	int *ans;
	int ans_size;
	if (!input) {
		*returnSize = 0;
		return NULL;
	}
	ans = malloc(sizeof(int) * MAX_NODE);
	partition(0, strlen(input) - 1, input, ans, &ans_size);
	*returnSize = ans_size;
	return ans;
}

int main()
{
	int loop;
	int *ret;
	int ret_size;
	ret = diffWaysToCompute("2-1-1", &ret_size);
	for (loop = 0; loop < ret_size; loop++) {
		printf("%d\n", ret[loop]);
	}
}

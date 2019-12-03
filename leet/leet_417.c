#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
dp_ret(x,y) = {
	0 x < 0 y > max
	1  边界
	for (x,y) 相邻 且小于 x, y
	1 
*/

#define MAX_NODE    200

static int dp_left[MAX_NODE][MAX_NODE];
static int dp_right[MAX_NODE][MAX_NODE];
static int visit[MAX_NODE][MAX_NODE];
static int max_row;
static int max_col;

static int **ans_array;
static int ans_size;
static int *col_ret;

static int dir[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

static int is_okay(int row, int col, int **matrix, int next_row, int next_col)
{
	if (next_row >= 0 && next_row <= max_row - 1 &&
	    next_col >= 0 && next_col <= max_col - 1 &&
	    matrix[next_row][next_col] <= matrix[row][col]) {
		    return 1;
	    }
	return 0;
}

int dp(int row, int col, int **matrix, int dp_ret[MAX_NODE][MAX_NODE], int type)
{
	int loop;
	int next_row;
	int next_col;

	if (row < 0 || col < 0) {
		return 0;
	}
	visit[row][col] = 1;
	if (type == 0) {
		if (row == 0 || col == 0) {
			printf("%d %d is 1\n", row, col);
			dp_ret[row][col] = 1;
			return dp_ret[row][col];
		}
	} else if (type == 1){
		if (row == max_row - 1 || col == max_col - 1) {
			dp_ret[row][col] = 1;
			return dp_ret[row][col];
		}		
	}
	if (dp_ret[row][col] != -1) {
		return dp_ret[row][col];
	}
	for (loop = 0; loop < 4; loop++) {
		next_row = dir[loop][0] + row;
		next_col = dir[loop][1] + col;
		if (is_okay(row, col, matrix, next_row, next_col)) {

			//printf("from [%d %d] -> [%d %d]\n", row, col, next_row, next_col);
			if (dp_ret[next_row][next_col] == 1) {
				dp_ret[row][col] = 1;
				break;
			}
			if (!visit[next_row][next_col]) {
				if (dp(next_row, next_col, matrix, dp_ret, type) == 1) {
					dp_ret[row][col] = 1;
					break;
				}
			}
		}
	}
	visit[row][col] = 0;
	if (dp_ret[row][col] == -1) {
		dp_ret[row][col] = 0;
	} else if (dp_ret[row][col] == 1){
		//printf("%d %d is 1\n", row, col);
	}
	return dp_ret[row][col];
}

void add_ret(int row, int col)
{
	//printf("add %d %d\n", row, col);
	ans_array[ans_size][0] = row;
	ans_array[ans_size][1] = col;
	col_ret[ans_size] = 2;
	ans_size++;
}

void alloc_array(int row, int col)
{
	int loop;
	ans_array = malloc(row * col * sizeof(int *));
	col_ret = malloc(row * col * sizeof(int));
	for (loop = 0; loop < row * col; loop++) {
		ans_array[loop] = (int *)malloc(sizeof(int) * 2);
	}
}

int** pacificAtlantic(int** matrix, int matrixSize, int* matrixColSize,
		      int* returnSize, int** returnColumnSizes)
{
	int loop_row;
	int loop_col;
	ans_size = 0;
	if (!matrix || matrixSize == 0) {
		*returnSize = ans_size;
		*returnColumnSizes = NULL;
		return NULL;
	}
	max_row = matrixSize;
	max_col = *matrixColSize;
	alloc_array(max_row, max_col);
	memset(dp_left, -1, sizeof(dp_left));
	memset(dp_right, -1, sizeof(dp_right));
	for (loop_row = 0; loop_row < max_row; loop_row++) {
		for (loop_col = 0; loop_col < max_col; loop_col++) {
			memset(visit, 0, sizeof(visit));
			dp(loop_row, loop_col, matrix, dp_left, 0);
			memset(visit, 0, sizeof(visit));
			dp(loop_row, loop_col, matrix, dp_right, 1);
		}
	}
	for (loop_row = 0; loop_row < max_row; loop_row++) {
		for (loop_col = 0; loop_col < max_col; loop_col++) {
			if (dp_left[loop_row][loop_col] == 1 &&
			    dp_right[loop_row][loop_col] == 1) {
				    add_ret(loop_row, loop_col);
			    }
		}
	}
	*returnSize = ans_size;
	*returnColumnSizes = col_ret;
	return ans_array;
}
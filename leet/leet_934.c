#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int **map;
static int map_row;
static int map_col;

static int dir_list[][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
#define DIR_MAX         4

#define MAX_NODE  4096
struct node {
	int x;
	int y;
	int step;
};

static struct node list[MAX_NODE];
static int left;
static int right;

void show(int **data, int row, int col)
{
	int loop;
	int next;
	for (loop = 0; loop < row; loop++) {
		for (next = 0; next < col; next++) {
			printf("%d ", data[loop][next]);
		}
		printf("\n");
	}
}

int available(int row, int col)
{
	if (row >= 0 && row < map_row) {
		if (col >= 0 && col < map_col)
			return 1;
	}
	return 0;
}

void dfs(int row, int col, int index)
{
	int new_row;
	int new_col;
	int loop;
	struct node cur;
	map[row][col] = index;
	if (index == 2) {
		cur.x = row;
		cur.y = col;
		cur.step = 0;
		list[right++] = cur;
	}
	for (loop = 0; loop < DIR_MAX; loop++) {
		new_row = row + dir_list[loop][0];
		new_col = col + dir_list[loop][1];
		if (available(new_row, new_col) && map[new_row][new_col] == 1) {
			dfs(new_row, new_col, index);
		}
	}
}

int shortestBridge(int **A, int ASize, int *AColSize)
{
	int loop;
	int next;
	int index = 2;
	struct node pre;
	struct node cur;
	int new_x;
	int new_y;
	if (!A || !ASize) {
		return 0;
	}
	left = 0;
	right = 0;
	map = A;
	map_row = ASize;
	map_col = AColSize[0];
	//show(A, ASize, AColSize[0]);
	for (loop = 0; loop < ASize; loop++) {
		for (next = 0; next < AColSize[loop]; next++) {
			if (A[loop][next] == 1) {
				dfs(loop, next, index++);
			}
		}
	}
	//printf("current index %d\n", index);
	//show(A, ASize, AColSize[0]);
	while (left < right) {
		pre = list[left++];
		for (loop = 0; loop < DIR_MAX; loop++) {
			cur.x = pre.x + dir_list[loop][0];
			cur.y = pre.y + dir_list[loop][1];
			cur.step = pre.step + 1;
			if (available(cur.x, cur.y)) {
				if (map[cur.x][cur.y] == 3) {
					return pre.step;
				}
				if (map[cur.x][cur.y] == 0) {
					list[right++] = cur;
				}
			}
		}		
	}
	return 1;
}
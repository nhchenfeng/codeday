#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 4096 * 100

static int dir[][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
static int *dis;

struct node {
	int x;
	int y;
	struct node *pre;
};

static struct node list[MAX_NODE];
static int list_first;
static int list_last;

static void bfs(int **map, int row_max, int col_max)
{
	int loop;
	struct node pre;
	struct node cur;
	struct node *parent;
	int pre_node;
	int cur_node;
	dis[0] = map[0][0];
	list[list_first].x = 0;
	list[list_first].y = 0;
	list[list_first].pre = NULL;
	list_first++;

	while (list_last < list_first) {
		pre = list[list_last];
		parent = &list[list_last];
		list_last++;
		for (loop = 0; loop < 4; loop++) {
			cur.x = pre.x + dir[loop][0];
			cur.y = pre.y + dir[loop][1];
			cur.pre = parent;
			if (cur.x >= 0 && cur.x < row_max && cur.y >= 0 &&
			    cur.y < col_max) {
				pre_node = pre.x * col_max + pre.y;
				cur_node = cur.x * col_max + cur.y;
				if (dis[pre_node] + map[cur.x][cur.y] <
					    dis[cur_node] ||
				    dis[cur_node] == -1) {
					dis[cur_node] = dis[pre_node] + map[cur.x][cur.y];
					list[list_first] = cur;
					list_first++;
				}
			}
		}
	}
}

int minPathSum(int **grid, int gridSize, int *gridColSize)
{
	int row;
	int col;
	int size;

	if (!grid || !gridSize || !gridColSize || !gridColSize[0]) {
		return 0;
	}
	row = gridSize;
	col = gridColSize[0];
	size = row * col;
	list_first = 0;
	list_last = 0;
	dis = (int *)malloc(sizeof(int) * size);
	memset(dis, -1, sizeof(int) * size);
	bfs(grid, row, col);
	return dis[row * col - 1];
}
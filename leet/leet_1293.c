#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int x;
	int y;
	int use;
	int step;
};

#define MAX_NODE   4096 * 10
static struct node list[MAX_NODE];
static int list_first;
static int list_last;
static int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

static inline int is_okay(int x, int y, int row, int col)
{
	if (x >= 0 && x < row && y >= 0 && y < col)
		return 1;
	return 0;
}

int shortestPath(int **grid, int gridSize, int *gridColSize, int k)
{
	int loop;
	int new_x;
	int new_y;
	struct node pre = { 0 };
	struct node cur = { 0 };
	if (!grid || gridSize == 0 || *gridColSize == 0) {
        printf("init zero\n");
		return 0;
	}
	int visit[gridSize][*gridColSize];
	memset(visit, 0x0f, sizeof(visit));
	list_first = 0;
	list_last = 0;
	cur.step = 0;
	cur.x = 0;
	cur.y = 0;
	cur.use = 0;
	list[list_first++] = cur;
	while (list_last < list_first)
	{
		pre = list[list_last++];
		if (pre.x == gridSize - 1 && pre.y == *gridColSize - 1)
			return pre.step;
		for (loop = 0; loop < 4; loop++) {
			cur.x = pre.x + dir[loop][0];
			cur.y = pre.y + dir[loop][1];
			cur.step = pre.step + 1;
			cur.use = pre.use;
            		// printf("new %d %d\n", cur.x, cur.y);
			if (is_okay(cur.x, cur.y, gridSize, *gridColSize)) {
                		// printf("okay %d %d\n", cur.x, cur.y);
				if (grid[cur.x][cur.y] == 1) {
					cur.use = pre.use + 1;
				}
				if (cur.use <= k && cur.use < visit[cur.x][cur.y]) {
                    			// printf("add %d %d\n", cur.x, cur.y);
					visit[cur.x][cur.y] = cur.use;
					list[list_first++] = cur;
				}
			}
		}
	}
	return -1;
}
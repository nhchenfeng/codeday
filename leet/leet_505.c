#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
=======
#include <math.h>
#include <limits.h>

#define MAX_NODE  4096 * 10
#define MAX_MAP   100
#define MAX_DIR   4

struct node {
	int x;
	int y;
	int dir;
};

static int dir_list[MAX_DIR][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

static struct node list[MAX_NODE];
static int left;
static int right;

static int max_row;
static int max_col;
static int **map;

static int dis[MAX_DIR][MAX_MAP * MAX_MAP];
static int flag[MAX_DIR][MAX_MAP * MAX_MAP];

static int is_okay(int x, int y)
{
	if (x >= 0 && x < max_row) {
		if (y >= 0 && y < max_col) {
			if (map[x][y] == 0)
				return 1;
		}
	}
	return 0;
}

static void init_local(int **maze, int start_x, int start_y)
{
	int new_x;
	int new_y;
	int loop;
	struct node cur;

	left = 0;
	right = 0;
	memset(flag, 0, sizeof(flag));
	for (loop = 0; loop < MAX_DIR; loop++) {
		new_x = dir_list[loop][0] + start_x;
		new_y = dir_list[loop][1] + start_y;
		if (is_okay(new_x, new_y)) {
			cur.x = new_x;
			cur.y = new_y;
			cur.dir = loop;
			dis[loop][cur.x * max_col + cur.y] = 1;
			list[right++] = cur;
		}
	}
}
>>>>>>> 801bf7f018e66395f8dcac1706efc145a4150e76

int shortestDistance(int **maze, int mazeSize, int *mazeColSize, int *start,
		     int startSize, int *destination, int destinationSize)
{
<<<<<<< HEAD
=======
	int loop;
	int ans = INT_MAX;
	struct node pre;
	struct node cur;
	int dis_pre;
	int new_x;
	int new_y;
	if (!maze || !mazeSize || !start || !destination) {
		return -1;
	}
	max_row = mazeSize;
	max_col = mazeColSize[0];
	map = maze;
	memset(dis, -1, sizeof(dis));

	init_local(maze, start[0], start[1]);
	while(left < right) {
		pre = list[left++];
		dis_pre = dis[pre.dir][pre.x * max_col + pre.y];
		new_x = pre.x + dir_list[pre.dir][0];
		new_y = pre.y + dir_list[pre.dir][1];
		if (is_okay(new_x, new_y)) {
			if (dis[pre.dir][new_x * max_col + new_y] == -1 ||
			    dis_pre + 1 < dis[pre.dir][new_x * max_col + new_y]) {
				cur.x = new_x;
				cur.y = new_y;
				cur.dir = pre.dir;
				dis[pre.dir][cur.x * max_col + cur.y] = dis_pre + 1;
				list[right++] = cur;
			}
		} else {
			flag[pre.x * max_col + pre.y] = 1;
			for (loop = 0; loop < MAX_DIR; loop++) {
				new_x = dir_list[loop][0] + pre.x;
				new_y = dir_list[loop][1] + pre.y;
				if (is_okay(new_x, new_y)) {
					if (dis[loop][new_x * max_col + new_y] == -1 ||
					    dis_pre + 1 < dis[loop][new_x * max_col + new_y]) {
						cur.x = new_x;
						cur.y = new_y;
						cur.dir = loop;
						dis[loop][cur.x * max_col + cur.y] = dis_pre + 1;
						list[right++] = cur;
					}
				}
			}			
		}
	}
	for (loop = 0; loop < MAX_DIR; loop++) {
		if (dis[loop][destination[0] * max_col + destination[1]] != -1 && flag[destination[0] * max_col + destination[1]]) {
			ans = fmin(ans, dis[loop][destination[0] * max_col + destination[1]]);
		}
	}
	return (ans == INT_MAX) ? -1 : ans;
>>>>>>> 801bf7f018e66395f8dcac1706efc145a4150e76
}
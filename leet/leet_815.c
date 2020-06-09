#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_LIST  4096
#define MAX_NODE  500

static char map[MAX_NODE][MAX_NODE];
static int dis[500];
static char mark[MAX_NODE];
static int list[MAX_LIST];
static int left;
static int right;
static int start;
static int end;

static int is_okay(int *src, int *dst, int src_size, int dst_size)
{
	int loop;
	int next;

	for (loop = 0; loop < src_size; loop++) {
		for (next = 0; next < dst_size; next++) {
			if (src[loop] == dst[next]) {
				return 1;
			}
		}
	}
	return 0;
}

static void set_map(int **routes, int routesSize, int *routesColSize)
{
	int loop;
	int next;
	int col;

	memset(map, 0, sizeof(map));
	memset(dis, -1, sizeof(dis));
	memset(mark, 0, sizeof(mark));
	left = 0;
	right = 0;
	for (loop = 0; loop < routesSize; loop++) {
		for (col = 0; col < routesColSize[loop]; col++) {
			if (routes[loop][col] == start) {
				dis[loop] = 1;
				list[right++] = loop;
			}
			if (routes[loop][col] == end) {
				mark[loop] = 1;
			}
		}
		for (next = loop + 1; next < routesSize; next++) {
			if (is_okay(routes[loop], routes[next], routesColSize[loop], routesColSize[next])) {
				map[loop][next] = 1;
				map[next][loop] = 1;
			}
		}
	}
}

int numBusesToDestination(int **routes, int routesSize, int *routesColSize,
			  int S, int T)
{
	int pre;
	int cur;
	int loop;
	int next;
	int have = 0;

	int ans = INT_MAX;

	if (!routes || !routesSize) {
		return -1;
	}
	start = S;
	end = T;
	if (start == end)
		return 0;
	set_map(routes, routesSize, routesColSize);

	while (left < right) {
		pre = list[left++];
		for (loop = 0; loop < routesSize; loop++) {
			if (map[pre][loop]) {
				if (dis[loop] == -1 || dis[pre] + 1 < dis[loop]) {
					dis[loop] = dis[pre] + 1;
					list[right++] = loop;
				}
			}
		}
	}
	return -1;
}
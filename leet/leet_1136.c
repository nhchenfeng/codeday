#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MAX_NODE   5001
static int max;

struct edge_
{
	int to;
	int w;
	int next;
};

static struct edge_ edge[MAX_NODE];
static int head[MAX_NODE];
static int cnt;

static int order[MAX_NODE];

struct node {
	int step;
	int data;
};

static struct node list[MAX_NODE];
static int list_first;
static int list_last;

void init_local()
{
	memset(head, -1, sizeof(head));
	cnt = 0;
}
void add_edge(int from, int to, int w)
{
	edge[cnt].to = to;
	edge[cnt].w = w;
	edge[cnt].next = head[from];
	head[from] = cnt++;  /* insert to the first index */
}
/*
	from index-> a; index -> b； into  a, b
	for(loop = head[index]; loop != -1; loop = edge[loop].next) {
		dfs(edge[loop].to);
	}
*/

void bfs()
{
	int loop;
	struct node pre;
	while(list_last < list_first) {
		pre = list[list_last];
		list_last++;
		for(loop = head[pre.data]; loop != -1; loop = edge[loop].next) {
			order[edge[loop].to]--;
			if (order[edge[loop].to] == 0) {
				list[list_first].step = pre.step + 1;
				list[list_first].data = edge[loop].to;
				list_first++;
				max = MAX(max, pre.step + 1);
			}
		}
	}
}

int minimumSemesters(int N, int **relations,
		     int relationsSize, int* relationsColSize)
{
	int loop;

	init_local();
	memset(order, 0 , sizeof(order));
	memset(list, 0, sizeof(list));
	max = 0;

	if (relationsSize == 0 || !relations) {
		return 1;
	}
	for (loop = 0; loop < relationsSize; loop++) {
		add_edge(relations[loop][0], relations[loop][1], 0);
		order[relations[loop][1]]++;
	}

	for (loop = 0; loop < N; loop++) {
		if (order[loop] == 0) {
			list[list_first].data = loop;
			list[list_first].step = 1;
			list_first++;
		}
	}
	bfs();
	for (loop = 0; loop < N; loop++) {
		if (order[loop] != 0) {
			return -1;
		}
	}
	return max;
}
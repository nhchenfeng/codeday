#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NODE   1024 * 1024

struct edge_
{
	int to;
	int w;
	int next;
};

static struct edge_ edge[MAX_NODE];
static int head[MAX_NODE];
static int cnt;

static int ret_array[MAX_NODE];
static int ret_size;

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

void add_ret(int data)
{
	ret_array[ret_size] = data;
	ret_size++;
}

void dfs(int index)
{
	int loop;
	add_ret(index);
	for(loop = head[index]; loop != -1; loop = edge[loop].next) {
		dfs(edge[loop].to);
	}
}

int* killProcess(int *pid, int pidSize, int *ppid, int ppidSize, int kill, int *returnSize)
{
	int loop;
	int i;
	int j;
	init_local();
	ret_size = 0;
	for (loop = 0; loop < pidSize; loop++) {
		printf("add %d -> %d\n", ppid[loop], pid[loop]);
		add_edge(ppid[loop], pid[loop], 0);
	}
	add_ret(kill);
	*returnSize = ret_size;
	return ret_array;
}

int main()
{
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODE   1024 * 1024
#define MAX(a, b)  ((a) > (b) ? (a) : (b))

static int ret_array[MAX_NODE];
static int visit[MAX_NODE];
static int ret_size;
static int local_father[MAX_NODE];
static int max_size;

void init(int n, int *father)
{
	int i;

	for (i = 0; i < n; i++) {
		father[i] = i;
	}
}

int find(int x, int *father)
{
	printf("find x %d fx %d\n", x, father[x]);
	if (x != father[x]) {
		father[x] = find(father[x], father);
	}

	return father[x];
}

void union_circle(int x, int y, int *father)
{
	int fx = find(x, father);
	int fy = find(y, father);

	if (fx != fy) {
		father[fx]= fy;
	}
}

void add_ret(int data)
{
	ret_array[ret_size] = data;
	ret_size++;
}

void dfs(int index, int size, int *father)
{
	int loop;
	add_ret(index);
	visit[index] = 1;
	for(loop = 0; loop < size; loop++) {
		//printf("%d father %d\n", loop, find(loop, father));
		if (find(loop, father) == index && !visit[loop]) {
			visit[loop] = 1;
			dfs(loop, size, father);
		}
	}
}

int* killProcess(int *pid, int pidSize, int *ppid, int ppidSize,
		 int kill, int *returnSize)
{
	int loop;
	ret_size = 0;
	max_size = 0;
	memset(visit, 0, sizeof(visit));
	
	init(MAX_NODE, local_father);
	for(loop = 0; loop < pidSize; loop++) {
		union_circle(pid[loop], ppid[loop], local_father);
		max_size = MAX(max_size, pid[loop]);
		max_size = MAX(max_size, ppid[loop]);
	}
	dfs(kill, max_size, local_father);
	*returnSize = ret_size;
	return ret_array;
}
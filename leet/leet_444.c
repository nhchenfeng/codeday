#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10001
#define MAX_NODE (4096 * 10)

static int order[MAX_LEN];

static int list[MAX_NODE];
static int left;
static int right;

static int ans[MAX_LEN];
static int ans_size;

static int added[MAX_LEN];

#define MAX_EDGE 1024 * 400

struct edge_ {
	int to;
	int w;
	int next;
};

static struct edge_ edge[MAX_EDGE];
static int head[MAX_EDGE];
static int cnt;
void init_local()
{
	memset(head, -1, sizeof(head));
	memset(order, -1, sizeof(order));
	memset(added, 0, sizeof(added));
	left = 0;
	right = 0;
	ans_size = 0;
	cnt = 0;
}

void add_edge(int from, int to, int w)
{
	edge[cnt].to = to;
	edge[cnt].w = w;
	edge[cnt].next = head[from];
	head[from] = cnt++; /* insert to the first index */
}

bool sequenceReconstruction(int *org, int orgSize, int **seqs, int seqsSize,
			    int *seqsColSize)
{
	int loop;
	int next;
	int size;
	int pre;
	int cur;

	if (!org || !orgSize || !seqs || !seqsSize) {
		printf("input error\n");
		return false;
	}

	init_local();
	for (loop = 0; loop < seqsSize; loop++) {
		for (next = 0; next < seqsColSize[loop]; next++) {
			if (seqs[loop][next] < 0 || seqs[loop][next] > 10000) {
				printf("value over false\n");
				return false;
			}
			if (seqsColSize[loop] > orgSize)
				return false;
			added[seqs[loop][next]] = 1;
			order[seqs[loop][next]] = 0;
		}
	}
	for (loop = 0; loop < seqsSize; loop++) {
		for (next = 0; next < seqsColSize[loop] - 1; next++) {
			add_edge(seqs[loop][next], seqs[loop][next + 1], 1);
			order[seqs[loop][next + 1]]++;
		}
	}
	for (loop = 0; loop < MAX_LEN; loop++) {
		if (added[loop] && !order[loop]) {
			list[right++] = loop;
		}
	}

	while (left < right) {
		if (right - left > 1) {
			printf("over 1 false\n");
			return false;
		}
		pre = list[left++];
		ans[ans_size++] = pre;
		for (loop = head[pre]; loop != -1; loop = edge[loop].next) {
			order[edge[loop].to]--;
			if (!order[edge[loop].to]) {
				list[right++] = edge[loop].to;
			}
		}
	}
	if (ans_size != orgSize) {
		printf("size not equal false ans_size %d expect %d\n", ans_size,
		       orgSize);
		return false;
	}
	for (loop = 0; loop < ans_size; loop++) {
		if (ans[loop] != org[loop]) {
			printf("ans value not match\n");
			return false;
		}
	}
	return true;
}

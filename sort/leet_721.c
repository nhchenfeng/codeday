#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char *name;
	char *email;
	int index;
	int mark;
};

static struct node node_array[100000];
static int father[100000];
static int node_size;

void init(int n)
{
        int i;

        for (i = 0; i < n; i++) {
                father[i] = i;
        }
}

int find(int x)
{
        if (x != father[x]) {
                father[x] = find(father[x]);
        }

        return father[x];
}

void union_circle(int x, int y)
{
        int fx = find(x);
        int fy = find(y);

        if (fx != fy) {
                father[fx]= fy;
        }
}

char *** accountsMerge(char *** accounts, int accountsSize, int* accountsColSize, int* returnSize, int** returnColumnSizes)
{
	int row;
	int col;
	int index;
	node_size = 0;

	if (!accounts || accountsSize == 0) {
		*returnSize = 0;
		return NULL;
	}

	init(100000);

	for (row = 0; row < accountsSize; row++) {
		for (col = 0; col < *accountsColSize; col++) {
			node_array[node_size].email = accounts[row][col];
			node_array[node_size].name = accounts[row][0];
			node_array[node_size].index = node_size;
			node_size++;
		}
		for (index = *accountsColSize - 1; index > 0; index--) {
			union_circle(node_array[index].index, node_array[0].index);
		}
	}
}

int main()
{
	return 0;
}
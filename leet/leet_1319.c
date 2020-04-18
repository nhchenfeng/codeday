#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void init(int n, int *father)
{
        int i;

        for (i = 0; i < n; i++) {
                father[i] = i;
        }
}

int find(int x, int *father)
{
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

int makeConnected(int n, int **connections, int connectionsSize,
		  int *connectionsColSize)
{
	int loop;
	int *father;
	int first;
	int second;
	int enough = 0;
	int need = 0;

	if (n == 0) {
		return 0;
	}

	if (!connections || !connectionsSize) {
		return -1;
	}
	father = (int *)malloc(n * sizeof(int));
	init(n, father);
	for (loop = 0; loop < connectionsSize; loop++) {
		first = fmin(connections[loop][0], connections[loop][1]);
		second = fmax(connections[loop][0], connections[loop][1]);
		if (find(first, father) != find(second, father))
			union_circle(second, first, father);
		else {
			enough++;
			union_circle(second, first, father);
		}
	}
	for (loop = 0; loop < n; loop++) {
		if (find(n, father) == n) {
			need++;
		}
	}
	if (enough >= need) {
		return need;
	}
	return -1;
}
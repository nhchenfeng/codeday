#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
先求差分数组，然后一一还原元数组，看原数组是否超过capacity
*/

#define MAX_NODE 1005

static int a[MAX_NODE];
static int b[MAX_NODE];

bool carPooling(int **trips, int tripsSize, int *tripsColSize, int capacity)
{
	int loop;
	int sum = 0;

	if (!trips || !tripsSize) {
		return true;
	}

	memset(b, 0, sizeof(b));
	memset(a, 0, sizeof(a));
	for (loop = 0; loop < tripsSize; loop++) {
		b[trips[loop][1]] += trips[loop][0];
		b[trips[loop][2]] -= trips[loop][0];
	}
	for (loop = 0; loop < MAX_NODE; loop++) {
		sum += b[loop];
		a[loop] = sum;
		if (a[loop] > capacity)
			return false;
	}
	return true;
}
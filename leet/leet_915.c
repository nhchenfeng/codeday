#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b)         ((a) > (b) ? (a) : (b))

#define MAX_NODE  30001

int partitionDisjoint(int *A, int ASize)
{
	int loop;
	if (!A || ASize == 0) {
		return 0;
	}
	int index = 0;
	int max = -1;
	int left_max = A[0];
	for (loop = index; loop < ASize; loop++) {
		max = MAX(max, A[loop]);
		if (A[loop] < left_max) {
			index = loop;
			left_max= max;
		}
	}
	return index + 1;
}
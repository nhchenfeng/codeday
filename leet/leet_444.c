#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static int order[10000 + 1];

bool sequenceReconstruction(int *org, int orgSize, int **seqs, int seqsSize,
			    int *seqsColSize)
{
	int loop;
	int next;

	memset(order, 0, sizeof(order));
	for (loop = 0; loop < seqsSize; loop++) {
		
	}
}

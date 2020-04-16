#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE  20001

static int a[MAX_NODE];
static int b[MAX_NODE];

/*
b[0] = a[0];
a[i] = b[0] + b[1] + ... + b[i] 从第一个一直+差分 到最后一个
*/

int *corpFlightBookings(int **bookings, int bookingsSize, int *bookingsColSize,
			int n, int *returnSize)
{
	int loop;

	if (!bookings || !bookingsSize) {
		*returnSize = 0;
		return NULL;
	}
	memset(b, 0, sizeof(b));
	for (loop = 0; loop < bookingsSize; loop++) {
		b[bookings[loop][0]] += bookings[loop][2];
		b[bookings[loop][1] + 1] -= bookings[loop][2];
	}

	for (loop = 0; loop < n; loop++) {
		a[loop] += b[loop];
	}
	*returnSize = n;
	return a;
}
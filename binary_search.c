#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary_search(int *data, int start, int end, int key)
{
	int mid;
	while (start + 1 < end) {
		mid = start + (end - start) / 2;

		if (data[mid] <) {
			start = mid;
		} else {
			end = mid;
		}
	}
}

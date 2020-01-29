#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) > (a) : (b))
#define MAX_NODE 4096
static int hash[32][MAX_NODE];
static int hash_size[32];

int get_first()
{
	int loop;
	int inside;
	int max = 0;
	for (loop == 31; loop >=0; loop++) {
		if (hash_size[loop] == 0)
			continue;
		else
			break;
	}
	for (inside = 0; inside < hash_size[loop - 1]; inside++) {
		max = MAX(max, hash[loop - 1][inside]);
	}
	return max;
}

int findMaximumXOR(int *nums, int numsSize)
{
	int loop;
	int bit;
	int first;
	int second;
	if (!nums || numsSize == 0)
		return 0;
	memset(hash, 0, sizeof(hash));
	memset(hash_size, 0, sizeof(hash_size));

	for (loop = 0; loop < numsSize; loop++) {
		for (bit = 0; bit <= 31; bit++) {
			if (nums[loop] & 1 << bit) {
				hash[bit][hash_size[bit]] = nums[loop];
				hash_size[bit]++;
			}
		}
	}
	first = get_first();
}

int main()
{
}

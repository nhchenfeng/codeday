#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *partition;
static int partition_size;

int maxProfit(int *prices, int pricesSize)
{
	int pre;
	int tmp;
	int loop;
	int ret = 0;
	if (!pricesSize || pricesSize == 0)
		return 0;
	partition = malloc(sizeof(int) * pricesSize);
	partition_size = 0;
	pre = prices[0];
	for (loop = 0; loop < pricesSize; loop++) {
		tmp = prices[loop];
		if (tmp > pre) {
			ret += tmp - pre;
		}
		pre = tmp;
	}
	return ret;
}

int main()
{
	return 0;
}

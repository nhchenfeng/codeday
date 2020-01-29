/*
计算2个字符串的差值放到一个数组
求数组和小于等于cost的最大子数组长度，滑动窗口
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b)    ((a) > (b) ? (a) : (b))
#define MAX_NODE     256
#define MAX_SIZE     100001

static int hash[MAX_NODE];
static char data[MAX_SIZE];

int equalSubstring(char *s, char *t, int maxCost)
{
	int left = 0;
	int right = 0;
	int max = 0;
	int cost = 0;
	if (!s || !t || strlen(s) == 0 || strlen(t) == 0)
		return 0;
	memset(hash, 0, sizeof(hash));
	for (right = 0; right < strlen(s); right++) {
		data[right] = abs(*(s + right) - *(t + right));
	}
	for (right = 0; right < strlen(s); right++) {
		cost += data[right];
		while(left < right && cost > maxCost) {
			cost -= data[left];
			left++;
		}
		max = MAX(max, right - left + 1);
	}
	return max;
}

int main()
{
}

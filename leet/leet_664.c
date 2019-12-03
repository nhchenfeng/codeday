#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#define MAX_NODE    200
static int dp_ret[MAX_NODE][MAX_NODE];
#define INF_MAX     9999999

int dp(int start, int end, char *str)
{
	int loop;
	int min = INF_MAX;
	if (start > end) {
		//printf("start %d < end %d\n", start, end);
		return 0;
	}
	if (start == end) {
		dp_ret[start][end] = 1;
		//printf("init start %d end %d to %d\n", start, end, dp_ret[start][end]);
		return dp_ret[start][end];
	}
	if (dp_ret[start][end] != 2139062143) {
		return dp_ret[start][end];
	}
	for (loop = start; loop < end; loop++) {
		if (str[loop] == str[end]) {
			dp_ret[start][end] = MIN((dp(start, loop, str) + dp(loop + 1, end - 1, str)), dp_ret[start][end]);
		}
	}
	dp_ret[start][end] = MIN(dp_ret[start][end], dp(start, end - 1, str) + 1);
	//printf("dp out %d %d to %d\n", start, end, dp_ret[start][end]);
	return dp_ret[start][end];
}

int strangePrinter(char *s)
{
	if (!s || strlen(s) == 0)
		return 0;
	memset(dp_ret, INF_MAX, sizeof(dp_ret));
	dp(0, strlen(s) - 1, s);
	return dp_ret[0][strlen(s) - 1];
}
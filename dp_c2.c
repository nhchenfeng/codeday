#include <stdio.h>
#include <string.h>
#define N 50
int main()
{
	char s1[N], s2[N];
	int dp[N][N], i, j, max_len = 0;
	gets(s1);
	gets(s2);
	for (i = 0; i < strlen(s1); i++) {
		for (j = 0; j < strlen(s2); j++) {
			if (s1[i] == s2[j]) {
				if (i > 0 && j > 0) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				} else {
					dp[i][j] = 1;
				}
				if (max_len < dp[i][j]) {
					max_len = dp[i][j];
				}
			}
		}
	}
	printf("%d\n", max_len);
	return 0;
}


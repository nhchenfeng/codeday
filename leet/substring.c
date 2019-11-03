#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
求 str1和 str2的最长相同子串
设 dp(x, y) 包含 x, y 为结尾，且包含 x, y 项的最长子串
dp(x)(y) = {
        dp(x - 1)(y - 1) + 1;（str1[x] == str2[y])
        0； (str1[x] != str2[y])
        0 (x < 0, y < 0)
}
*/

#define MAX_NODE 100
#define max(a, b) ((a) > (b) ? (a) : (b))

static int dp_ret[MAX_NODE][MAX_NODE];
static char *str1;
static char *str2;

int dp_substr(int x, int y)
{
        if (x < 0 || y < 0) {
                return 0;
        }
        if (dp_ret[x][y] != -1) {
                return dp_ret[x][y];
        }
        if (str1[x] == str2[y]) {
                dp_ret[x][y] = dp_substr(x - 1, y - 1) + 1;
                return dp_ret[x][y];
        } else {
                dp_ret[x][y] = 0;
                return dp_ret[x][y];
        }
}

/*
求 str1和 str2的最长子序列
设 dp(x, y) 以 x, y 的为结尾，且包含 x, y 项的最长子序列
dp(x)(y) = {
        dp(x - 1)(y - 1) + 1;（str1[x] == str2[y])
        max(dp(x - 1, y), dp(x, y - 1)； (str1[x] != str2[y])
        0 (x < 0, y < 0)
}
*/
int dp_sublist(int x, int y)
{
        if (x < 0 || y < 0) {
                return 0;
        }
        if (dp_ret[x][y] != -1) {
                return dp_ret[x][y];
        }
        if (str1[x] == str2[y]) {
                dp_ret[x][y] = dp_sublist(x - 1, y - 1) + 1;
                return dp_ret[x][y];
        } else {
                dp_ret[x][y] = max(dp_sublist(x - 1, y), dp_sublist(x, y - 1));
                return dp_ret[x][y];
        }       
}

int main()
{
        char *data1 = "abcde";
        char *data2 = "ace";
        memset(dp_ret, -1, sizeof(dp_ret));
        str1 = data1;
        str2 = data2;
        dp_sublist(strlen(str1) - 1, strlen(str2) - 1);
        printf("%d\n", dp_ret[strlen(str1) - 1][strlen(str2) - 1]);
}
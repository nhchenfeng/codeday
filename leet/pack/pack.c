#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
第i个物品的费用是 c[i], 价值是 w[i]
求在费用为 v 的情况下，价值最大

dp(n, v) = {
        max[dp(n - 1, v - c[i]) + w[i], dp(n - 1, v)]  (v - c[i] >= 0)
        dp(n - 1, v) (v - c[i] < 0 ) 装不下这一个
        0; n < 0 || v < 0 
}
*/

#define NODE_MAX 1000
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static int dp_ret[NODE_MAX][NODE_MAX];

int dp(int *cost, int *value, int index, int total)
{
        if (index < 0 || total < 0) {
                return 0;
        }
        if (dp_ret[index][total] != -1) {
                return dp_ret[index][total];
        }
        if (total - cost[index] >= 0) {   /* 可以等于0 装满 */
                dp_ret[index][total] = MAX(dp(cost, value, index - 1, total - cost[index]) + value[index],
                                           dp(cost, value, index - 1, total));
        } else {  /* 装不下这一个 */
                dp_ret[index][total] = dp(cost, value, index - 1, total);
        }

        printf("dp out [%d][%d]   -> [%d]\n", index, total, dp_ret[index][total]);
        return dp_ret[index][total];
}

int main()
{
        memset(dp_ret, -1, sizeof(dp_ret));
        int cost[] = {1, 2, 3, 2};  /* 费用 */
        int value[] = {4, 6, 12, 7};
        dp(cost, value, 3, 6);
        printf("%d\n", dp_ret[3][6]);
        return 0;
}
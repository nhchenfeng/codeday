#include <stdio.h>
#include <string.h>
#include <stdio.h>

/*
dp(x) 表示以 x 为结尾的最长子串
dp(x) = {
        dp(y) + 1 if (data[y] > data[x], y 从0 到 x - 1)
        0 (没有这样的 y)
        1; (x == 0)
}
*/

#define MAX_NODE   1000
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static int dp_ret[MAX_NODE];
static int max = 0;

int dp(int x, int size, int *data)
{
        int index;
        if (x == 0) {
                dp_ret[x] = 1;
                return dp_ret[x];
        }
        if (dp_ret[x] != -1) {
                return dp_ret[x];
        }
        for (index = 0; index < x; index++) {
                if (data[index] < data[x]) {
                        dp_ret[x] = MAX(dp(index, size, data) + 1, dp_ret[x]); /*注意这里不能 return 需要求完*/
                }
        }
        if (dp_ret[x] == -1) {
                dp_ret[x] = 1;
        }
        return dp_ret[x];
}

int get_max(int *data, int size)
{
        int index;
        int max = 0;
        for (index = 0; index < size; index++) {
                if (data[index] > max) {
                        max = data[index];
                }
        }
        return max;
}

int lengthOfLIS(int* nums, int numsSize)
{
        int index;
        if (!nums || !numsSize)
                return 0;
        memset(dp_ret, -1, sizeof(dp_ret));
        for (index = 0; index < numsSize; index++) {
                dp(index, numsSize, nums);
        }
        return get_max(dp_ret, numsSize);
}

int main()
{
        int ret;
        int data[] = {10,9,2,5,3,7,101,18};
        ret = lengthOfLIS(data, ARRAY_SIZE(data));
        printf("%d\n", ret);
        return 0;
}
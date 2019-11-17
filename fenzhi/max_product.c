#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF_MIN          -999999
#define INF_MAX          999999
#define MAX(a, b)        ((a) > (b) ? (a) : (b))
#define MIN(a, b)        ((a) < (b) ? (a) : (b))
#define ARRAY_SIZE(x)    (sizeof(x) / sizeof((x)[0]))

int divide(int *data, int left, int right)
{
    int loop;
    int mid;
    int s1_max = INF_MIN;
    int s1_min = INF_MAX;
    int s2_max = INF_MIN;
    int s2_min = INF_MAX;
    int tmp_s1 = 0;
    int tmp_s2 = 0;
    int ret_left;
    int ret_right;
    int ret_mid = INF_MIN;
    int ret = INF_MIN;

    if (left == right) {
        return data[left];
    }
    mid = (left + right) / 2;
    ret_left = divide(data, left, mid);
    ret_right = divide(data, mid + 1, right);

    tmp_s1 = 1;
    for (loop = mid; loop >= 0; loop--) {
        tmp_s1 = tmp_s1 * data[loop];
        s1_max = MAX(s1_max, tmp_s1);
        s1_min = MIN(s1_min, tmp_s1);
    }
    tmp_s2 = 1;
    for (loop = mid + 1; loop <= right; loop++) {
        tmp_s2 = tmp_s2 * data[loop];
        s2_max = MAX(s2_max, tmp_s2);
        s2_min = MIN(s2_min, tmp_s2);
    }
    ret_mid = MAX(ret_mid, s1_min * s2_max);
    ret_mid = MAX(ret_mid, s1_min * s2_min);
    ret_mid = MAX(ret_mid, s1_max * s2_max);
    ret_mid = MAX(ret_mid, s1_max * s2_min);
    //printf("[%d %d] s1 %d %d s2 %d %d ret_mid %d\n", left, right, s1_min, s1_max, s2_min, s2_max, ret_mid);

    ret = MAX(ret_left, ret_right);
    ret = MAX(ret, ret_mid);
    //printf("[%d %d] ret %d\n", left, right, ret);
    return ret;
}

int maxProduct(int *nums, int numsSize)
{
    int ret;
    ret = divide(nums, 0, numsSize - 1);
    printf("max product %d\n", ret);
    return ret;
}

int main()
{
    int ret;
    int local_data[] = {-2,1};
    ret = maxProduct(local_data, ARRAY_SIZE(local_data));
    return 0;
}
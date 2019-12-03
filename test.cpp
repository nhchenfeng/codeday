int max(int a, int b)
{
    return (a > b) ? a : b;
}

int maxSubArrayLen(int* nums, int numsSize, int k)
{
    int i;
    int j;
    int sum = 0;
    int maxLen = 0;

    if ((nums == 0) || (numsSize == 0)) {
        return 0;
    }
    int dpSum[numsSize + 1];
    memset(dpSum, 0, sizeof(int) * (numsSize + 1));

    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
        dpSum[i+1] = sum;
        for (j = i; j >= 0; j--) {
            if ((dpSum[i+1] - dpSum[j]) == k) {
                maxLen = max(maxLen, i - j +  1);
            }
        }
    }

    return maxLen;
}

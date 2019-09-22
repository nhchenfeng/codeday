/*
 * 设滑雪数组为a[m][n]
 * 分别求a[0][0] ~ a[m][n]的最长路径放到数组b[0] ~ b[m*n - 1]中
 * 然后遍历数组b求其中的最大长度即可
 * 以a[i][j]为结尾的最长路径为：
 * 1、找到(a[i-1][j],a[i+1][j],a[i][j-1],a[i][j+1]) < a[i][j],则b[i*j] = max(b[找到的]) + 1,可能找到多个
 * 2、找不到上述条件，则b[i][j] = 0
 *
 * f(i,j) = 
 * 	if (i == 0 && j == 0)
 * 		= 0
 * 	if (a[i-1][j],a[i+1][j],a[i][j-1],a[i][j+1]) < a[i][j]) (i-1 >=0 || j -1 >= 0)
 * 		= max(f(i-i,j) (i+1,j) (i, j-1) (i, j +1)) + 1
 * 	else
 * 		= 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lcs(int arrary[][5], int m, int n, int *b)
{
	int longest = 0;
	int i;
	int j;
	int temp = 0;
	int max = 0;
	if (m == 0 && n == 0) {
		if (b[0] == 0)
			b[0] = 0;
		return 0;
	}

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (i - 1 >= 0 && arrary[i - 1][j] < arrary[i][j]) {
				if (b[i * 5 + j])
					longest = b[i * 5 + j] + 1;
				else
					longest = lcs(arrary, i - 1, j, b) + 1;
				if (longest > max) {
					max = longest;
				}
			}
			if (arrary[i + 1][j] < arrary[i][j]) {
				if (b[(i + 1) * 5 + j])
					longest = b[(i + 1) * 5 + j] + 1;
				else
					longest = lcs(arrary, i + 1, j, b) + 1;
				if (longest > max) {
					max = longest;
				}
			}
			if (j - 1 >= 0 && arrary[i - 1][j] < arrary[i][j]) {
				if (b[i * 5 + j])
					longest = b[i * 5 + j] + 1;
				else
					longest = lcs(arrary, i, j - 1, b) + 1;
				if (longest > max) {
					max = longest;
				}
			}
			if (arrary[i][j + 1] < arrary[i][j]) {
				if (b[i * 5 + j])
					longest = b[i * 5 + j + 1] + 1;
				else
					longest = lcs(arrary, i, j + 1, b) + 1;
				if (longest > max) {
					max = longest;
				}
			}
		}
	}
	/*printf("no little than return 1\n");*/
	if (b[i] == 0) {
		printf("set [%d] %d\n", i, max);
		b[i] = max;
	}
	return max;
}

int main(void)
{
	int i;
	int tmp;
	int max = 0;
	int a[5][5] = {
		{1, 2, 3, 4, 5},
		{16, 17, 18, 19, 6},
		{15, 24, 25, 20, 7},
		{14, 23, 22, 21, 8},
		{13, 12, 11, 10, 9},
	};
	int *b = (int *)malloc(25 * sizeof(int));
	memset(b, 0, 25 * sizeof(int));
	for (i = 0; i < 25; i++) {
		tmp = lcs(a, 10, i, b);
		if(tmp > max)
			max = tmp;
	}
	printf("max %d\n", max);
}

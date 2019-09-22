/*输入为两行字符串（可能包含空格），长度均小于等于50*/
/*输出描述:*/
/*输出为一个整数，表示最长公共连续子串的长度*/

/*输入例子:*/
/*abcde*/

/*abgde*/

/*输出例子:*/
/*2*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int max(int a, int b);

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(char *X, char *Y, int m, int n)
{
	int L[m + 1][n + 1];
	int i, j;

	/* Following steps build L[m+1][n+1] in bottom up fashion. Note
	   that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				L[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;

			else
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}

	/* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
	return L[m][n];
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

/*测试上面的函数 */
int main()
{
	char X[] = "abcdefg";
	char Y[] = "def";

	int m = strlen(X);
	int n = strlen(Y);

	printf("Length of LCS is %d\n", lcs(X, Y, m, n));

	getchar();
	return 0;
}

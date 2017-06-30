#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
 * 题目就是要找一个比N大的M^x，得到M^x*x/N的最简分数 
 * */

long long xn(long long x,int n)
{
	long long f;
	if(n==0) { //如果0次直接返回1
		f=1;
	} else {
		f = xn(x,n-1)*x;//此处为递归处理
	}
	return f;
}

int main()
{
	int i;
	long long m;
	long long n;
	scanf("%ld", &m);
	scanf("%ld", &n);
	printf("%ld %ld\n", m, n);
	for (i = 0; i < 20; i++) {
		/*printf("%ld\n", xn(n, i));*/
		if (xn(n, i) >= m) {
			printf("%d\n", i);
			return;
		}
	}
}

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int y, c, m, d, w, year, month, day;
	printf("请输入一个日期：\n");
	scanf("%d%d%d", &year, &month, &day);
	y = year % 100; //年　如2015 即年是15年
	c = year / 100; // 年份前两位　如2015即20
	m = month;
	d = day;
	if (m == 1 || m == 2) { //判断月份是否为1或2
		y--;
		m += 12; //某年的1、2月要看作上一年的13、14月来计算
	}
	w = y + y / 4 + c / 4 - 2 * c + 13 * (m + 1) / 5 + d -
	    1; //蔡勒公式的公式
	while (w < 0)
		w += 7; //确保余数为正
	w %= 7;
	printf("输入的日期是星期%d", w);
	system("pause");
}

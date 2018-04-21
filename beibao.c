/**
 * package 8
 * lizi 4KG 4500
 * pingguo 5KG 5700
 * juzi 2KG 2250
 * caomei 1KG 1100
 * tiangua 6KG 6700
 */

/*
 * f(0) = 0
 * f(i) = max(v(i - 1) + )
 */
#include <stdio.h>
#include <stdlib.h>

#define LIMIT 8   // 重量限制
#define N 5       // 物品种类
#define MIN 1     // 最小重量

struct body {
	char name[20];
	int size;
	int price;
};

typedef struct body object;

int main(void)
{
	int item[LIMIT + 1] = {0};
	int value[LIMIT + 1] = {0};
	int newvalue, i, s, p;

	object a[] = {{"李子", 4, 4500},
		{"苹果", 5, 5700},
		{"橘子", 2, 2250},
		{"草莓", 1, 1100},
		{"甜瓜", 6, 6700}
	};

	for (i = 0; i < N; i++) {
		for (s = a[i].size; s <= LIMIT; s++) {
			p = s - a[i].size;
			newvalue = value[p] + a[i].price;
			if (newvalue > value[s]) { // 找到阶段最佳解
				value[s] = newvalue;
				item[s] = i;
			}
		}
	}

	printf("物品\t价格\n");
	for (i = LIMIT; i >= MIN; i = i - a[item[i]].size) {
		printf("%s\t%d\n",
		       a[item[i]].name, a[item[i]].price);
	}

	printf("合计\t%d\n", value[LIMIT]);

	return 0;
}


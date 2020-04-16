#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
维护一个hash表，里边存放隔多久可以取值的时间片
每次从中取出最小的
*/
#define MAX_NODE 26

struct node {
	int index;
	int okay;
	int num;
};

static struct node array[MAX_NODE];


void update_num(int index, int step)
{
	int loop;

	for (loop = 0; loop < MAX_NODE; loop++) {
		if (loop == index)
			continue;
		if (array[loop].okay) {
			array[loop].okay -= step;
			if (array[loop].okay < 0) {
				array[loop].okay = 0;
			}
		}		
	}
}

int find_one(int *sum, int step, int *get)
{
	int loop;
	int index;
	int min = INT_MAX;
	
	for (loop = 0; loop < MAX_NODE; loop++) {
		if (array[loop].num && array[loop].okay < min) {
			min = array[loop].okay;
			index = loop;
		}
	}
	if (min == INT_MAX)
		return 0;
	
	*sum += array[index].okay + 1;
	update_num(loop, array[index].okay + 1);
	array[index].okay = step;
	array[index].num--;
	*get = index;
	return 1;
}


int leastInterval(char *tasks, int tasksSize, int n)
{
	int loop;
	int index;
	int sum = 0;

	if (!tasks || !tasksSize)
		return 0;
	if (n == 0)
		return tasksSize;
	
	memset(array, 0, sizeof(array));
	for (loop = 0; loop < tasksSize; loop++) {
		array[tasks[loop] - 'A'].index = tasks[loop];
		array[tasks[loop] - 'A'].num++;
		array[tasks[loop] - 'A'].okay = 0;
	}
	while(find_one(&sum, n, &index)) {
	}
	return sum;
}
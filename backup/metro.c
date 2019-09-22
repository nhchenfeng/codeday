/** * 2条地铁线路，A,B * A为环线，B东西线，均为双向线路 * 线路如下，交叉的地方用T1,T2表示
 * 给任意两点，求最少经过的站点数量，换乘站点计算一次
 *
 *
 *  A1 A2 A3 A4 A5 A6 A7 A8 A9 T1 A10 A11 A12 A13 T2 A14 A17 A16 A17 A18
 *  B1 B2 B3 B4 B5 T1 B6 B7 B8 B9 B10 T2 B11 B12 B13 B14 B17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel_list.h"

struct mnode {
	char *data;
	struct list_head entry;
};

LIST_HEAD(mlist);

static char *metro_a[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "T1", "A10",
	                  "A11", "A12", "A13", "T2", "A14", "A17", "A16", "A17", "A18"};

static char *metro_b[] = {"B1", "B2", "B3", "B4", "B5", "T1", "B6", "B7", "B8", "B9", "B10",
                          "T2", "B11", "B12", "B13", "B14", "B15"};

static int marked_a[20] = {0};
static int marked_b[17] = {0};


void init_metro()
{
	memset(marked_a, 0, sizeof(marked_a));
	memset(marked_b, 0, sizeof(marked_b));
}

int cal_min_path()
{
	struct mnode *node;
	struct list_head *curr, *next;
	int i;
	int num = 0;
	for (i = 0; i < 20; i++) {
		if (marked_a[i] == 1) {
			num++;
			/*printf("%s\n", metro_a[i]);*/
		}
	}
	for (i = 0; i < 17; i++) {
		if (marked_b[i] == 1 && i != 5 && i != 11) {
			num++;
			/*printf("%s\n", metro_b[i]);*/
		}
	}
	list_for_each_safe(curr, next, &mlist) {
		node = list_entry(curr, struct mnode, entry);
		printf("%s-> ", node->data);
	}
	printf("\n");

	return num;
}

void marked_and_vist(char *data) {
	int i;
	struct mnode *node = (struct mnode *)malloc(sizeof(*node));
	node->data = data;
	list_insert(&node->entry, &mlist);
	for (i = 0; i < 20; i++) {
		if (!strcmp(data, metro_a[i])) {
			marked_a[i] = 1;
			/*printf("visit %s data %s\n", metro_a[i], data);*/
		}
	}
	for (i = 0; i < 17; i++) {
		if (!strcmp(data, metro_b[i])) {
			marked_b[i] = 1;
			/*printf("visit %s data %s\n", metro_b[i], data);*/
		}
	}
}
static int min = 1024;
static int tmp_min;

int get_data_index(char *data, int *is_a)
{
	int i;
	for (i = 0; i < 20; i++) {
		if (!strcmp(data, metro_a[i])) {
			*is_a = 1;
			return i;
		}
	}

	for (i = 0; i < 17; i++) {
		if (!strcmp(data, metro_b[i])) {
			*is_a = 0;
			return i;
		}
	}
	printf("fail to find %s index\n", data);
	return 0;
}

char to_find[10] = {0};

int not_visit(char *data)
{
	int i;
	for (i = 0; i < 20; i++) {
		if (!strcmp(data, metro_a[i])) {
			if (marked_a[i]) {
				/*printf("A%d is already visited\n", i);*/
				return 0;
			}
		}
	}

	for (i = 0; i < 17; i++) {
		if (!strcmp(data, metro_b[i])) {
			if (marked_b[i]) {
				/*printf("B%d is already visited\n", i);*/
				return 0;
			}
		}
	}
	return 1;
}

void un_mark(char *data)
{
	int i;
	struct list_head *curr, *next;
	struct mnode *node;
	for (i = 0; i < 20; i++) {
		if (!strcmp(data, metro_a[i])) {
			marked_a[i] = 0;
			/*printf("unmark %s\n", metro_a[i]);*/
		}
	}

	for (i = 0; i < 17; i++) {
		if (!strcmp(data, metro_b[i])) {
			marked_b[i] = 0;
			/*printf("unmark %s\n", metro_b[i]);*/
		}
	}
	list_for_each_safe(curr, next, &mlist) {
		node = list_entry(curr, struct mnode, entry);
		if (!strcmp(node->data, data)) {
			list_del(&node->entry);
			free(node);
		}
	}
}

/*static int metro_a[20] = {"A 1, "A 2, "A 3, "A 4, "A 5, "A 6, "A 7, "A 8, "A 9, "T 1, "A 10,*/
			  /*"A 11, "A 12, "A 13, "T 2, "A 14, "A 17, "A 16, "A 17, "A 18};*/

/*static int metro_b[17] = {"B 1, "B 2, "B 3, "B 4, "B 5, "T 1, "B 6, "B 7, "B 8, "B 9, "B 10,*/
                          /*"T 2, "B 11, "B 12, "B 13, "B 14, "B 17};*/
void dfs(char *data)
{
	int is_a;
	int index;
	marked_and_vist(data);
	if (!strcmp(data, to_find)) {
		tmp_min = cal_min_path();
		printf("find path count %d\n", tmp_min);
		if (tmp_min < min) {
			min = tmp_min;
		}
	}
	/*printf("dfs %s\n", data);*/
	index = get_data_index(data, &is_a);
	if (!strcmp(data, "T1")) {
		/*printf("DATA T1\n");*/
		if (not_visit("A9"))
			dfs("A9");
		if (not_visit("A10")) {
			dfs("A10");
		}
		if (not_visit("B5"))
			dfs("B5");
		if (not_visit("B6"))
			dfs("B6");
	} else if (!strcmp(data, "T2")){
		/*printf("DATA T2\n");*/
		if (not_visit("A13"))
			dfs("A13");
		if (not_visit("A14"))
			dfs("A14");
		if (not_visit("B10"))
			dfs("B10");
		if (not_visit("B11"))
			dfs("B11");
	}else if (is_a && index == 0) {
		/*printf("is_a && index == 0\n");*/
		if (not_visit(metro_a[1]))
			dfs(metro_a[1]);
		if (not_visit(metro_a[19]))
			dfs(metro_a[19]);
	} else if (is_a && index == 19) {
		/*printf("is_a && index == 19\n");*/
		if (not_visit(metro_a[0]))
			dfs(metro_a[0]);
		if (not_visit(metro_a[18]))
			dfs(metro_a[18]);
	} else if (!is_a && index == 0) {
		/*printf("is_b && index == 0\n");*/
		if (not_visit(metro_b[1]))
			dfs(metro_b[1]);
	} else if (!is_a && index == 16) {
		/*printf("is_b && index == 16\n");*/
		if (not_visit(metro_b[0]))
			dfs(metro_b[0]);
	} else if (is_a){
		/*printf("normal a index %d\n", index);*/
		if (not_visit(metro_a[index + 1]))
			dfs(metro_a[index + 1]);
		if (not_visit(metro_a[index - 1]))
			dfs(metro_a[index - 1]);
	} else if (!is_a) {
		/*printf("normal b index %d\n", index);*/
		if (not_visit(metro_b[index + 1]))
			dfs(metro_b[index + 1]);
		if (not_visit(metro_b[index - 1]))
			dfs(metro_b[index - 1]);
	} else {
		printf("not got here\n");
	}

	un_mark(data);
}

int main()
{
	char start[10];
	while (1) {
		init_metro();
		memset(start, 0, 10);
		memset(to_find, 0, 10);
		min = 1024;
		scanf("%s", start);
		scanf("%s", to_find);
		dfs(start);
		printf("min %d\n", min);
	}
	return 0;
}

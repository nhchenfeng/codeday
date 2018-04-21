#include <stdio.h>
#include <stdlib.h>
#include "kernel_list.h"

static int src[] = {27, 27, 108, 108, 207};
static int dst[] = {48, 12, 11};

struct node {
	int i;
	int j;
	struct list_head entry;
};

int not_insert(int i, int j, struct list_head *mlist)
{
	struct list_head *curr;
	struct list_head *next;
	struct node *cur_node;
	list_for_each_safe(curr, next, mlist) {
		cur_node = list_entry(curr, struct node, entry);
		if (cur_node->i == i || cur_node->j == j) {
			return 0;
		}

	}
	return 1;
}

void empty_list(struct list_head *mlist)
{
	printf("empty_list\n");
	struct list_head *curr;
	struct node *cur_node;

	while (!list_empty(mlist)) {
		curr = list_remove(mlist);
		cur_node = list_entry(curr, struct node, entry);
		free(cur_node);
	}
}
int get_ratio_match(int *src, int src_num, int *dst, int dst_num)
{
	int src_loop;
	int dst_loop;
	float base;
	int max = 0;
	int tmp_max;
	int i;
	int j;

	struct list_head mlist;
	INIT_LIST_HEAD(&mlist);
	struct node *node;
	float **result = (float **)malloc(sizeof(float *) * src_num);
	for (src_loop = 0; src_loop < dst_num; src_loop++) {
		result[src_loop] = (float *)malloc(sizeof(float) * dst_num);
	}

	for (src_loop = 0; src_loop < src_num; src_loop++) {
		for (dst_loop = 0; dst_loop < dst_num; dst_loop++) {
			if (dst[dst_loop])
				result[src_loop][dst_loop] = (float)src[src_loop] / dst[dst_loop];
			else
				result[src_loop][dst_loop] = 0;
		}
	}
	for (src_loop = 0; src_loop < src_num; src_loop++) {
		for (dst_loop = 0; dst_loop < dst_num; dst_loop++) {
			base = result[src_loop][dst_loop];
			tmp_max = 1;
			node = (struct node *)malloc(sizeof(*node));
			if (!node) {
				printf("oom\n");
				return max;
			}
			node->i = src_loop;
			node->j = dst_loop;
			list_insert(&node->entry, &mlist);
			for (i = 0; i < src_num; i++) {
				for (j = 0; j < dst_num; j++) {
					if (result[i][j] == base && not_insert(i, j, &mlist)) {
						node = (struct node *)malloc(sizeof(*node));
						if (!node) {
							printf("oom\n");
							return max;
						}
						node->i = i;
						node->j = j;
						list_insert(&node->entry, &mlist);
						tmp_max++;
						printf("%d\t[%d][%d] -- [%d][%d]\n", tmp_max, i, j, src_loop, dst_loop);
						break;
					}
				}
			}
			if (tmp_max > max) {
				max = tmp_max;
			}
			empty_list(&mlist);
		}
	}
	for (src_loop = 0; src_loop < src_num; src_loop++) {
		for (dst_loop = 0; dst_loop < dst_num; dst_loop++) {
			printf("%f\t", result[src_loop][dst_loop]);
		}
		printf("\n");
	}
	return max;
}

int main()
{
	int ret = get_ratio_match(src, 5, dst, 4);
	printf("max %d\n", ret);
}

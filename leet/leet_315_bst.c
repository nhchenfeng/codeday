#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/*
定义一个搜索数，小于等于放在左边，大于放在右边
定义count，为当前节点下小于它的个数，即为当前节点左子数的全部节点数目
统计一个节点小于它的全部，等于所有走右边分支的count + 1
相当于所有的左子数全部加一起，然后加上每个节点本身
注意！ 这里count统计的是当前节点下左子树的个数，所以不会重复
*/
struct node {
	struct node *left;
	struct node *right;
	int val;
	int count;
};

static void insert_node(struct node *tree, struct node *tmp, int *data)
{
	if (tmp->val > tree->val) {
                *data += tree->count + 1; /* 比当前节点大，加上当前节点的全部，加上当前节点本身 */
		if (!tree->right) {
			tree->right = tmp;
		} else {
			insert_node(tree->right, tmp, data);
		}
	} else {
                tree->count++; /* 比当前节点，当前节点的左子数个数加1 */
		if(!tree->left) {
			tree->left = tmp;
		} else {
			insert_node(tree->left, tmp, data);
		}
	}
}

int* countSmaller(int* nums, int numsSize, int* returnSize)
{
	int loop;
	struct node *tmp;
	struct node tree = { 0 };
	int *ans_array;
	int tmp_count;
	
	if (!nums || numsSize == 0) {
		*returnSize = 0;
		return NULL;
	}
	ans_array = (int *)malloc(numsSize * sizeof(int));
	tree.val = nums[numsSize - 1];
	ans_array[numsSize - 1] = 0;
	for (loop = numsSize - 2; loop >= 0; loop--) {
		tmp = (struct node *)malloc(sizeof(struct node));
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->val = nums[loop];
                tmp->count = 0;
		tmp_count = 0;
		insert_node(&tree, tmp, &tmp_count);
		ans_array[loop] = tmp_count;
	}
	*returnSize = numsSize;
	return ans_array;
}
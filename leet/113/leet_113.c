#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define LIST_MAX                100000

struct ret_node {
	int data;
	int total;
	int step;
	struct ret_node *pre;
};

static struct ret_node node_list[100000];
static int list_first;
static int list_last;
static int **ret_arrary;

int list_empty()
{
	if (list_first == list_last)
		return 1;
	else
		return 0;
}

int list_full()
{
	if ((list_last + 1) % LIST_MAX == list_fist)
		return 1;
	return 0;
}

int list_insert(struct ret_node node){
	if (list_full)
		return 1;
	node_list[list_first] = node;
	list_first == (list_first + 1) % LIST_MAX;
}

int list_pop() {
	if (list_empty())
		return 1;

	memset(&node_list[list_last], 0, sizeof(node_list[list_last]));
	list_last == (list_fist + 1) % LIST_MAX;
}

void add_ret(struct ret_node *node, int *size, int** returnColumnSizes)
{
	int i;

	printf("node step %d\n", node->step);
	ret_arrary[*size] = (int *)malloc(sizeof(int) * node->step);
	returnColumnSizes[*size] = (int *)malloc(sizeof(int));
	*returnColumnSizes[*size] = node->step;
	for (i = node->step; i > 0; i--) {
		ret_arrary[*size][i] = node->data;
		node = node->parent;
	}
	*size += 1;
}

int bfs(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes)
{
	struct ret_node tmp_node = {0};
	struct ret_node *p_node = &tmp_node;
	struct ret_node *next_node = &tmp_node;

	p_node->data = root->val;
	p_node->total = root->val;
	p_node->step = 1;

	list_insert(*p_node);
	while (!list_empty()) {
		p_node = &node_list[list_last];
		list_pop();
		if (p_node->left) {
			next_node->data = p_node->left->val;
			next_node->total = p_node->total + p_node->data;
			next_node->parent = p_node;
			next_node->step = p_node->step + 1;
			if (next_node->total <= sum) {
				list_insert(*next_node);
			}
		}
		if (p_node->right) {
			next_node->data = p_node->right->val;
			next_node->total = p_node->total + p_node->data;
			next_node->parent = p_node;
			next_node->step = p_node->step + 1;
			if (next_node->total <= sum) {
				list_insert(*next_node);
			}
		}
		if (!p_node->right && !p_node->left) {
			if (p_node->total == sum)
				add_ret(p_node, returnSize, returnColumnSizes);
		}
	}
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes)
{
	memset(not_list , 0, sizeof(node_list));
	ret_arrary = (int **)malloc(1024 * sizeof(int *));
	*returnColumnSizes = (int *)malloc(1024 * sizeof(int));
	*returnSize = 0;

	if (!root || !returnSize || !returnColumnSizes)
		return 0;

	return ret_arrary;
}

int main()
{
	return 0;
}

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
	struct ret_node *parent;
	struct TreeNode *tree_node;
};

static struct ret_node node_list[LIST_MAX];
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
	if ((list_first + 1) % LIST_MAX == list_last)
		return 1;
	return 0;
}

int list_insert(struct ret_node node){
	if (list_full())
		return 1;
	node_list[list_first] = node;
	list_first = (list_first + 1) % LIST_MAX;
    return 0;
}

int list_pop() {
	if (list_empty())
		return 1;

	//memset(&node_list[list_last], 0, sizeof(node_list[list_last]));
    //node_list[list_last].parent = NULL;
	list_last = (list_last + 1) % LIST_MAX;
    return 0;
}

void add_ret(struct ret_node *node, int *size, int** returnColumnSizes)
{
	int i;

	printf("node step %d\n", node->step);
	ret_arrary[*size] = (int *)malloc(sizeof(int) * node->step);
	(*returnColumnSizes)[*size] = node->step;
	for (i = node->step; i > 0; i--) {
		ret_arrary[*size][i - 1] = node->data;
        printf("data %d\n", node->data);
		node = node->parent;
	}
	*size += 1;
}

int bfs(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes)
{
	struct ret_node tmp_node = {0};
	struct TreeNode *t_node = root;
	struct ret_node *curr_node = &tmp_node;
	struct ret_node *next_node = &tmp_node;

	next_node->data = root->val;
	next_node->total = root->val;
	next_node->step = 1;
	next_node->tree_node = t_node;
    next_node->total = t_node->val;
	list_insert(*next_node);

	while (!list_empty()) {
		curr_node = &node_list[list_last];
		t_node = curr_node->tree_node;
		list_pop();
        printf("pop %d at depth %d left %x right %x\n", t_node->val, curr_node->step, t_node->left, t_node->right);
		if (t_node->left) {
			next_node->data = t_node->left->val;
			next_node->total = curr_node->total + t_node->left->val;
			next_node->parent = curr_node;
			next_node->step = curr_node->step + 1;
            next_node->tree_node = t_node->left;
			list_insert(*next_node);
		}
		if (t_node->right) {
			next_node->data = t_node->right->val;
			next_node->total = curr_node->total + t_node->right->val;
			next_node->parent = curr_node;
			next_node->step = curr_node->step + 1;
            next_node->tree_node = t_node->right;
			list_insert(*next_node);
		}
		if (!t_node->right && !t_node->left) {
			if (curr_node->total == sum)
				add_ret(curr_node, returnSize, returnColumnSizes);
		}
	}
    return 0;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes)
{
	if (!root) {
		*returnSize = 0;
		return NULL;
	}
	memset(node_list , 0, sizeof(node_list));
	ret_arrary = (int **)malloc(1024 * sizeof(int *));
	*returnColumnSizes = (int *)malloc(1024 * sizeof(int));
	*returnSize = 0;
    list_first = 0;
    list_last = 0;

    bfs(root, sum, returnSize, returnColumnSizes);
	return ret_arrary;
}
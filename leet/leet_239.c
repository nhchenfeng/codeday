#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ARRAY_SIZE(x)    ((sizeof(x) / sizeof((x)[0])))
#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MAX_NODE  4096 * 10
struct node {
	int max;
	int start;
	int end;
	struct node *left;
	struct node *right;
};

static struct node array[MAX_NODE];
static int arr_index;

static int ret_array[MAX_NODE];
static int ret_size;

struct node *build_tree(int left, int right, int *data, int len)
{
	int ret_left;
	int ret_right;
	struct node *root = &array[arr_index];
	root->start = left;
	root->end = right;
	arr_index++;

	int mid = (left + right) / 2;
	if (left < right) {
		root->left = build_tree(left, mid, data, len);
		root->right = build_tree(mid + 1, right, data, len);
		root->max = MAX(root->left->max, root->right->max);
	} else {
		root->max = data[left];
		root->left = NULL;
		root->right = NULL;
	}
	//printf("[%d %d] init %d\n", left, right, root->max);
	return root;
}

int query(struct node *tree, int left, int right)
{
	int ret_left;
	int ret_right;
	int mid = (tree->start + tree->end) / 2;

	if (left == tree->start && right == tree->end)
		return tree->max;

	/* left is [start, mid], right [mid + 1, end] */
	if (right <= mid) {
		return query(tree->left, left, right);
	} else  if (left >= mid + 1) {
		return query(tree->right, left, right);
	} else {
		ret_left = query(tree->left, left, mid);
		ret_right = query(tree->right, mid + 1, right);
		return MAX(ret_right, ret_left);
	}
}

int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{
	int loop;
	int tmp;
	struct node *tree;

	if (!nums || numsSize == 0 || k > numsSize)
		return NULL;
	arr_index = 0;
	ret_size = 0;
	tree = build_tree(0, numsSize - 1, nums, k);

	for (loop = 0; loop <= numsSize - k; loop++) {
		tmp = query(tree, loop, loop + k - 1);
		//printf("[%d %d] is %d\n", loop, loop + k - 1, tmp);
		ret_array[ret_size] = tmp;
		ret_size++;
	}
	*returnSize = ret_size;
	return ret_array;
}

int main()
{
	int nums[] = {1,3,-1,-3,5,3,6,7};
	int ret;
	maxSlidingWindow(nums, ARRAY_SIZE(nums), 3, &ret);
	return 0;
}
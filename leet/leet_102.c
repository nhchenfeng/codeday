#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX_NODE  4096
#define MAX_LEN   20

static struct TreeNode *list[MAX_NODE];
static int left;
static int right;

static int **ans;
static int *col;
static int ans_size;

static void init_local(void)
{
	left = 0;
	right = 0;
	ans = (int **)malloc(sizeof(int *) * MAX_LEN);
	ans_size = 0;
	col = (int *)malloc(sizeof(int) * MAX_LEN);
}

int **levelOrder(struct TreeNode *root, int *returnSize,
		 int **returnColumnSizes)
{
	int loop;
	int size;
	static struct TreeNode *pre;
	static struct TreeNode *cur;

	init_local();
	if (!root) {
		*returnSize = 0;
		return ans;
	}
	list[right++] = root;
	while(left < right) {
		size = right - left;
		ans[ans_size] = (int *)malloc(sizeof(int) * size);
		col[ans_size] = size;
		for (loop = 0; loop < size; loop++) {
			pre = list[left++];
			ans[ans_size][loop] = pre->val;
			if (pre->left) {
				list[right++] = pre->left;
			}
			if (pre->right) {
				list[right++] = pre->right;
			}
		}
		ans_size++;
	}
	*returnSize = ans_size;
	*returnColumnSizes = col;
	return ans;
}
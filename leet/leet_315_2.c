#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
求右边比自己小的树，简单的想法是把自己跟右边所有的数字对比一下
为了简化对比，可以去掉一些不必要的操作，利用二叉树搜索树，对比的时候如果比当前节点大
加上当前节点的左侧的个数即可

因此，建立树的时候，比当前节点小，当前节点的left_count+1
比当前节点大，当前节点的count = cur.count + 1;
*/

struct node {
	struct node *left;
	struct node *right;
	int data;
	int left_count;
	int count;
};

static int insert_node(struct node *root, int val, int count)
{
	//printf("insert %d root val %d count %d\n", val, root->data, count);
	if (val > root->data) {
		count += root->left_count + 1;
		if (root->right) {
			return insert_node(root->right, val, count);
		} else {
			root->right = (struct node *)malloc(sizeof(struct node));
			memset(root->right, 0, sizeof(struct node));
			root->right->data = val;
			root->right->count = count;
			return count;
		}
	} else {
		root->left_count += 1;
		if (root->left) {
			return insert_node(root->left, val, count);
		} else {
			root->left = (struct node *)malloc(sizeof(struct node));
			memset(root->left, 0, sizeof(struct node));
			root->left->data = val;
			root->left->count = count;
			return count;		
		}
	}
}

int *countSmaller(int *nums, int numsSize, int *returnSize)
{
	int loop;
	int *ans;
	struct node root;

	if (!nums || !numsSize) {
		*returnSize = 0;
		return NULL;
	}
	ans = (int *)malloc(numsSize * sizeof(int));
	root.count = 0;
	root.left_count = 0;
	root.data = nums[numsSize - 1];
	root.left = NULL;
	root.right = NULL;
	ans[numsSize - 1] = 0;
	for (loop = numsSize - 2; loop >= 0; loop--) {
		ans[loop] = insert_node(&root, nums[loop], 0);
		//printf("loop %d insert %d got %d\n", loop, nums[loop], ans[loop]);
	}
	*returnSize = numsSize;
	return ans;
}
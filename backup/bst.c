/*
 * BST: Binary Sort Tree
 * 二叉排序树，二叉搜索树
 * 如果左子树不为空，则左子树所有节点值小于根节点值
 * 如果右子树不为空，则右子树所有节点值大于根节点值
 * 左右子树也分别为二叉排序树
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bnode {
	int value;
	struct bnode *right;
	struct bnode *left;
};

void insert_tree(struct bnode *t, int key)
{
	struct bnode *temp;
	struct bnode *insert;
	int left;

	for (temp = t; temp;) {
		insert = temp;
		if (key > temp->value) {
			temp = temp->right;
			left = 0;
		}
		else {
			temp = temp->left;
			left = 1;
		}
	}

	temp = (struct bnode *)malloc(sizeof(*temp));
	memset(temp, 0, sizeof(*temp));

	temp->value = key;
	if (left) {
		printf("insert %d to %d left\n", key, insert->value);
		insert->left = temp;
	}
	else {
		printf("insert %d to %d right\n", key, insert->value);
		insert->right = temp;
	}
	return;
}

void pre_order(struct bnode *t)
{
	if (t) {
		printf("%d", t->value);
		pre_order(t->left);
		pre_order(t->right);
	}
}

void mid_order(struct bnode *t)
{
	if (t) {
		mid_order(t->left);
		printf("%d", t->value);
		mid_order(t->right);
	}
}

void bak_order(struct bnode *t)
{
	if (t) {
		bak_order(t->left);
		bak_order(t->right);
		printf("%d", t->value);
	}
}

int max (int a, int b)
{
	return a < b ? b : a;
}
/*
 *     1
 *  2     3 层数2，高度1 depth = high + 1
 */
int depth_tree(struct bnode *t)
{
	if (!t)
		return 0;
	int left_depth = depth_tree(t->left);
	int right_depth = depth_tree(t->right);

	return 1 + max(left_depth, right_depth);
}

void print_level(struct bnode *t, int level)
{
	if (!t || level < 1)
		return;

	if (level == 1) {
		printf("%d\n", t->value);
		printf("return\n");
		return;
	}

	print_level(t->left, level - 1);
	print_level(t->right, level - 1);
}

void level_order(struct bnode *t)
{
	if (!t)
		return;

	int depth = depth_tree(t);

	int i;
	for (i = 1; i <= depth; i++) {
		print_level(t, i);
	}
}

int main()
{
	struct bnode *t = (struct bnode *)malloc(sizeof(*t));
	memset(t, 0, sizeof(*t));
	/*insert_tree(t, 3);*/
	/*insert_tree(t, 1);*/
	/*insert_tree(t, 2);*/
	/*insert_tree(t, 7);*/
	/*insert_tree(t, 8);*/
	/*insert_tree(t, 6);*/
	/*insert_tree(t, 5);*/
	/*insert_tree(t, 4);*/
	insert_tree(t,1);
	insert_tree(t,2);
	pre_order(t);
	printf("\n");
	mid_order(t);
	printf("\n");
	bak_order(t);
	printf("\n");
	level_order(t);
	return 0;
}

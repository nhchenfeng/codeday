#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bnode {
	struct bnode *left;
	struct bnode *right;
	int visited;
	char data;
};

enum POSITION {
	LEFT = 1,
	RIGHT,
	MAX,
};

#define INIT_NODE_DATA(name, x) \
		struct bnode *name;\
		name = (struct bnode *)malloc(sizeof(*name)); \
		memset(name, 0, sizeof(*name)); \
		name->data = x;
	/*} while(0);*/

void insert_node(struct bnode *node, struct bnode *child, enum POSITION pos)
{
	/* position 1 left, position 2 right */
	if (pos == LEFT) {
		node->left = child;
	} else if (pos == RIGHT) {
		node->right = child;
	} else {
		printf("position error\n");
	}
}

void visit(struct bnode *node)
{
	printf("%c\n", node->data);
}

void dfs(struct bnode *node)
{
	if (!node->visited) {
		visit(node);
		node->visited = 1;
	}
	/*if (node->left && !node->left->visited) {*/
		/*dfs(node->left);*/
	/*}*/
	/*if (node->right && !node->right->visited) {*/
		/*dfs(node->right);*/
	/*}*/

	struct bnode *tmp_left = node->left;
	struct bnode *tmp_right = node->right;
	if (tmp_left && !tmp_left->visited) {
		dfs(tmp_left);
	}
	if (tmp_right && !tmp_right->visited) {
		dfs(tmp_right);
	}
}

int main(void)
{
	INIT_NODE_DATA(node_a, 'A');
	INIT_NODE_DATA(node_b, 'B');
	INIT_NODE_DATA(node_c, 'C');
	INIT_NODE_DATA(node_d, 'D');
	INIT_NODE_DATA(node_e, 'E');
	INIT_NODE_DATA(node_f, 'F');
	INIT_NODE_DATA(node_g, 'G');
	insert_node(node_a, node_b, LEFT);
	insert_node(node_a, node_c, RIGHT);
	insert_node(node_b, node_d, LEFT);
	insert_node(node_b, node_e, RIGHT);
	insert_node(node_c, node_f, LEFT);
	insert_node(node_c, node_g, RIGHT);
	dfs(node_a);
	return 0;
}

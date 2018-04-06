#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel_list.h"

struct bnode {
	struct bnode *left;
	struct bnode *right;
	struct bnode *parent;
	int visited;
	char data;
	struct list_head entry;
};

enum POSITION {
	LEFT = 1,
	RIGHT,
	MAX,
};

LIST_HEAD(mlist);

struct bnode *node_a;
struct bnode *node_b;
struct bnode *node_c;
struct bnode *node_d;
struct bnode *node_e;
struct bnode *node_f;
struct bnode *node_g;

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

void print_path(struct bnode *node)
{
	 while(node && node->visited) {
	 	printf("%c\n", node->data);
	 }
	 print_path(node->left);
	 print_path(node->right);
}

void visit_and_mark(struct bnode *node)
{
	printf("visited %c\n", node->data);
	node->visited = 1;
}

int get_found_high(struct bnode *node, struct bnode *root)
{
	int high = 0;
	struct bnode *tmp = node;
	while (tmp != root) {
		tmp = tmp->parent;
		printf("%c\n", tmp->data);
		high++;
	}
	return high;
}

int bfs(struct bnode *root, char find)
{
	int found = 0;
	int high = 0;
	struct list_head *curr;
	struct bnode *curr_node;
	if (root->data == find) {
		found = 1;
		return high;
	}
	list_insert(&root->entry, &mlist);
	printf("insert %c\n", root->data);
	while (!list_empty(&mlist)) {
		curr = list_remove(&mlist);
		curr_node = list_entry(curr, struct bnode, entry);
		visit_and_mark(curr_node);
		if (curr_node->data == find) {
			printf("found %c\n", find);
			high = get_found_high(curr_node, root);
		}
		if (curr_node->left && !curr_node->left->visited) {
			curr_node->left->parent = curr_node;
			printf("here insert_node %c\n", curr_node->left->data);
			list_insert(&curr_node->left->entry, &mlist);
		}
		if (curr_node->right && !curr_node->right->visited) {
			curr_node->right->parent = curr_node;
			printf("here insert_node %c\n", curr_node->right->data);
			list_insert(&curr_node->right->entry, &mlist);
		}
	}
	return -1;
}

struct bnode *init_bnode(char data)
{
	struct bnode *node = (struct bnode *)malloc(sizeof(*node));
	memset(node, 0, sizeof(*node));
	node->data = data;
	return node;
}

int main(void)
{
	node_a = init_bnode('A');
	node_b = init_bnode('B');
	node_c = init_bnode('C');
	node_d = init_bnode('D');
	node_e = init_bnode('E');
	node_f = init_bnode('F');
	node_g = init_bnode('G');
	insert_node(node_a, node_b, LEFT);
	insert_node(node_a, node_c, RIGHT);
	insert_node(node_b, node_d, LEFT);
	insert_node(node_b, node_e, RIGHT);
	insert_node(node_c, node_f, LEFT);
	insert_node(node_c, node_g, RIGHT);
	bfs(node_a, 'G');
	return 0;
}

#include "kernel_list.h"

LIST_HEAD(mhead);

struct node {
	struct list_head entry;
	int data;
};


int main()
{
	struct list_head *curr;
	struct list_head *next;
	struct node *cur_node;
	struct node *a = (struct node *)malloc(sizeof(*a));
	a->data = 1;
	struct node *b = (struct node *)malloc(sizeof(*b));
	b->data = 2;
	struct node *c = (struct node *)malloc(sizeof(*c));
	c->data = 3;
	struct node *d = (struct node *)malloc(sizeof(*d));
	d->data = 4;
	struct node *e = (struct node *)malloc(sizeof(*e));
	e->data = 5;
	/* test list insert remove */
	list_insert(&a->entry, &mhead);
	list_remove(&mhead);
	list_insert(&b->entry, &mhead);
	list_insert(&c->entry, &mhead);
	list_remove(&mhead);
	list_insert(&d->entry, &mhead);
	list_insert(&e->entry, &mhead);
	list_remove(&mhead);
	/*list_insert(&e->entry, &mhead);*/
	list_for_each_safe(curr, next, &mhead) {
		cur_node = list_entry(curr, struct node, entry);
		printf("curr node %d\n", cur_node->data);
	}

	while (!list_empty(&mhead)) {
		curr = list_remove(&mhead);
		cur_node = list_entry(curr, struct node, entry);
		printf("remove %d\n", cur_node->data);
	}
	list_for_each_safe(curr, next, &mhead) {
		cur_node = list_entry(curr, struct node, entry);
		printf("curr node %d\n", cur_node->data);
	}

	/* test stack push pop */
	list_push(&a->entry, &mhead);
	list_remove(&mhead);
	list_push(&b->entry, &mhead);
	list_remove(&mhead);
	list_push(&c->entry, &mhead);
	list_push(&d->entry, &mhead);
	list_remove(&mhead);
	list_remove(&mhead);
	list_push(&e->entry, &mhead);
	list_for_each_safe(curr, next, &mhead) {
		cur_node = list_entry(curr, struct node, entry);
		printf("curr node %d\n", cur_node->data);
	}

	while (!list_empty(&mhead)) {
		curr = list_pop(&mhead);
		cur_node = list_entry(curr, struct node, entry);
		printf("pop %d\n", cur_node->data);
	}
	list_for_each_safe(curr, next, &mhead) {
		cur_node = list_entry(curr, struct node, entry);
		printf("curr node %d\n", cur_node->data);
	}
}

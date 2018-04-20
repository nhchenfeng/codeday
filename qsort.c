#include "kernel_list.h"

LIST_HEAD(mhead);

struct node {
	struct list_head entry;
	int data;
};

void list_sort(struct list_head *head, int litter)
{

}

int main()
{
	test();
	struct list_head *curr;
	struct list_head *next;
	struct node *cur_node;
	struct node *a = (struct node *)malloc(sizeof(*a));
	a->data = 1;
	struct node *b = (struct node *)malloc(sizeof(*b));
	b->data = 6;
	struct node *c = (struct node *)malloc(sizeof(*c));
	c->data = 3;
	struct node *d = (struct node *)malloc(sizeof(*d));
	d->data = 9;
	struct node *e = (struct node *)malloc(sizeof(*e));
	e->data = 100;
	/* test list insert remove */
	list_insert(&a->entry, &mhead);
	list_insert(&b->entry, &mhead);
	list_insert(&c->entry, &mhead);
	list_insert(&d->entry, &mhead);
	list_insert(&e->entry, &mhead);
	list_sort();
	list_for_each_safe(curr, next, &mhead) {
		cur_node = list_entry(curr, struct node, entry);
		printf("curr node %d\n", cur_node->data);
	}
	list_sort();
	list_for_each_safe(curr, next, &mhead) {
		cur_node = list_entry(curr, struct node, entry);
		printf("curr node %d\n", cur_node->data);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct blist {
	int key;
	struct blist *prev;
	struct blist *next;
};


void print_list(struct blist *head)
{
	struct blist *temp;
	for(temp = head; temp->next; temp = temp->next) {
		printf("%d ", temp->key);
	}
	printf("%d ", temp->key);
	printf("\n");
	/*
	 *for (temp; temp->prev; temp = temp->prev) {
	 *        printf("%d %lx ", temp->key, temp);
	 *}
	 *printf("%d %lx ", temp->key, temp);
	 *printf("\n");
	 */
	/*
	 *struct blist *temp;
	 *temp = head;
	 *int i = 0;
	 *for (;temp;) {
	 *        printf("[%d] %d ", i, temp->key);
	 *        temp = temp->next;
	 *        i++;
	 *}
	 *printf("\n");
	 */
}

int get_key(struct blist *head, int position)
{
	int i;
	struct blist *temp = head;
	for(i = 0; i < position; i++) {
		temp = temp->next;	
	}
	return temp->key;
}

struct blist* swap(struct blist *head, int m, int n)
{
	int i;
	struct blist *left;
	struct blist *right;
	struct blist *temp;
	struct blist *temp_data = (struct blist *)malloc(sizeof(*temp));
	/*printf ("to swap %d %d\n", m, n);*/
	temp = head;
	for(i = 0; i < m; i++) {
		temp = temp->next;	
	}
	left = temp;

	temp = head;
	for(i = 0; i < n; i++) {
		temp = temp->next;	
	}
	right = temp;
	
	temp = temp_data;
	temp->prev = right->prev;
	temp->next = right->next;
	if (right->next)
		right->next->prev = left;
	if (right->prev) {
		right->prev->next = left;
	}
	right->prev = left->prev;
	right->next = left->next;
	if(left->prev) {
		left->prev->next = right;
	} else {
		head = right;
	}
	if (left->next) {
		left->next->prev = right;
	}
	left->prev = temp->prev;
	left->next = temp->next;
	return head;
}

struct blist *sort_list(struct blist *head, int low, int high)
{
	int i, j;	
	struct blist *temp_head;
	temp_head = head;
	for (j = high; j >=0; j--) {
		for(i = low; i < j; i++) {
			if(get_key(temp_head, i) > get_key(temp_head, j)) {
				temp_head = swap(temp_head, i, j);
			}
		}
	}
	return temp_head;
}

void add_list(struct blist *head, struct blist *add)
{
	head->next = add;
	add->prev = head;
}

int main() {
	struct blist a = {0};	
	struct blist b = {0};	
	struct blist c = {0};	
	struct blist d = {0};	
	struct blist e = {0};	
	struct blist f = {0};	
	a.key = 3;
	b.key = 2;
	c.key = 1;
	d.key = 5;
	e.key = 4;
	f.key = 0;
	add_list(&a, &b);
	add_list(&b, &c);
	add_list(&c, &d);
	add_list(&d, &e);
	add_list(&e, &f);
	print_list(&a);
	struct blist * head = sort_list(&a, 0, 5);
	print_list(head);
}

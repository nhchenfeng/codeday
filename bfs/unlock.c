/*
 *      1 2 3 4 -> 2 1 3 4
 *      can add dec and swp, each of one for 1 step
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define debug

#ifdef debug
#define info printf
#else
#define info
#endif

#define MAX_NODE  1000000

static char input[10];
static char key[10];
static int step;

static int visit[10000];

struct node {
	char data[10];
	int step;
	struct node *parent;
};

static struct node list[MAX_NODE];
static int head;
static int tail;

void show_path(struct node *np)
{
	printf("%s ", np->data);
	while(np->parent) {
		np = np->parent;
		printf("<- %s ", np->data);
	}
	info("\n");
}

static void list_add(struct node *n)
{
	info("add %s step %d parent %s step %d\n", n->data, n->step, n->parent->data, n->step);
	memcpy(&list[head], n, sizeof(struct node));
	head++;
	if (head == MAX_NODE) {
		printf("may error\n");
		head = 0;
	}
}

static struct node *list_dec()
{
	struct node *n = &list[tail];
	/*info("dec list %s step %d tail %d\n", n->data, n->step, tail);*/
	tail++;
	if (tail == MAX_NODE) {
		printf("tail -> 0");
		tail = 0;
	}
	return n;
}

static int list_empty()
{
	if (head == tail)
		return 1;
	else
		return 0;
}

void str_inc(struct node *src, struct node *dst, int index)
{
	memcpy(dst, src, sizeof(struct node));
	if (dst->data[index] == '9') {
		dst->data[index] = '1';
	} else
		dst->data[index] += 1;
	info("str inc %d %s -> %s\n", index, src->data, dst->data);
}

void str_dec(struct node *src, struct node *dst, int index)
{
	memcpy(dst, src, sizeof(struct node));
	if (dst->data[index] == '1') {
		dst->data[index] = '9';
	} else
		dst->data[index] -= 1;
	info("str dec %d %s -> %s\n", index, src->data, dst->data);
}

void str_swp(struct node *src, struct node *dst, int index)
{
	char tmp;

	memcpy(dst, src, sizeof(struct node));
	tmp = dst->data[index];
	dst->data[index] = dst->data[index + 1];
	dst->data[index + 1] = tmp;
	info("str swp %d %s -> %s\n", index, src->data, dst->data);
}


int bfs(char *input) {
	int i;
	struct node nd = {0};
	struct node *np = &nd;
	struct node *tmp = &nd;

	if (!memcmp(input, key, strlen(key)))
		return 0;

	memcpy(np->data, input, strlen(input));
	np->parent = NULL;
	np->step = 0;
	list_add(np);
	while(!list_empty()) {
		np = list_dec();
		visit[atoi(np->data)] = 1;
		info("\n%s as visit\n", np->data);

		/* do not change np's data below */
		if (!memcmp(np->data, key, strlen(key))) {
			info("okay\n");
			show_path(np);
			return np->step;
		}
		for (i = 0; i < 4; i++) {
			str_dec(np, tmp, i);
			if (!visit[atoi(tmp->data)]) {
				visit[atoi(tmp->data)] = 1; /* here add visit is okay swp can same as inc dec*/
				tmp->parent = np;
				tmp->step = np->step + 1;
				list_add(tmp);
			}
			str_inc(np, tmp, i);
			if (!visit[atoi(tmp->data)]) {
				visit[atoi(tmp->data)] = 1;
				tmp->parent = np;
				tmp->step = np->step + 1;
				list_add(tmp);
			}
		}
		for (i = 0; i < 3; i++) {
			str_swp(np, tmp, i);
			if (!visit[atoi(tmp->data)]) {
				visit[atoi(tmp->data)] = 1;
				tmp->parent = np;
				tmp->step = np->step + 1;
				list_add(tmp);
			}
		}
	}

	/* never be here */
	return 0;
}

int main()
{
	int step;
	freopen("input.txt", "r", stdin);
	gets(input);
	gets(key);
	step = bfs(input);
	printf("input %s\nkey %s\n step %d\n", input, key, step);
}

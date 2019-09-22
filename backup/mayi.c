#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel_list.h"

struct node {
	int x;
	int y;
	struct list_head entry;
};

LIST_HEAD(mlist);

/*start (17, 0) end (7, 24)*/
static int local_map[25][25] = {
	{1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1},
	{1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0},
	{1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
	{0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1},
	{0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0},
	{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
};
void print_map()
{
	int m;
	int n;
	printf("----------------------------------------\n");
	for (m = 0 ; m < 25 ; m++) {
		for (n = 0 ; n < 25 ; n++) {
			if (local_map[m][n] == 2) {
				printf("@");
			} else if (local_map[m][n] == 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("++++++++++++++++++++++++++++++++++++++++\n");
}

int little = 25 * 25;

void mark_and_visit(struct node *m_node)
{
	local_map[m_node->x][m_node->y] = 2;
	list_insert(&m_node->entry, &mlist);
}

void un_mark(struct node *m_node)
{
	local_map[m_node->x][m_node->y] = 0;
	list_del(&m_node->entry);
	/* not list remove */
	free(m_node);
}

int calc_step()
{
	int i = 0;
	struct node *m_node;
	struct list_head *curr, *next;
	int first_x = -1;
	int first_y = -1;
	int second_x = -1;
	int second_y = -1;
	list_for_each_safe(curr, next, &mlist) {
		m_node = list_entry(curr, struct node, entry);
		/*printf("[%d][%d] -> ", m_node->x, m_node->y);*/
		if (first_x == -1 && first_y == -1) {
			/*printf("[%d][%d] -> [%d][%d] -> [%d][%d] + 1\n", first_x, first_y, second_x, second_y, m_node->x, m_node->y);*/
			first_x = m_node->x;
			first_y = m_node->y;
			i ++;
		} else if (second_x == -1 && second_y == -1) {
			/*printf("[%d][%d] -> [%d][%d] -> [%d][%d] + 1\n", first_x, first_y, second_x, second_y, m_node->x, m_node->y);*/
			second_x = m_node->x;
			second_y = m_node->y;
			i ++;
		} else if (m_node->x == second_x && second_x == first_x) {
			/*printf("[%d][%d] -> [%d][%d] -> [%d][%d] + 1\n", first_x, first_y, second_x, second_y, m_node->x, m_node->y);*/
			first_x = second_x;
			first_y = second_y;
			second_x = m_node->x;
			second_y = m_node->y;
			i ++;
		} else if (m_node->y == second_y  && second_y == first_y) {
			/*printf("[%d][%d] -> [%d][%d] -> [%d][%d] + 1\n", first_x, first_y, second_x, second_y, m_node->x, m_node->y);*/
			first_x = second_x;
			first_y = second_y;
			second_x = m_node->x;
			second_y = m_node->y;
			i ++;
		} else {
			/*printf("[%d][%d] -> [%d][%d] -> [%d][%d] + 2\n", first_x, first_y, second_x, second_y, m_node->x, m_node->y);*/
			first_x = second_x;
			first_y = second_y;
			second_x = m_node->x;
			second_y = m_node->y;
			i += 2;
		}
	}
	/*printf("curr %d\n", i);*/
	return i - 2;
}

int end_x = 7;
int end_y = 24;

void dfs(int start_x, int start_y)
{
	int tmp;
	struct node *m_node = (struct node *)malloc(sizeof(*m_node));
	memset(m_node, 0, sizeof(*m_node));
	m_node->x = start_x;
	m_node->y = start_y;
	mark_and_visit(m_node);

	if ((start_x == end_x) && (start_y == end_y)) {
		tmp = calc_step();
		print_map();
		if (tmp < little)
			little = tmp;
	}

	/* up */
	if ((start_x - 1) >= 0 && local_map[start_x - 1][start_y] == 0) {
		dfs((start_x - 1), start_y);
	}
	if ((start_x + 1) <= 24 && local_map[start_x + 1][start_y] == 0) {
		dfs((start_x + 1), start_y);
	}
	if ((start_y - 1) >= 0 && local_map[start_x][start_y - 1] == 0) {
		dfs(start_x, start_y - 1);
	}
	if ((start_y + 1) <= 24 && local_map[start_x][start_y + 1] == 0) {
		dfs(start_x, start_y + 1);
	}
	un_mark(m_node);
}

int main(void)
{
	print_map();
	dfs(17, 0);
	printf("min is %d\n", little);
	return 0;
}

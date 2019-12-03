#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MAX_NODE   1024

static char map[MAX_NODE][MAX_NODE];
static char ret_array[MAX_NODE];
static int ret_size;
static int map_row;
static int map_col;
static int max_row;
static int max_col;
static int pre_dir; /* 0 down 1 right */

void update_pos(int row_max)
{
	if (pre_dir == 0) {
		if (map_row == row_max - 1) {
			map_row = map_row - 1;
			map_col = map_col + 1;
			pre_dir = 1;
		} else {
			map_row = map_row + 1;
			map_col = map_col;
			pre_dir = 0;
		}
	} else if(pre_dir == 1) {
		if (map_row == 0) {
			map_row = map_row + 1;
			map_col = map_col;
			pre_dir = 0;
		} else {
			map_row = map_row - 1;
			map_col = map_col + 1;
			pre_dir = 1;
		}
	}
}

void add_ret()
{
	int row;
	int col;
	for (row = 0; row <= max_row; row++) {
		for (col = 0; col <= max_col; col++) {
			//printf("%c ", map[row][col]);
			if (map[row][col] != -1) {
				ret_array[ret_size] = map[row][col];
				ret_size++;
			}
		}
		//printf("\n");
	}
}


char *convert(char *s, int numRows)
{
	int loop;
	map_row = 0;
	map_col = 0;
	max_row = 0;
	max_col = 0;

	memset(map, -1, sizeof(map));
	memset(ret_array, 0, sizeof(ret_array));
	ret_size = 0;
	if (!s || numRows == 0)
		return NULL;
	pre_dir = 0;
	if (numRows == 1) {
		return s;
	}
	for (loop = 0; loop < strlen(s); loop++) {
		max_row = MAX(max_row, map_row);
		max_col = MAX(max_col, map_col);
		//printf("row %d col %d\n", map_row, map_col);
		map[map_row][map_col] = s[loop];
		update_pos(numRows);
	}
	add_ret();
	return ret_array;
}

int main()
{
	char *ret;
	ret = convert("PAYPALISHIRING", 3);
	printf("%s\n", ret);
	return 0;
}
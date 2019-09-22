#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#ifdef DEBUG
#define info printf
#else
#define info
#endif

/*
char test[10][10] =
{{'O','X','O','O','X','O','X','O','O','O'},{'O','O','O','O','O','X','O','O','X','O'},{'O','O','O','O','O','O','O','O','X','O'},{'O','O','O','O','O','O','X','X','X','O'},{'O','O','O','O','O','X','O','O','O','X'},{'O','O','O','O','O','O','O','O','O','X'},{'O','O','O','O','X','O','O','O','O','O'},{'O','O','O','O','X','O','O','O','X','O'},{'X','X','O','O','O','O','O','O','O','O'},{'O','O','O','O','X','O','X','O','O','X'}};
*/
char test[6][4] =
{{'X','O','X','X'},{'O','X','O','X'},{'X','O','X','O'},{'O','X','O','X'},{'X','O','X','O'},{'O','X','O','X'}};

static char **maze;
static int row;
static int col;
static int okay;

int step[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void show_board(int index)
{
	info("=============%d ==========\n", index);
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			info("%c ", maze[i][j]);
		}
		info("\n");
	}
	info("=============%d ==========\n", index);
}

void dfs(int x, int y, int depth)
{
	int i;
	int next_x;
	int next_y;
	if (maze[x][y] != 'O')
		return;

	maze[x][y] = '@';
	for (i = 0; i < 4; i++) {
		next_x = x + step[i][0];
		next_y = y + step[i][1];
		if (next_x >= 0 && next_x <= row - 1 && next_y >= 0 && next_y <= col - 1) {
			if (maze[next_x][next_y] == 'O') {
				dfs(next_x, next_y, ++depth);
			}
		}
	}
}

void solve(char** board, int boardSize, int* boardColSize)
{
	int i, j;
	if (!board || boardSize == 0 || *boardColSize == 0) {
		printf("NULL\n");
		return;
	}

	maze = (char **)board;
	row = boardSize;
	col = *boardColSize;
	show_board(-1);

	for (i = 0; i < row; i++) {
		if (maze[i][0] == 'O') {
			dfs(i, 0, 0);
		}
		if (maze[i][col - 1] == 'O') {
			dfs(i, col - 1, 0);
		}
	}
	for (j = 0; j < col; j++) {
		if (maze[0][j] == 'O') {
			dfs(0, j, 0);
		}
		if (maze[row - 1][j] == 'O') {
			dfs(row - 1, j, 0);
		}
	}
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (maze[i][j] == '@')
				maze[i][j] = 'O';
			else if (maze[i][j] == 'O')
				maze[i][j] = 'X';
		}
	}
}

int main()
{
	int i = 0;
	int data = 4;
	char **mz = (char **)malloc(sizeof(char *) * 6);
	for(i = 0; i < 6; i++) {
		mz[i] = (char *)test[i];
	}
	solve((char **)mz, 6, &data);
	show_board(-1);
	return 0;
}

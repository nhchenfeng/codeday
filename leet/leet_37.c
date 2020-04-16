#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 9

int okay_matrix(char **board, int x, int y, int data)
{
	int row;
	int col;

	int start_x = x - x % 3;
	int end_x = start_x + 2;
	int start_y = y - y % 3;
	int end_y = start_y + 2;
	for (row = start_x; row <= end_x; row++) {
		for (col = start_y; col <= end_y; col++) {
			if (board[row][col] == data + '0') {
				return 0;
			}
		}
	}
	return 1;
}

int okay_pos(char **board, int x, int y, int data)
{
	int row;
	int col;

	for (row = 0; row < MAX_NODE; row++) {
		if (board[row][y] == data + '0')
			return 0;
	}
	for (col = 0; col < MAX_NODE; col++) {
		if (board[x][col] == data + '0')
			return 0;
	}
	return okay_matrix(board, x, y, data);
}

static int flag;

void dfs(char **board, int x, int y, int size)
{
	int row;
	int col;
	int data;

	if (x == size || y == size) {
		flag = 1;
		return;
	}

	if (board[x][y] != '.') {
		if (y == size - 1) {
			dfs(board, x + 1, 0, size);
		} else {
			dfs(board, x, y + 1, size);
		}
	} else {
		for (data = 1; data <= 9; data++) {
			if (okay_pos(board, x, y, data)) {
				board[x][y] = data + '0';
				if (y == size - 1) {
					dfs(board, x + 1, 0, size);
				} else {
					dfs(board, x, y + 1, size);
				}
				if (!flag)
					board[x][y] = '.';
			}
		}
	}
}

void solveSudoku(char **board, int boardSize, int *boardColSize)
{
	if (!board || !boardSize || boardSize != MAX_NODE)
		return;

	flag = 0;
	dfs(board, 0, 0, boardSize);
	return;
}

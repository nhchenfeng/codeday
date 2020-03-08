#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 10002

struct node {
	int id;
	int score;
	int valid;
};

typedef struct {
	int data;
} Leaderboard;

static struct node array[MAX_NODE];
static Leaderboard board;

Leaderboard *leaderboardCreate()
{
	memset(array, 0, sizeof(array));
	return &board;
}

void leaderboardAddScore(Leaderboard *obj, int playerId, int score)
{
	array[playerId].score += score;
	if (array[playerId].score > array[0].score) {
	}
}

int leaderboardTop(Leaderboard *obj, int K)
{
}

void leaderboardReset(Leaderboard *obj, int playerId)
{
}

void leaderboardFree(Leaderboard *obj)
{
}

int main()
{
	return 0;
}

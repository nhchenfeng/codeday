#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <stack>
#include <queue>

using namespace std;

typedef struct point {
	int x;
	int y;
	point *previous;
	int step;
} point;

point dir[4] = {
	{ 0, 1, NULL, 0 },
	{ 1, 0, NULL, 0 },
	{ 0, -1, NULL, 0 },
	{ -1, 0, NULL, 0 },
};

//只有0位置可以走，到数组边缘就是走出迷宫。
//输出最短的路径和最短步数
int map[8][8] = {
	{ 1, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1 },
};

void PrintAllPath(point *p)
{
	int shortest = p->step;

	cout << "可行短路径为：";
	while (p->previous != NULL) {
		cout << "(" << p->x << "," << p->y << ")";
		p = p->previous;
	}
	cout << "(" << p->x << "," << p->y << ")" << endl;
	cout << "路径长度为：" << shortest << endl;
}

void BFS(point startPoint)
{
	queue<point> q;
	q.push(startPoint);
	point cur;

	while (!q.empty()) {
		cur = q.front();
		q.pop();
		map[cur.x][cur.y] = 1;

		for (int i = 0; i < 4; i++) {
			point nxt = { cur.x + dir[i].x, cur.y + dir[i].y, NULL, 0 };
			if (nxt.x >= 0 && nxt.x < 8 && nxt.y >= 0 && nxt.y < 8 && map[nxt.x][nxt.y] == 0) {
				point *tmp = new point;
				memcpy(tmp, &cur, sizeof(point));
				nxt.previous = tmp;
				nxt.step = cur.step + 1;
				map[nxt.x][nxt.y] = 1;

				if (nxt.x == 0 || nxt.x == 7 || nxt.y == 0 || nxt.y == 7) {
					PrintAllPath(&nxt);

					//这句话注释则输出所有路径，不注释是最短路径
					/*return;*/
				}
				q.push(nxt);
			}
		}
	}
}

int main()
{
	point startPoint = { 0, 1, NULL, 0 };
	BFS(startPoint);

	return 0;
}

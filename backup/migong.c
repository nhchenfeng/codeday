#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
int maze[5][5];
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

//用结构体来记录更方便
struct Node {
	int x, y ;
	int prex, prey;  //前一节点坐标
	int dis ; //记录是第几层访问的节点
} s[5][5];


void bfs(int x, int y)
{
//队列来实现bfs
	queue <Node> q;
	q.push(s[0][0]);  //加入头节点
	s[0][0].dis = 0;
	s[0][0].x = 0;
	s[0][0].y = 0;
	while (!q.empty()) {
		Node temp = q.front();
		int tx = temp.x;
		int ty = temp.y;
		int tdis = temp.dis;

		if (tx == 4 && ty == 4)   //终止条件
			return;

		for (int i = 0; i < 4; i++) {
			int row = tx + dir[i][0];
			int col = ty + dir[i][1];
			if (row >= 0 && row < 5 && col >= 0 && col < 5 && maze[row][col] != 1) {
				maze[row][col] = 1;
				s[row][col].x = row;
				s[row][col].y = col;
				s[row][col].prex = tx;
				s[row][col].prey = ty;
				s[row][col].dis = tdis + 1;  //有了这一步，便可知道最短路径的长度！
				q.push(s[row][col]);
			}
		}
		q.pop();



	}

}

//递归打印路径！从后往前，打印从前往后
void print_path(int x, int y)
{

	if (x == 0 && y == 0) { //终止条件，打印第一个
		cout << "(" << s[0][0].x << ", " << s[0][0].y << ")" << endl;
		return;
	}

	int prex = s[x][y].prex;
	int prey = s[x][y].prey;
	print_path(prex, prey);
	cout << "(" << s[x][y].x << ", " << s[x][y].y << ")" << endl;
}

int main()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			cin >> maze[i][j];
	bfs(0, 0);
	//cout<<s[4][4].dis<<endl;
	print_path(4, 4);
	return 0;
}

dfs模板
```
dfs(x, depth) {
	mark_vist(x);
	if (x == dst) {
		add_result(x);
	}
	for(y = x.adj) {
		if (not_vist(y)) {
			y.parent = x;
			dfs(y, depth + 1);
		}
	}
	unmark(x);
}
```
dfs一般有遍历，搜索，和回溯3种: 像二叉树，往下dfs的时候，天然不会走到回路，这样其实
mark和unmark可以不做，像二维数组，后面dfs往下的时候可能回到前边的节点，这样需要mark
不mark会死循环; 回溯则需要unmark，走到死胡同的时候，需要回退一步，这时候前边的这个需要
unmark掉，想象一下有环的时候，这个节点可能重新走到，回溯到上边某一层的时候可以再走到

如 dfs 求解排列组合
求解排列，可以看成每次是从 x 开始的全连接图，每次 dfs 时候，可以从全数据index中选择，只有没有被访问即可;
求解组合的时候，可以看成从 x 开始到比 x 大的有向图，每次的dfs 的时候，只能从比当前加入的 index 大的地方选择, 注意这里的 step 和 index 的区别。
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
static int array[MAX_NODE];
static int visit[MAX_NODE];
static int out[MAX_NODE];
static int sum;

void dfs_pailie(int *data, int start, int step, int choose, int total)
{
        int index;

        if (step == choose) {
                sum ++;
                for (index = 0; index < choose; index++) {
                        printf("%d ", out[index]);
                }
                printf("pailie %d\n", sum);
        }
        for (index = 0; index < total; index++) {
                if (!visit[index]) {
                        out[step] = data[index];
                        visit[index] = 1;
                        dfs_pailie(data, 0, step + 1, choose, total);
                        visit[index] = 0;
                }
        }
}

void dfs_zuhe(int *data, int start, int step, int choose, int total)
{
        int index;

        if (step == choose) {
                sum ++;
                for (index = 0; index < choose; index++) {
                        printf("%d ", out[index]);
                }
                printf("zuhe sum %d\n", sum);
                return;
        }
        for (index = start; index < total; index++) {
                if (!visit[index]) {
                        //printf("add %d @ step %d\n", data[index], step);
                        out[step] = data[index];
                        visit[index] = 1;
                        dfs_zuhe(data, index + 1, step + 1, choose, total);
                        visit[index] = 0;
                }
        }
}

int main()
{
        memset(array, 0, sizeof(array));
        memset(visit, 0, sizeof(visit));
        memset(out, 0, sizeof(out));
        sum = 0;
        int data[] = {1, 2, 3, 4};
        dfs_pailie(data, 0, 0, 3, 4); /* A 4 3 */
        dfs_zuhe(data, 0, 0, 3, 4);  /*C 42 */
}
```

bfs与spfa
广度搜索，一圈一圈像外
```
bfs(x) {
	x 入队 list;
	x.depth = 1;
	while (not_emptry(list)) {
		pre = list.pop;
		if (okay) {
			add_ret(pre);
		}
		for(curr = pre.adj) {
			curr 入队
		}
	}
}
```
如果bfs中有环，需要做mark，但是要考虑是否这个mark的点后续还需要，如果是求最短路径，可以
直接不mark，相当于中间有一个路径一直再转圈，但是这样不影响结果，但是需要加退出条件

spfa求解最短路径

map[row][col] 表示x 到y的直线距离
dis[x] 表示起点到x的最短距离, 刚开始初始化未最大值

```
spfa(x, map, row, col) {
	struct list_node *pre;
	struct list_node cur;
	row_index = row;
	col_index;
	dis[x] = 0;
	cur.parent = NULL;
	cur.total = 0;

	list_insert(cur);
	while(!list_empty()) {
		pre = list_pop();
		if (okay) {
			add_ret(pre);
		}
		for (col_index = 0; col_index < col; col_index ++) {
			if (map[row_index][col_index] + dis[row_index] < dis[col_index]) {
				dis[col_index] = map[row_index][col_index] + dis[row_index];
				cur.parent = pre;
				cur.total = dis[col_index];
				list_insert(cur);
			}
		}
	}
}
```

并查集与最小生成树问题
朋友的朋友还是朋友，初始化一个father数组, father都是自己
然后又关系的做union

```
void init(int n, int *father)
{
        int i;

        for (i = 0; i < n; i++) {
                father[i] = i;
        }
}

int find(int x, int *father)
{
        if (x != father[x]) {
                father[x] = find(father[x], father);
        }

        return father[x];
}

void union_circle(int x, int y, int *father)
{
        int fx = find(x, father);
        int fy = find(y, father);

        if (fx != fy) {
                father[fx]= fy;
        }
}
最小生成树问题

一个有权图，求权最小的最小生成数，又叫 xxx 算法，忘了
首先将所有的边的权排序，并初始化一个并查集
然后将边的权从大到小排序，例如数组 map[x][2]  x 从0开始往下，依次从大到小排列完成
for(index = 0; index < size; index ++) {
	if (find(index[x][0], father) != find(index[x][1], father)) {
			union_circle(index[x][0], index[x][1]);
			add_ret(index);
	}
}
```

动态规划 及一些子问题
动态规划可以理解成一个带记忆的递归，一般情况下，需要找到 dp(n) 与 dp(n - 1)，或者从0 ~ （n - 1）的每一项的最大或最小值有关系，并且有一个初始化值。
```
最长子串与最长子序列
求 str1和 str2的最长相同子串
设 dp(x, y) 包含 x, y 为结尾，且包含 x, y 项的最长子串
dp(x)(y) = {
        dp(x - 1)(y - 1) + 1;（str1[x] == str2[y])
        0； (str1[x] != str2[y])
        0 (x < 0, y < 0)
}

求 str1和 str2的最长子序列
设 dp(x, y) 以 x, y 的为结尾，且包含 x, y 项的最长子序列
dp(x)(y) = {
        dp(x - 1)(y - 1) + 1;（str1[x] == str2[y])
        max(dp(x - 1, y), dp(x, y - 1)； (str1[x] != str2[y])  /* x和y所在的前一个构成的最大，及y和x所在的前一项构成的最大*/
        0 (x < 0, y < 0)
}
```

背包问题
```
由N件物品和一个容量为 V 的背包。第 i 个物品的费用为 c[i]，价值为w[i]

01背包
每个物品只能选择一次

/*
第i个物品的费用是 c[i], 价值是 w[i]
求在费用为 v 的情况下，价值最大
dp(n, v) = {
        max[dp(n - 1, v - c[i]) + w[i], dp(n - 1, v)]  (v - c[i] >= 0)
        dp(n - 1, v) (v - c[i] < 0 ) 装不下这一个
        0; n < 0 || v < 0
}
*/
int dp(int *cost, int *value, int index, int total)
{
        if (index < 0 || total < 0) {
                return 0;
        }
        if (dp_ret[index][total] != -1) {
                return dp_ret[index][total];
        }
        if (total - cost[index] >= 0) {   /* 可以等于0 装满 */
                dp_ret[index][total] = MAX(dp(cost, value, index - 1, total - cost[index]) + value[index],
                                           dp(cost, value, index - 1, total));
        } else {  /* 装不下这一个 */
                dp_ret[index][total] = dp(cost, value, index - 1, total);
        }

        printf("dp out [%d][%d]   -> [%d]\n", index, total, dp_ret[index][total]);
        return dp_ret[index][total];
}

完全背包
每个物品可以选择无穷次
/*
第i个物品的费用是 c[i], 价值是 w[i]
求在费用为 v 的情况下，价值最大
dp(n, v) = {
        max[dp(n - 1, v - k * c[i]) + k * w[i], dp(n - 1, v)]  (v - k * c[i] >= 0)
        dp(n - 1, v) (v - c[i] < 0 ) 装不下这一个
        0; n < 0 || v < 0
}
*/

多重背包
第i 个物品可以选择有限次
/*
第i个物品的费用是 c[i], 价值是 w[i]
求在费用为 v 的情况下，价值最大
dp(n, v) = {
        max[dp(n - 1, v - k * c[i]) + k * w[i], dp(n - 1, v)]  (v - k * c[i] >= 0 且 k < 有限次)
        dp(n - 1, v) (v - c[i] < 0 ) 装不下这一个
        0; n < 0 || v < 0
}
*/
```
存图与遍历

存图一般有邻接矩阵，邻接表。 其中邻接表的构造需要每次alloc，出错概率较大，邻接矩阵的空间复杂度较大
可以用数组模拟邻接表 链式前向星存图，空间复杂度和遍历的时间复杂度都是最优，代码也比较简洁
/*
链式向前星存图 -- 邻接数组存图
初始化一个head数组，head的数组坐标index是from点
每次添加一个边进来的时候，head[from]等于这个新边
新边的next置位为head[from]，相当于每次在链表的头上
添加一个新边进来
*/
```
#define MAX_NODE   1024 * 4

struct edge_
{
	int to;
	int w;
	int next;
};

<<<<<<< HEAD
   ```
   一个有权图，求权最小的最小生成数，又叫 xxx 算法，忘了
   首先将所有的边的权排序，并初始化一个并查集
   然后将边的权从大到小排序，例如数组 map[x][2]  x 从0开始往下，依次从大到小排列完成
   for(index = 0; index < size; index ++) {
   	if (find(index[x][0], father) != find(index[x][1], father)) {
   			union_circle(index[x][0], index[x][1]);
   			add_ret(index);
   	}
   }
   ```

   滑动窗口模板
   ```
   int window(int *data, int len)
   {
           int hash[MAX_NODE];
	   int left;
	   int right;

	   for (right = 0; right < len; right++) {
	           hash[data[r]]++;
		   update result;
		   while (l < r && result not okay) {
		         hash[data[left]]--; 
			 le++;
		   }

                   len = right - left + 1;
		   ans = ...
	   }
	   return ans;
   }
   ```
=======
static struct edge_ edge[MAX_NODE];
static int head[MAX_NODE];
static int cnt;
void init_local()
{
	memset(head, -1, sizeof(head));
	cnt = 0;
}
void add_edge(int from, int to, int w)
{
	edge[cnt].to = to;
	edge[cnt].w = w;
	edge[cnt].next = head[from];
	head[from] = cnt++;  /* insert to the first index */
}
/*
	for(loop = head[index]; loop != -1; loop = edge[loop].next) {
		dfs(edge[loop].to);
	}
*/
```
堆与优先队列，K问题
考虑使用一个数组模拟二叉树，根节点在1，左边的为2n，右边的为2n + 1
如求解K个最大的数，或者优先队列，往其中添加的无序，但是读取的是有序的
```
#define MAXN 1700
int heap[MAXN], g_size;
void put(int k)
{
        heap[++g_size] = k;
        int now = g_size;
        while (now > 1) {
                int nxt = now >> 1;
                if (heap[now] > heap[nxt]) {   /*heap[now] < heap[nxt] */
                        return;
                }
                int tmp = heap[now];
                heap[now] = heap[nxt];
                heap[nxt] = tmp;
                now = nxt;
        }
}
int get()
{
        int ret = heap[1];
        heap[1] = heap[g_size--]; /* last to head */
        int now = 1;
        while (now * 2 <= g_size) {
                int nxt = now << 1;
                if (nxt < g_size && heap[nxt] > heap[nxt + 1]) { /* < */
                        nxt++; /* min of left right */
                }
                if (heap[now] <= heap[nxt]) { /* >= */
                        return ret;
                }
                int tmp = heap[now];
                heap[now] = heap[nxt];
                heap[nxt] = tmp;
                now = nxt;
        }
        return ret;
}
```
最后总结，没有算法，上来开搞
>>>>>>> d9e90a47925de200f7ab016cb543437775131d16

## 简单的算法总结

1. DFS

   一条路走下去，走到最后，看看是否是自己想要的终点，注意减枝和回溯

   模板

   ```c
   dfs (x, step, dst)
   {
   		if (x = dst) {
   			add_ret;
   		}
   		mark_and_visit(x);
   		for (y = x.adj) {
   				if (!visit(y) && y满足一定条件) { /* 这里y满足一定条件就是减枝 */
   						dfs(y, step + 1);
   				}
   		}
         unmark(x);   /* 考虑是否需要回溯 */
   }
   ```

   如 dfs 求解排列组合

   求解排列，可以看成每次是从 x 开始的全连接图，每次 dfs 时候，可以从**全数据index**中选择，只有没有被访问即可;

   求解组合的时候，可以看成从 x 开始到比 x 大的有向图，每次的dfs 的时候，只能从**比当前加入的 index 大**的地方选择, 注意这里的 step 和 index 的区别。

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

2. BFS 及sfpa

   BFS算法模板

   ```c
    static struct node node_array[NODE_MAX];
    static int node_fist；
    static int node_last; /* 一般情况下，使用一个数组来做list，但是需要考虑数组是否够大 */
    bfs(x, dst, step)
    {
    		struct node cur;
    		struct node *pre;
    		if (x = dst) {
    				add_ret();
    		}
    		cur.xxx = x.xxx;
    		node_array[list_first] = cur;
    		list_first++;
    		while (list_last < list_fist) {
    				pre = &node_array[list_last];
         		list_last++;
               if (pre == dst) {
                  add_ret();
               }
    				for (y = cur.adj) {
    				    cur.xxx = y.xxx;
               cur.step = pre->step + 1;
    						list_array[list_first] = cur;
    						list_first++;
    				}
    		}
    }
   ```

   spfa 一般情况下用于求解带权图的最短路径

   ```c
   int **map; map[x][y] 表示 x 到 y 的直线距离，直线不可达，初始化为0
   int dis[MAX]; dis[x] 表示从 src 到 x 的最短距离，默认初始化未较大值
   int array[MAX_NODE];
   int list_fist, list_last;
   spfa(map, int src, int dst, int row, int col)
   {
       int index;
       dis[src] = 0;
   	 array[list_first] = src;
       list_first++;
     	 while (list_last < list_first) {
          pre = array[list_last];
          list_last++;
          for (index = pre; index < col; index++) {
             if (map[pre][index] && dis[pre] + map[pre][index] < dis[index]) {
               	dis[index] = dis[pre] + map[pre][index] < dis[index]; /* 关键一步 小于更新 */
                 array[list_first] = index;
                 list_first++;
             }
          }
       }
   }
   ```

   

3. 动态规划 及一些子问题

   动态规划可以理解成一个带记忆的递归，一般情况下，需要找到 dp(n) 与 dp(n - 1)，或者从0 ~ （n - 1）的每一项的最大或最小值有关系，并且有一个初始化值。

   

   最长子串与最长子序列

   ```
   
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
           max(dp(x - 1, y), dp(x, y - 1)； (str1[x] != str2[y])
           0 (x < 0, y < 0)
   }
   ```

   最长递增子序列

   ```c
   dp(x) 表示以 x 为结尾的最长子串
   dp(x) = {
           dp(y) + 1 if (data[y] > data[x], y 从0 到 x - 1)
           0 (没有这样的 y)
           1; (x == 0)
   }
   
   leet 300
   ```

   背包问题

   由N件物品和一个容量为 V 的背包。第 i 个物品的费用为 c[i]，价值为w[i]

   ```c
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

   

   

4. 并查集 及最小生成树

   并查集，简单的一句话就是朋友的朋友还是朋友，每个朋友圈用一个人标记，查看2个人是否是朋友圈，只要看他们的标记人是否是同一个人即可。

   ```
   并查集 3部曲， 用一个数组初始化所有的人，每个人的 father 都是他自己。
   然后把由关系的人 x 连接到 y，这样 x 的 father 则都指向了 y
   查看2个人的关系，通过 find 即可找到。
   
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
   ```

   最小生成树问题

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

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

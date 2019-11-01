#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
static int array[MAX_NODE];
static int visit[MAX_NODE];
static int out[MAX_NODE];
https://www.cnblogs.com/en-heng/p/7512059.html

void dfs_pailie(int *data, int step, int size)
{
        int index;

        if (step == size) {
                for (index = 0; index < size; index++) {
                        printf("%d ", out[index]);
                }
                printf("\n");
        }
        for (index = 0; index < size; index++) {
                if (!visit[index]) {
                        out[step] = data[index];
                        visit[index] = 1;
                        dfs_pailie(data, step + 1, size);
                        visit[index] = 0;
                }
        }
}

void dfs_zuhe(int *data, int step, int choose, int total)
{
        int index;

        //printf("step @ %d\n", step);
        if (step == choose) {
                for (index = 0; index < choose; index++) {
                        printf("out %d ", out[index]);
                }
                printf("\n");
                return;
        }
        printf("step %d\n", step);
        for (index = step; index < total; index++) {
                if (!visit[index]) {
                        printf("add index %d @ step %d\n", index, step);
                        out[step] = data[index];
                        visit[index] = 1;
                        dfs_zuhe(data, step + 1, choose, total);
                        visit[index] = 0;
                }
        }
}

int main()
{
        memset(array, 0, sizeof(array));
        memset(visit, 0, sizeof(visit));
        memset(out, 0, sizeof(out));
        int data[] = {1, 2, 3};
        //dfs_pailie(data, 0, 3);
        dfs_zuhe(data, 0, 2, 3);
}

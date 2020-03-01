#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void shell_sort(int *data, int size)
{
        int step;
        int i, j;
        int tmp;
        for (step = size / 2; step > 0; step = step / 2) {
                for (i = step; i < size; i++) { /* 从step开始，往后每相隔step进行插入排序 */
                        tmp = data[i];
                        for (j = i - step; j >= 0 && data[j] > tmp; j -= step) {
                                data[j + step] = data[j]; /* 比较的数，相隔step */
                        }
                        data[j + step] = tmp;
                }
        }
}

int main()
{
        int i;
        int data[10] = {3,5,1,-7,4,9,-6,8,10,4};
        shell_sort(data, 10);
        for (i = 0; i < 10; i++) {
                printf("data %d %d\n", i, data[i]);
        }
        return 0;
}

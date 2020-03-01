#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insert_sort(int *data, int size)
{
        int i, j;
        int tmp;
        int flag = 0;
        for (i = 1; i < size; i++) {
                flag = 0;
                tmp = data[i];
                for (j = i - 1; j >= 0 && data[j] > tmp; j--) { /* from right to left, only bigger j-- */
                        data[j + 1] = data[j];
                }
                data[j + 1] = tmp;
        }
}

int main()
{
        int i;
        int data[10] = {3,5,1,-7,4,9,-6,8,10,4};
        insert_sort(data, 10);
        for (i = 0; i < 10; i++) {
                printf("data %d %d\n", i, data[i]);
        }
        return 0;
}

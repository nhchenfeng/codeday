#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubble_sort(int *data, int size)
{
        int i, j;
        int tmp;

        for (i = 0; i < size; i++) {
                for (j = 0; j < size - i - 1; j++) { /* compare data[j] data [j + 1] */
                        if (data[j + 1] < data[j]) {
                                tmp = data[j + 1];
                                data[j + 1] = data[j];
                                data[j] = tmp;
                        }
                }
        }
}

int main()
{
        int i;
        int data[10] = {3,5,1,-7,4,9,-6,8,10,4};
        bubble_sort(data, 10);
        for (i = 0; i < 10; i++) {
                printf("data %d %d\n", i, data[i]);
        }
        return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void select_sort(int *data, int size)
{
	int i, j;
        int min, tmp;
        for (i = 0; i < size; i++) {
                min = i;
                for (j = i + 1; j < size; j++) {
                        if (data[j] < data[min])
                                min = j;
                }
                tmp = data[min];
                data[min] = data[i];
                data[i] = tmp;
        }
}

int main()
{
        int i;
        int data[10] = {3,5,1,-7,4,9,-6,8,10,4};
        select_sort(data, 10);
        for (i = 0; i < 10; i++) {
                printf("data %d %d\n", i, data[i]);
        }
        return 0;
}
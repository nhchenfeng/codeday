#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* start from 0, left 2 * dad + 1, right 2 * dad + 2, max up */
void max_heap(int *data, int index, int end)
{
        int tmp;
        int dad = index;
        int left =  2 * dad + 1;
        int right = 2 * dad + 2;
        int max = dad;
        if (left <= end && data[left] > data[max])
                max = left;
        if (right <= end && data[right] > data[max])
                max = right;

        if (max != dad) {
                tmp = data[max];
                data[max] = data[dad];
                data[dad] = tmp;
                max_heap(data, max, end);
        }
}

void heap_sort(int *data, int size)
{
        int i;
        int tmp;
        for (i = size - 1; i >= 0; i--) {
                /* 从后往前堆化，这点很重要 */
                max_heap(data, i, size);
        }
        for(i = size - 1; i >= 0; i--) {
                tmp = data[0];
                data[0] = data[i];
                data[i] = tmp; /* swap root to last */
                max_heap(data, 0, i - 1); /* end = i - 1, for next */
        }
}

int main()
{
        int i;
        int data[10] = {3,5,1,-7,4,9,-6,8,10,4};
        heap_sort(data, 10);
        for (i = 0; i < 10; i++) {
                printf("data %d %d\n", i, data[i]);
        }
        return 0;
}
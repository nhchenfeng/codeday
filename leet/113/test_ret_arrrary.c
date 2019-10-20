#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
        int row_index;
        int col_index;
        int row;
        int **array = (int **)malloc(5 * sizeof(int *));

        array[0] = (int *)malloc(5 * sizeof(int));

        array[0][0] = 1;
        array[0][3] = 5;
        printf("end\n");
}

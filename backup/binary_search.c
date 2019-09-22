#include <stdio.h>

/*
 * 在一个有序,无重复的数组中查找某个特征元素
 * */
static int local_arrary[10] = {10, 22, 33, 44, 101, 123, 198, 201, 290, 401};

int binary_search(int arrary[], int len, int target)
{
	int middle;
	int low = 0;
	int high = len - 1;

	while(low <= high) {
		/*middle = (high - low + 1) / 2  + low;	*/
		middle = (high - low) / 2  + low; /*这里去上和取下都一样*/
		if(arrary[middle] == target)
			return middle;
		else if (arrary[middle] > target)
			high = middle - 1;
		else
			low = middle + 1;
	}
	return -1;
}

int main()
{
	int result;
	result = binary_search(local_arrary, sizeof(local_arrary) / sizeof(local_arrary[0]), 290);
	printf("search result %d\n", result);
	result = binary_search(local_arrary, sizeof(local_arrary) / sizeof(local_arrary[0]), 10);
	printf("search result %d\n", result);
	result = binary_search(local_arrary, sizeof(local_arrary) / sizeof(local_arrary[0]), 401);
	printf("search result %d\n", result);
	result = binary_search(local_arrary, sizeof(local_arrary) / sizeof(local_arrary[0]), 22);
	printf("search result %d\n", result);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*char *local_arrary = "([[]()])";*/

void delete_char_arrary(char *arrary, int index)
{
	/*printf("before arrary %s index %d\n", arrary, index);*/
	int len = strlen(arrary);
	char * local_data = (char *)malloc(sizeof(char) * (len + 1));
	memset(local_data, 0, sizeof(char) * (len + 1));
	memcpy(local_data, arrary, index);
	memcpy(local_data + index, arrary + index + 1, len - index - 1);
	memcpy(arrary, local_data, len + 1);
	/*printf("after arrary %s\n", arrary);*/
}

void delete_char_arrary_two(char *arrary, int index_a, int index_b)
{
	/*printf("before arrary %s \n", arrary);*/
	int len = strlen(arrary);
	int i = 0;
	int j = 0;
	char * local_data = (char *)malloc(sizeof(char) * (len + 1));
	memset(local_data, 0, sizeof(char) * (len + 1));
	for (i = 0; i < strlen(arrary); i ++) {
		if (i != index_a && i != index_b) {
			local_data[j] = arrary[i];
			j ++;
		}
	}
	memcpy(arrary, local_data, len + 1);
	/*printf("after arrary %s\n", arrary);*/
}

int is_match(char a, char b)
{
	if (a == '(' && b == ')') {
		/*printf("match\n");*/
		return 0;
	}
	else if (a == '[' && b == ']') {
		/*printf("match\n");*/
		return 0;
	}
	else {
		/*printf("not match\n");*/
		return 1;
	}
}

int match(const char *arrary)
{
	char *local_arrary = (char *)malloc(sizeof(char) * (strlen(arrary) + 1));
	memcpy(local_arrary, arrary, strlen(arrary) + 1);
	int i;
	int j;
	int len = strlen(arrary);
	if (len % 2) {
		printf("No \n");
		return 0;
	}
	for (i = 0; i < len / 2; i ++) {
		for (j = 0; j < strlen(local_arrary) - 1; j++) {
			if (!is_match(local_arrary[j], local_arrary[j + 1])) {
				/*delete_char_arrary(local_arrary, j);*/
				/*delete_char_arrary(local_arrary, j);*/
				delete_char_arrary_two(local_arrary, j, j +1);
				break;
			}
		}
	}
	if(!strlen(local_arrary))
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}

int main()
{
	int num = 0;
	char local_arrary[1000] = {0};
	printf("please intut\n");
	printf("input N to stop \n");
	while (1) {
		scanf("%s", local_arrary);
		if (local_arrary[0] == 'N')
			break;
		if (!strlen(local_arrary))
			break;
		else
			match(local_arrary);
	}
	/*match(local_arrary);*/
	return 0;
}

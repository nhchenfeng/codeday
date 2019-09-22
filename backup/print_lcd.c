#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_1(char *str, int len)
{
	int i;
	for (i = 1; i <= len; i++) {
		str[i] = '-';
	}
}

void print_2(char *str, int len)
{
	int i;
	int j = 0;
	for (i = len + 3; j < len; i = i + len + 3, j ++) {
		str[i] = '|';
	}
}

void print_3(char *str, int len)
{

	int i;
	int j = 0;
	for (i = (len + 3) * (len + 2); j < len; i = i + len + 3, j ++) {
		str[i] = '|';
	}
}

void print_6(char *str, int len)
{

	int i;
	int j = 0;
	for (i = len + 3 + len + 1; j < len; i = i + len + 3, j ++) {
		str[i] = '|';
	}
}

void print_5(char *str, int len)
{

	int i;
	int j = 0;
	for (i = (len + 3) * (len + 2) + len + 1; j < len; i = i + len + 3, j ++) {
		str[i] = '|';
	}
}

void print_7(char *str, int len)
{
	int i;
	int j = 0;
	for (i = (len + 3) * (len + 1) + 1; j < len; i = i + 1, j ++) {
		str[i] = '-';
	}
}

void print_4(char *str, int len)
{
	int i;
	int j = 0;
	for (i = (len + 3) * (2 * len + 2) + 1; j < len; i = i + 1, j ++) {
		str[i] = '-';
	}
}

void print_n(char *str, int len, int end)
{
	int i;
	int j = 0;
	for (i = (len + 2); j < 2 * len + 3; i = i + len + 3, j ++) {
		if (end) {
			printf("%d\n", i);
			str[i] = '\n';
		}
		else
			str[i] = 0;
	}
}

char * print_num(int data, int len, int end)
{
	char *str = (char *)malloc((len + 3) * (2 * len + 3));
	memset(str, ' ', (len + 3) * (2 * len + 3));
	switch(data) {
		case 1:
			print_6(str, len);
			print_5(str, len);
			break;
		case 2:
			print_1(str, len);
			print_6(str, len);
			print_7(str, len);
			print_3(str, len);
			print_4(str, len);
			break;
		case 3:
			print_1(str, len);
			print_6(str, len);
			print_7(str, len);
			print_5(str, len);
			print_4(str, len);
			break;
		case 4:
			print_2(str, len);
			print_7(str, len);
			print_6(str, len);
			print_5(str, len);
			break;
		case 5:
			print_1(str, len);
			print_2(str, len);
			print_7(str, len);
			print_5(str, len);
			print_4(str, len);
			break;
		case 6:
			print_1(str, len);
			print_2(str, len);
			print_3(str, len);
			print_4(str, len);
			print_5(str, len);
			print_7(str, len);
			break;
		case 7:
			print_1(str, len);
			print_6(str, len);
			print_5(str, len);
			break;
		case 8:
			print_1(str, len);
			print_2(str, len);
			print_3(str, len);
			print_4(str, len);
			print_5(str, len);
			print_6(str, len);
			print_7(str, len);
			break;
		case 9:
			print_1(str, len);
			print_2(str, len);
			print_4(str, len);
			print_5(str, len);
			print_6(str, len);
			print_7(str, len);
			break;
		case 0:
			print_1(str, len);
			print_2(str, len);
			print_3(str, len);
			print_4(str, len);
			print_5(str, len);
			print_6(str, len);
			break;
		default:
			break;
	}
	print_n(str, len, end);
	return str;
}
int main(void)
{
	char a[10] = {0};
	int len;
	int i = 0;
	int j = 0;
	char out[1024];
	while (1) {
		scanf("%s", a);
		scanf("%d", &len);
		char **str_arrary = (char **)malloc(sizeof(char *) * strlen(a));
		for (i = 0; i < strlen(a) - 1; i++) {
			str_arrary[i] = print_num(a[i] - '0', len, 0);
		}
		str_arrary[i] = print_num(a[i] - '0', len, 1);
		for (j = 0; j < 2 * len + 3; j ++) {
			for (i = 0; i < strlen(a) - 1; i++) {
				sprintf(out + j * (len + 3) * strlen(a) + i * (len + 3), "%s ", str_arrary[i] + j * (len + 3));
			}
			sprintf(out + j * (len + 3) * strlen(a) + i * (len + 3), "%s ", str_arrary[i] + j * (len + 3));
		}
		printf("%s\n", out);
	}
}

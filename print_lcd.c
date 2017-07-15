#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*char * print_num(int data, int len)*/
/*{*/
	/*char *str = (char *)malloc((len + 3) * (len + 3) + 1);*/
	/*memset(str, ' ', (len + 3) * (len + 3) + 1);*/
	/*int i = 1;*/
	/*int j = 1;*/
	/*while(1) {*/
		/*str[i * (len + 3)] = '|';*/
		/*if (i == (len + 2))*/
			/*break;*/
		/*i ++;*/

	/*}*/
	/*i = 1;*/
	/*j = 1;*/
	/*while(1) {*/
		/*for (j = i * (len + 3); j < i * (len + 3) + len + 3; j++) {*/
			/*str[i * (len + 3) + j] = '-';*/
		/*}*/
		/*if (i == (len + 2))*/
			/*break;*/
		/*i ++;*/

	/*}*/

	/*i = 1;*/
	/*j = 1;*/
	/*while(1) {*/
		/*str[i * (len + 3)] = '\n';*/
		/*if (i == (len + 2))*/
			/*break;*/
		/*i ++;*/

	/*}*/

	/*return str;*/
/*}*/

void print_1(char *str, int len)
{
	int i;
	for (i = 1; i <= len; i++) {
		str[i] = '-';
	}
}

char * print_num(int data, int len)
{
	char *str = (char *)malloc((len + 3) * (len + 3) + 1);
	memset(str, ' ', (len + 3) * (len + 3) + 1);
	int i;
	for (i = len + 2; i <= (len + 3) * (len + 3) + 1; i = i + (len + 3)) {
		str[i] = '\n';
	}
	/* 1 */
	print_1(str, len);
}

/*char * PrintNum(char* num, int s)*/
/*{*/

/*}*/

int main(void)
{
	printf("%s\n", print_num(8, 2));
}

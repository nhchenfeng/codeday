#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_int(int a, int b)
{
	return a > b ? a : b;
}

void str_add(char *a, char *b, char *out)
{
	int i;
	int add = 0;
	int len_a = strlen(a);
	int len_b = strlen(b);
	int max = max_int(len_a, len_b);
	char *local_a = (char *)malloc(max + 1);
	memset(local_a, '0', max + 1);
	char *local_b = (char *)malloc(max + 1);
	memset(local_b, '0', max + 1);
	char *local_out = (char *)malloc(max + 2);
	memset(local_out, 0, max + 2);
	if (len_a > len_b) {
		memcpy(local_a, a, strlen(a));
		memcpy(local_b + len_a - len_b, b, strlen(b));
	} else {
		memcpy(local_b, b, strlen(b));
		memcpy(local_a + len_a - len_b, a, strlen(a));
	}
	for (i = max - 1; i >= 0; i--) {
		int ret = (local_a[i] - '0') + (local_b[i] - '0') + add;
		add = ret / 10;
		local_out[i + 1] = ret % 10 + '0';
	}
	if (add) {
		local_out[0] = add + '0';
		memcpy(out, local_out, strlen(local_out));
	} else {
		memcpy(out, local_out + 1, strlen(local_out + 1));
	}
	free(local_a);
	free(local_b);
	free(local_out);
}

int main()
{
	char a[1000] = {0};
	char b[1000] = {0};
	char c[1000] = {0};
	int i = 0;
	while (1) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));
		scanf("%s %s", a, b);
		str_add(a, b, c);
		printf("%s\n", c);
	}
}

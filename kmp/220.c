#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 1 10 6 4 5 - > 1 5 4 2 3
 * 1 4 5 6 10
 * */
void change_str(char *str, num)
{
	int i, j, k;
	int min = 0xffffff;
	int data[26] = {0};

	printf("input %s\n", str);
	for (j = 0; j < num; j++) {
		data[str[j] - '1'] += 1;
	}

	k = '1';
	for (i = 0; i < 26; i++) {
		for (j = 0; j < num; j++) {
			if (str[i] = data[j]) {
				str[i] = k;
				k++;
			}
		}
	}
	printf("out %s\n", str);
}

int str_cmp(char *src, int dst, int num) {
	char *m_src = (char *)malloc(num);
	char *m_dst = (char *)malloc(num);
	int ret;
	memcpy(m_src, src, num);
	memcpy(m_dst, dst, num);

	change_str(m_src);
	change_str(m_dst);
	ret = memcpy(m_src, m_dst, num);
	free(m_src);
	free(m_dst);
	return ret;
}

int main()
{
	int data = {1, 10, 6, 4, 5};
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char exist_num[214748364 * 10 + 1];
int start;

/*
 * 20 / 3
 */
void big_dec(long num, long den, char *ret_str, int index)
{
	long cur_ret;
	int len;
	if (exist_num[num]) {
		start = exist_num[num];
		return;
	} else {
		exist_num[num] = index;
		/*printf("num %d @ start %d\n", num, index);*/
	}
	if (!(num % den)) {
		cur_ret = num / den;
		len = sprintf(ret_str + index, "%d", cur_ret);
		index += len;
		return;
	}

	cur_ret = num / den;
	num = num % den;

	len = sprintf(ret_str + index, "%d", cur_ret);
	index += len;
	/*printf("little_dec index %d %s\n", index, ret_str);*/

	num = num * 10;
	while (num < den) {
		num *= 10;
		ret_str[index] = '0';
		index++;
		/*printf("little_dec index %d %s\n", index, ret_str);*/
	}
	big_dec(num, den, ret_str, index);
}

void little_dec(long num, long den, char *ret_str, int index)
{
	/*printf("little_dec index %d %s\n", index, ret_str);*/
	ret_str[index] = '.';
	index++;
	num = num * 10;

	while (num < den) {
		num = num * 10;
		ret_str[index] = '0';
		index++;
		/*printf("little_dec index %d %s\n", index, ret_str);*/
	}
	big_dec(num, den, ret_str, index);
}

static char ret_str[10000] = { 0 };
static char out_str[10000] = { 0 };
static char out2_str[10000] = { 0 };
int mark;
char *fractionToDecimal(int numerator, int denominator)
{
	/*printf("goto %d %d\n", numerator, denominator);*/
	memset(ret_str, 0, sizeof(ret_str));
	memset(out_str, 0, sizeof(out_str));
	memset(out2_str, 0, sizeof(out_str));
	memset(exist_num, 0, sizeof(char) * 214748364 * 10 + 1);
	mark = 0;

	int len = 0;
	int index = 0;
	if ((numerator < 0 && denominator > 0)) {
		numerator = numerator * (-1);
		mark = 1;
	}
	if ((numerator > 0 && denominator < 0)) {
		denominator = denominator * (-1);
		mark = 1;
	}
	if (numerator < 0 && denominator < 0) {
		numerator = numerator * (-1);
		denominator = denominator * (-1);
	}
	if (denominator == 0) {
		return out_str;
	}
	if (numerator > denominator) {
		len = sprintf(ret_str + index, "%d", numerator / denominator);
		index += len;
		numerator = numerator % denominator;
	} else if (numerator < denominator) {
		len = sprintf(ret_str + index, "%d", 0);
		index += len;
	} else {
		len = sprintf(ret_str + index, "%d", 1);
		index += len;
		return ret_str;
	}
	if (numerator == 0) {
		return ret_str;
	}
	if (numerator < denominator)
		little_dec(numerator, denominator, ret_str, index);

	if (start != 0) {
		memcpy(out_str, ret_str, start);
		out_str[start] = '(';
		memcpy(out_str + start + 1, ret_str + start, strlen(ret_str) - start);
		memcpy(out_str + strlen(out_str), ")", 1);
	} else {
		memcpy(out_str, ret_str, strlen(ret_str));
	}
	/*printf("ret str %s\n", ret_str);*/
	if (mark) {
		sprintf(out2_str, "%c%s", '-', out_str);
		return out2_str;
	}
	return out_str;
}

int main()
{
	printf("%s\n", fractionToDecimal(-50, 8));
	printf("%s\n", fractionToDecimal(50, 8));
	printf("%s\n", fractionToDecimal(1, 3));
	printf("%s\n", fractionToDecimal(-22, -2));
	printf("%s\n", fractionToDecimal(1, 214748364));
}

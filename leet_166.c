#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long long hash[100000];
static int hash_index;

long long numt;
long long dent;
static char out_str[100000];
static char ret_str[100000];
static int str_index;
static int start;

void insert_hash(long long str_index, long long numt)
{
	hash[str_index] = numt;
}

int hash_exist(long long numt)
{
	int i;
	for (i = 1; i < str_index; i++) {
		if (hash[i] == numt)
			return i;
	}
	return 0;
}

void dec()
{
	int n;
	printf("[%lld] / [%lld]\n", numt, dent);
	if (!(numt % dent)) {
		n = sprintf(out_str + str_index, "%lld", numt / dent);
		str_index += n;
		return;
	}
	n = sprintf(out_str + str_index, "%lld.", numt / dent);
	numt = numt % dent;
	str_index += n;
	while (1) {
		numt *= 10;
		start = hash_exist(numt);
		if (start) {
			return;
		}
		insert_hash(str_index, numt);
		n = sprintf(out_str + str_index, "%lld", numt / dent);
		str_index += n;
		numt = numt % dent;
		if (!numt)
			return;
	}

	numt = numt % dent;
}

char *fractionToDecimal(int numerator, int denominator)
{
	int n = 0;

	memset(hash, 0, sizeof(hash));
	memset(out_str, 0, sizeof(out_str));
	memset(ret_str, 0, sizeof(ret_str));
	hash_index = 0;
	str_index = 0;
	start = 0;

	if (denominator == 0 || numerator == 0) {
		n = sprintf(out_str + str_index, "%s", "0");
		str_index += n;
		return out_str;
	}
	if ((numerator < 0) ^ (denominator < 0)) {
		n = sprintf(out_str + str_index, "%s", "-");
		str_index += n;
	}

	numt = llabs((long long)numerator);
	dent = llabs((long long)denominator);
	dec();
	if (start) {
		memcpy(ret_str, out_str, start);
		memcpy(ret_str + strlen(ret_str), "(", 1);
		memcpy(ret_str + strlen(ret_str), out_str + start, strlen(out_str) - start);
		memcpy(ret_str + strlen(ret_str), ")", 1);
		return ret_str;
	}
	return out_str;
}

int main()
{
	printf("%s\n", fractionToDecimal(-50, 8));
	printf("%s\n", fractionToDecimal(50, 8));
	printf("%s\n", fractionToDecimal(1, 3));
	printf("%s\n", fractionToDecimal(-22, -2));
	printf("%s\n", fractionToDecimal(1, 11));
	printf("%s\n", fractionToDecimal(3, 17));
	printf("%s\n", fractionToDecimal(214748364, -1));
	printf("%s\n", fractionToDecimal(1, -2147483648));
	printf("%s\n", fractionToDecimal(-2147483648, 1));
}

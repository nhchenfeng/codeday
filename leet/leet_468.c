#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_number(char *str, int start, int end)
{
	int loop;
	for (loop = start; loop <= end; loop++) {
		if (str[loop] == '.' || str[loop] == ':')
			return 0;
	}
	return 1;
}

int get_number(char *str, int start, int end)
{
	char data[10] = { 0 };
	memcpy(data, str + start, end - start + 1);
	return atoi(data);
}

int okay_v4(char data1, char data2)
{
    if (isdigit(data1) & isdigit(data2))
	return 1;

	return 0;
}

int is_v4_number(char *str, int start, int end)
{
	int loop;
	int index = 0;
	char data[10] = {0};
	for (loop = start; loop <= end; loop++) {
		if (!isdigit(str[loop]))
			return 0;
		data[index] = str[loop];
		index++;
	}
	//printf("number %d\n", atoi(data));
	if (atoi(data) > 255) {
		return 0;
	}
	return 1;
}

int partition_v4(char *str, int start, int end, int step)
{
	int loop;
	int data;
	int left;
	int right;
	int ret = 0;
	int dot_number = 0;
	if (step > 3)
		return 0;
	if (is_number(str, start, end)) {
		if (str[start] == '0') {
			//printf("start with 0 not okay\n");
			return 0;
		}
		if (is_v4_number(str, start, end)) {
			return 1;
		}
		return 0;
	}
	for (loop = start; loop < end; loop++) {
		if (str[loop] == '.') {
			dot_number ++;
			if (dot_number > 3)
				return 0;
			if (!okay_v4(str[loop -1], str[loop + 1])){
				//printf("left or right not digit %c %c\n", str[loop - 1], str[loop + 1]);
				return 0;
			}
			left = partition_v4(str, start, loop - 1, step + 1);
			right = partition_v4(str, loop + 1, end - 1, step + 1);
                        //printf("[%d %d] %d [%d %d] %d\n", start, loop - 1, left, loop + 1, end, right);
			//printf("[%d %d]  %d\n", start, end, left & right);
			ret = left & right;
		}
	}
	if (step == 0 && dot_number != 3)
		return 0;
	return ret;
}

int str_size(char *str, int start, int end)
{
	char data[10] = { 0 };
	memcpy(data, str + start, end - start + 1);
	return strlen(data);
}

int okay_v6(char data1, char data2)
{
	if (isalnum(data2) && isalnum(data1))
		return 1;
	return 0;
}

static int okay;

int partition_v6(char *str, int start, int end, int step)
{
	int loop;
	int data;
	int left;
	int right;
	int ret = 0;
	int dot_number = 0;
	if (step > 7)
		return 0;
	if (step == 7)

	if (is_number(str, start, end)) {
		if (str_size(str, start, end) > 4) {
			//printf("strlen not 4\n");
                        return 0;
                }
		return 1;
	}
		loop = strstr(str + start, ":") - str;
		printf("loop %d\n", loop);
			if (!okay_v6(str[loop - 1], str[loop + 1])){
                                printf("%c %c not okay v6\n", str[loop - 1], str[loop + 1]);
				return 0;
			}
			left = partition_v6(str, start, loop - 1, step + 1);
			right = partition_v6(str, loop + 1, end - 1, step + 1);
                        //printf("[%d %d] %d [%d %d] %d\n", start, loop - 1, left, loop + 1, end, right);
			printf("[%d %d]  %d\n", start, end, left & right);
			ret = left & right;
	return ret;
}

char *validIPAddress(char * IP)
{
	if (!IP || strlen(IP) == 0)
		return "Neither";
	if (partition_v4(IP, 0, strlen(IP), 0)) {
		return "IPv4";
	}
	if (partition_v6(IP, 0, strlen(IP), 0)) {
		return "IPv6";
	}
	return "Neither";
}

int main()
{
	char *ret = validIPAddress("2001:0db8:85a3:00000:0:8A2E:0370:7334");
	printf("ret %s\n", ret);
	ret = validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334");
	printf("ret %s\n", ret);
	ret = validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334:5566");
	printf("ret %s\n", ret);
}
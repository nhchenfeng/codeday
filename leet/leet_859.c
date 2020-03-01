#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static int hash[26];

bool buddyStrings(char * A, char * B)
{
	int count = 0;
	int loop;
	int match[4]  = { 0 };
	int ret = 0;

	memset(hash, 0, sizeof(hash));
	if (!A || !B)
		return false;
	if (strlen(A) != strlen(B))
		return false;
	for (loop = 0; loop < strlen(A); loop++) {
		if (A[loop] != B[loop]) {
			match[count] = A[loop];
			match[count + 1] = B[loop];
			count++;
			if (count > 2)
				return false;
		}
		hash[A[loop] - 'a']++;
	}
	if (count == 2) {
		for (loop = 0; loop < 4; loop++) {
			ret |= match[loop];
		}
		if (!ret)
			return true;
		else
			return false;
	}
	if (count == 0) {
		for (loop = 0; loop < 26; loop++) {
			if (hash[loop] >= 2) {
				return true;
			}
		}
	}
	return false;
}

int main()
{
	return 0;
}
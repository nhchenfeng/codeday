#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODE  256

static int match[MAX_NODE];
static int hash[MAX_NODE];

bool checkInclusion(char *s1, char *s2)
{
	int loop;
	int size1;
	int size2;
	int left = 0;
	int right = 0;

	if (!s1) {
		return true;
	}
	if (!s2) {
		return false;
	}
	memset(match, 0, sizeof(match));
	memset(hash, 0, sizeof(hash));

	size1 = strlen(s1);
	for (loop = 0; loop < size1; loop++) {
		match[s1[loop]]++;
	}
	size2 = strlen(s2);
	for (right = 0; right < size2; right++) {
		hash[s2[right]]++;
		while(right - left + 1 > size1) {
			hash[s2[left]]--;
			left++;
		}
		if (!memcmp(hash, match, MAX_NODE)) {
			return true;
		}
	}
	return false;
}
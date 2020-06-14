#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODE     256
static int match[MAX_NODE];
static int hash[MAX_NODE];
static int left;
static int right;
static int match_count;
static char zero[1] = { 0 }; 

static void init(char *src)
{
	int loop;
	int size = strlen(src);
	match_count = 0;
	left = 0;
	right = 0;

	memset(match, 0, sizeof(match));
	memset(hash, 0, sizeof(hash));

	for (loop = 0; loop < size; loop++) {
		match[src[loop]]++;
		if (match[src[loop]] == 1) {
			match_count++;
		}
	}
}

char *minWindow(char *s, char *t)
{
	int size;
	int count = 0;
	int min = INT_MAX;
	char *ans;
	if (!s) {
		return s;
	}
	if (!t) {
		return t;
	}
	init(t);
	size = strlen(s);
	ans = (char *)malloc(strlen(s) + 1);
	for (right = 0; right < size; right++) {
		hash[s[right]]++;
		if (hash[s[right]] == match[s[right]] && match[s[right]]) {
			count++;
		}
		if (count < match_count) {
			continue;
		}
		while (left <= right && count == match_count) {
			hash[s[left]]--;
			if (hash[s[left]] < match[s[left]] && match[s[left]]) {
				count--;
			}
                        left++;
		}

                //printf("window %d %d is not okay min %d window %d\n", left , right, min, right - left + 2);
		if (right - left + 2 < min) {
			memcpy(ans, s + left - 1, right - left + 2);
			ans[right - left + 2] = 0;
			min = right - left + 2;
		}
	}
	if (min == INT_MAX) {
		return zero;
	}
	return ans;
}
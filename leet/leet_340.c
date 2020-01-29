#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MAX_NODE   256
static int hash[MAX_NODE];

int lengthOfLongestSubstringKDistinct(char *s, int k)
{
	int left = 0;
	int right = 0;
	int count = 0;
	int max = 0;

	if (!s || k == 0)
		return 0;
	if (strlen(s) < k)
		return strlen(s);

	memset(hash, 0, sizeof(hash));

	for (right = 0; right < strlen(s); right++) {
		hash[s[right]]++;
		if (hash[s[right]] == 1) {
			count++;
		}
		while (left < right && count > k) {
			hash[s[left]]--;
			if (hash[s[left]] == 0) {
				count--;
			}
			left++;
		}
		max = MAX(max, right - left + 1);
	}
	return max;
}

int main()
{
	int ret = lengthOfLongestSubstringKDistinct("eceba", 2);
	return 0;
}

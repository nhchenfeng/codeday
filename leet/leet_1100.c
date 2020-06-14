#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE  256
static int hash[MAX_NODE];

int numKLenSubstrNoRepeats(char *S, int K)
{
	int loop;
	int left = 0;
	int right = 0;
	int size;
	int sum = 0;
	int total = 0;

	if (!S || !K) {
		return 0;
	}
	memset(hash, 0, sizeof(hash));

	size = strlen(S);
	for(right = 0; right < size; right++) {
		hash[S[right]]++;
		if (hash[S[right]] > 1) {
			sum++;
		}
		while (left <= right && sum >= 1) {
			hash[S[left]]--;
			if (hash[S[left]] == 1) {
				sum--;
			}
			left++;
		}
		if (left + K <= right) {
			hash[S[left]]--;
			if (hash[S[left]] == 1) {
				sum--;
			}
			left++;
		}
		if (right - left + 1 == K) {
			total++;
		}
	}
	return total;
}
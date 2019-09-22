#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int m_arrary[6][5] = {0};

int get_total_n(int *a, int n, int number)
{
	int i;
	int total = 0;
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
		if (a[i] == number)
			total += 1;
	}
	printf("has %d of %d\n", total, number);
	return total;
}

static int time = 0;
int get_score(int (*arrary)[5], int n)
{
	int i;
	int score = 0;
	for (i = 0; i < n; i ++) {
		int total_n = get_total_n(arrary[i], 5, i + 1);
		/*printf("score += %d\n", total_n * (i + 1));*/
		score += total_n * (i + 1);
	}
	if (score >= 63)
		score += 35;
	printf("total %d time %d\n", score, ++time);
	printf("\n");
	return score;
}

/*static int temp[6][5] = {*/
	/*{2, 3, 2, 6, 1},*/
	/*{1, 3, 1, 1, 1},*/
	/*{4, 3, 4, 6, 4},*/
	/*{2, 3, 5, 5, 6},*/
	/*{6, 3, 5, 3, 5},*/
	/*{1, 4, 4, 6, 1},*/
/*};*/

static int temp[6][5] = {
	{2, 2, 3, 2, 2},
	{4, 6, 6, 6, 5},
	{5, 4, 5, 5, 5},
	{3, 3, 1, 1, 3},
	{1, 2, 3, 2, 3},
	{4, 3, 3, 3, 3},
};

# define N 6

void swap(int arr[], int num1, int num2) {
        int t = arr[num1];
        arr[num1] = arr[num2];
        arr[num2] = t;
    }

void reverse(int arr[], int num1, int num2) {
        int i;
        for (i = 0; i < (num2 - num1) / 2; i++) {
            swap(arr, num1 + i, num2 - 1 - (i));
        }
    }

int nextArr(int arr[]) {
        int left = -1;
        int right = -1;
        int i;
        for (i = N - 1; i > 0; i--) {
            if (arr[i - 1] < arr[i]) {
                left = i - 1;
                break;
            }
        }
        if (left < 0) {
            return 0;
        }


        for (i = N - 1; i >= left; i--) {
            if (arr[i] > arr[left]) {
                right = i;
                break;
            }
        }
        swap(arr, left, right);
        reverse(arr, left + 1, N);
        return 1;
    }

int sort(int arr[]){
    int i,j,temp;
    for(i=0;i<=N;i++){
        for(j=0;j<N-i;j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    return arr[N];
}

static int total_score = 0;

void syarrange(int arr[]){
        int i;
        /*arr[N]=sort(arr);*/
	int temp_score = 0;
        do{
            for (i = 0; i < N; i++) {
		/*printf("%d - %d\t",i, arr[i]);*/
		memcpy(m_arrary[i], temp[arr[i]], sizeof(int) * 5);
            }
            /*printf("\n");*/
	    temp_score = get_score(m_arrary, 6);
	    if (temp_score > total_score)
		    total_score = temp_score;
        }while(nextArr(arr)==1);
}

int main(){
        int arr[N]={0, 1, 2, 3, 4, 5};
        syarrange(arr);
	printf("score %d\n", total_score);
        return 0;
}


/*int main()*/
/*{*/
	/*int score, temp_score;*/
	/*int i, j;*/
	/*memcpy(m_arrary, temp, sizeof(int) * 6 * 5);*/
	/*score = get_score(m_arrary, 6);*/
	/*int *data = (int *)malloc(sizeof(int) * 5);*/
	/*for (i = 0; i < 6; i++) {*/
		/*for (j = 0; j < 6; j++) {*/
			/*memcpy(m_arrary, temp, sizeof(int) * 6 * 5);*/
			/*memcpy(data, m_arrary[i], sizeof(int) * 5);*/
			/*memcpy(m_arrary[i], m_arrary[j], sizeof(int) * 5);*/
			/*memcpy(m_arrary[j], data, sizeof(int) * 5);*/
			/*temp_score = get_score(m_arrary, 6);*/
			/*if (temp_score > score)*/
				/*score = temp_score;*/
		/*}*/
	/*}*/
	/*printf("score is %d\n", score);*/
/*}*/


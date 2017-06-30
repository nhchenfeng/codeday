# include <stdio.h>
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

void syarrange(int arr[]){
        int i;
        arr[N]=sort(arr);
        do{
            for (i = 0; i < N; i++) {
                printf("%d ",arr[i]);
            }
            printf("\n");
        }while(nextArr(arr)==1);
}

int main(){
        int arr[N]={0, 1, 2, 3, 4, 5};
        syarrange(arr);
        getchar();
        return 0;
}

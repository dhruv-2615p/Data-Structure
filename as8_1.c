#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int p, int q, int r){
    int nl = q-p+1;
    int nr = r-q;

    int left[nl];
    int right[nr];
    for(int i = 0; i < nl; i++){
        left[i] = arr[p + i];
    }

    for(int j = 0; j < nr; j++){
        right[j] = arr[q + 1 + j];
    }

    int i = nl - 1, j = 0, k = p;
    while(i >= 0 && j < nr){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i--;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while(i >= 0){
        arr[k] = left[i];
        i--;
    }
    while(j < nr){
        arr[k] = right[j];
        j++;
    }
}

int main(){
    int n;
    printf("Enter the number for array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter number for array: \n");
    for(int i = 0; i < n; i++){
        scanf("%d",&arr[i]);
    }

    int min = arr[0], idx;
    for(int j = 0; j < n; j++){
        if(arr[j] < min){
            min = arr[j];
            idx = j;
        }
    }
    
    printf("minimum index is %d\n", idx);
    merge(arr, 0, idx, n - 1);

    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}
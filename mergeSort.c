#include <stdio.h>

void merge(int a[], int p, int q, int r){
    int i, j , k;
    int nl = q-p+1;
    int nr = r-q;

    int l[nl], right[nr];

    for(i = 0; i < nl; i++){
        l[i] = a[p + i];
    }

    for(j = 0; j < nr; j++){
        right[j] = a[q + 1 + j];
    }

    i = 0, j = 0, k = p;
    while(i < nl && j < nr){
        if(l[i] <= right[j]){
            a[k] = l[i];
            i++;
        }
        else{
            a[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < nl){
        a[k] = l[i];
        i++, k++;
    }

    while(j < nr){
        a[k] = right[j];
        j++, k++;
    }
}

void mergeSort(int a[], int p, int r){
    if(p < r) {
        int q = p + (r - p) / 2;
        mergeSort(a, p, q);
        mergeSort(a, q+1, r);
        
        merge(a, p, q, r);
    }
}

void printArray(int a[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
}

int main(){
    int a[] = {9, 8, 10, 24, 45, 57};
    int n = sizeof(a)/sizeof(a[0]);

    printArray(a, n);
    mergeSort(a, 0, n-1);
    printf("\nAfter sorting array: \n");
    printArray(a, n);

    return 0;
}
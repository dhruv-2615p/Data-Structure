#include <stdio.h>
#include <stdlib.h>

typedef struct poly Poly;

struct poly{
    int coeff;
    int expo;
};

Poly p1[10], p2[10], p3[10];

void merge(Poly a[], int p, int q, int r){
    int i, j , k;
    int nl = q-p+1;
    int nr = r-q;

    Poly l[nl], right[nr];

    for(i = 0; i < nl; i++){
        l[i].expo = a[p + i].expo;
        l[i].coeff = a[p + i].coeff;
    }

    for(j = 0; j < nr; j++){
        right[j].expo = a[q + 1 + j].expo;
        right[j].coeff = a[q + 1 + j].coeff;
    }

    i = 0, j = 0, k = p;
    while (i < nl && j < nr) {
        if (l[i].expo >= right[j].expo) { 
            a[k].expo = l[i].expo;
            a[k].coeff = l[i].coeff;
            i++;
        } 
        else {
            a[k].expo = right[j].expo;
            a[k].coeff = right[j].coeff;
            j++;
        }
        k++;
    }

    while(i < nl){
        a[k].expo = l[i].expo;
        a[k].coeff = l[i].coeff;
        i++, k++;
    }

    while(j < nr){
        a[k].expo = right[j].expo;
        a[k].coeff = right[j].coeff;
        j++, k++;
    }
}

void mergeSort(Poly a[], int p, int r){
    if(p < r) {
        int q = p + (r - p) / 2;
        mergeSort(a, p, q);
        mergeSort(a, q+1, r);
        
        merge(a, p, q, r);
    }
}

int readPoly(Poly p1[10]){
    int t1;
    printf("Enter number of terms for polynomial: ");
    scanf("%d", &t1);

    int i;
    for(i=0; i<t1; i++){
        printf("Enter coefficent for term %dth: ",  i+1);
        scanf("%d", &p1[i].coeff);

        printf("Enter exponent for term %dth: ",  i+1);
        scanf("%d", &p1[i].expo);
    }

    return t1;
}

void displayPoly(Poly p1[10], int term){
    int i;
    for(i=0; i < term-1 ; i++){
        printf("%d(x^%d) + ", p1[i].coeff, p1[i].expo);
    }
    printf("%d(x^%d)\n", p1[i].coeff, p1[i].expo);
}

int addPoly(Poly p1[10], Poly p2[10], int t1, int t2, Poly p3[10]){
    int i = 0, j = 0, k = 0;

    while(i < t1 && j < t2){
        if(p1[i].expo == p2[j].expo){
            p3[k].coeff = p1[i].coeff + p2[j].coeff;
            p3[k].expo = p1[i].expo;
            i++, j++, k++;
        }

        else if(p1[i].expo > p2[j].expo){
            p3[k].expo = p1[i].expo;
            p3[k].coeff = p1[i].coeff;
            i++, k++;
        }

        else{
            p3[k].expo = p2[j].expo;
            p3[k].coeff = p2[j].coeff;
            k++, j++;
        }
    }

    while(i < t1){
        p3[k].coeff = p1[i].coeff;
        p3[k].expo = p1[i].expo;
        i++, k++;
    }

    while(j < t2){
        p3[k].coeff = p2[j].coeff;
        p3[k].expo = p2[j].expo;
        k++, j++;
    }

    return k;
}

int main(){
    int t1 = readPoly(p1);
    printf("\nEntered polynomial is: \n");
    mergeSort(p1, 0, t1);
    displayPoly(p1, t1);

    int t2 = readPoly(p2);
    printf("\nEntered polynomial is: \n");
    mergeSort(p2, 0, t2);
    displayPoly(p2, t2);

    printf("\nResultant polynomial after addition: \n");
    int t3 = addPoly(p1, p2, t1, t2, p3);
    displayPoly(p3, t3);

    return 0;
}

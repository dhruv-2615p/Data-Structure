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
    while(i < nl && j < nr){
        if(l[i].expo <= right[j].expo){
            a[k].expo = l[i].expo;
            a[k].coeff = l[i].coeff;
            i++;
        }
        else{
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

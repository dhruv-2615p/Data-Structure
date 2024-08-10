#include <stdio.h>
#include <stdlib.h>

int arrangedigit(int num){
    //use of an array to store digit

    int freq[10] = {0};
    int max_num = 0;

    while(num>0){

        int digit = num % 10;

        if(digit!=0){
            freq[digit]++;
        }
        num/=10;
    }

    //to make maximum possible number
    int multiplier = 1;

    for(int i = 9; i>=1; i--){

        while(freq[i]>0){
            max_num = max_num*10 + i;
            freq[i]--;
        }
    }

    return max_num;

}

void swap(int *x, int *y){
    //To swap the two number
    int temp = *x;
    *x = *y;
    *y = temp;
}
//to check number is prime or not
int is_prime(int num){

    if(num==2) return 1;

    for(int i=2; i<=num/2; i++){
        if(num%i == 0) return 0;
    }

    return 1;
}
int final(int arr[], int start, int end){
    //to get the final number as a result
    int finalnum = arr[end];
    for(int i = end - 1; i >= 0; i--){
        finalnum = finalnum*10 + arr[i];
    }
    return finalnum;

}
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}
//calculating all possible combination of digit
int factorial (int n){

    //for finding desier factorial
    int mult = 1;
    for(int i= 1; i<=n; i++){
        mult*=i;
    }

    return mult;
}

void permute(int *arry, int l, int r, int *result, int *count) {
    //to permute all the digit stored in array
    if (l == r) {
        result[*count] = 0;
        result[*count] = final(arry, 0 , r);
        (*count)++;
    }
    else {
        for (int i = l; i <= r; i++) {
            swap(&arry[l], &arry[i]);
            permute(arry, l + 1, r, result, count);
            swap(&arry[l], &arry[i]);
        }
    }
}



int main (){
    
    //input patient number..
    int patient_num;
    printf("Total number of patient: ");
    scanf("%d", &patient_num);

    //to count digit 
    int num = patient_num;
    int digit = 0;
    while(num>0){
        digit++;
        num /= 10;
    }
    
    //to find the maximum number
    int maximum_num = arrangedigit(patient_num);
    printf("The maximum number is: %d\n", maximum_num);
    
    //to store the digit in the array & number in the result
    int *array = (int *)malloc(digit * sizeof(int));
    int count = 0;
    int *result = (int *)malloc(factorial(digit) * sizeof(int));
    
    for (int i = digit - 1; i >= 0; i--) {
        int decimal = maximum_num % 10;
        array[i] = decimal;
        maximum_num = maximum_num / 10;
    }
    
    //to find number of facotial
    int combination = factorial(digit);
    printf("Possible combinations of patient id are: %d\n", combination);
    
    permute(array, 0 , digit  - 1,result , &count);
    
    qsort(result, count, sizeof(int), compare);
    
    //printing of patient id with corrosponding rank
    for(int i = 0; i < count; i++){
               if(is_prime(i + 1) && ((i + 1) % 10 == 3 || (i + 1) % 10 == 7 )){
                    printf("Patient id at rank %d is: %d\n", i + 1, result[i]);
               }
    }
    
    return 0;
}
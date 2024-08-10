#include <stdio.h>

int prime(int num){

    if(num<2) return 0;

    for (int i=2; i<=num/2; i++){
        if(num%i==0) return 0;
    }
    return 1;
}

int up_side_down (int num){

    int x = num;
    int reverse=0;
    int digit;
    while(x>0){
        digit = x%10;
        if (digit ==2) digit=5;
        else if (digit==5) digit=2;
        else if (digit==3) digit=3;
        if (digit==7) return 0;
        else if (digit==6) digit=9;
        else if (digit==9) digit=6;
        else if (digit==4) return 0;

        reverse = reverse*10 + digit;
        x = x/10;
    }
    return prime(reverse);
}

int main (){
    
    int n,m;
    printf("Enter a start number: ");
    scanf("%d", &n);
    printf("Enter a end number: ");
    scanf("%d", &m);

    printf("Alpha numbers within the range are\n");

    for(int i=n; i<=m; i++){
        if(prime(i) && up_side_down(i)) printf("%d \n",i);
    }

    return 0;
}
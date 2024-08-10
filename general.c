#include <stdio.h>

int main(){
    int n = 123;
    float f = 23.45;

    int l = f;
    printf("%d\n", l);
    float g = n;
    printf("%d\n", g);
    n = l;
    printf("%d\n", n);

}
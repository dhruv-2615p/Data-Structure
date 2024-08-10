#include <stdio.h>

int main(){

    int starValue, target;
    printf("starValue= ");
    scanf("%d", &starValue);

    printf("target= ");
    scanf("%d", &target);

    int step=0;
    while (starValue<target){
        
        if(target%2 ==0){
            target/=2;
            
        }
        else{
            target++;
        }

        step++;
    }

    printf("Output= %d",step+starValue-target);
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define sMAX 200

char *new(char *s,int *size , char x){
    char *newS = (char *) calloc (*size +1 , sizeof(char));
    int i = 0;
    int j = 0;
    int f = 1;
    int t = 1;
    while(s[i]){
        if(s[i] == x && f){
            newS[j++] = x;
            f = 0;
        }else {
            newS[j++] = s[i];
            t = 0;
        }
    }
    if(t == 1){
        newS[j++] = x;
    }
    newS[j] = '\0';
    free(s);
    return newS;
}

char *vaishnavi(char *s,char *order){
    int i = 0;
    int j = 0;
    int size = 0;
    char *susmita = NULL;
    while(s[i]){
        j = 0;
        while(order[j]){
            if(s[i] == order[j]){
                susmita = new(susmita,&size,s[i]);
                break;
            }
            j = j + 1;
        }
        i += 1;
    }
    return susmita;
}

int main(){
    char *order;
    char *s = (char *) calloc (sMAX , sizeof(char));
    
    printf("Enter the order string :  ");
    scanf("%[^\n]s",order);
    getchar();
    printf("Enter the string to change :  ");
    scanf("%[^\n]s",s);
    
    char *m = vaishnavi(s , order);
    free(s);
    puts(m);
    return 0;
}
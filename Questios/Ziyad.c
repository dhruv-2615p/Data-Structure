#include <stdio.h>
int Palindrome(int Time[], int index){
    int start = 0;
    int end = index - 1;
    while (start < end) {
        if (Time[start] != Time[end]) {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}
void Binary(int num, int Time[], int *index){
    int start = *index;
    for(; num > 0; start++){
        Time[start] = num % 2;
        num = num / 2;
    }
    *index =  start;
    //Reversing the Time array
    int j = 0;
    int i = *index;
    i--;
    while(i > j){
        char temp = Time[i];
        Time[i] = Time[j];
        Time[j] = temp;
        j++;
        i--;
    }
}

int main()
{
    int secret_number;
    scanf("%d", &secret_number);
    int Time[10] = {0};
    int index = 0;
    Binary(secret_number, Time, &index);
    for (int i = 0; i < index; i++){
        printf("%d", Time[i]);
    }
    printf(" (Contents of array Time)\n");
    int num = secret_number;
    while(1){
        num--;
        int ind = 0;
        Binary(num, Time, &ind);
        if(Palindrome(Time, ind)){
            for(int i = 0; i < ind; i++){
                printf("%d", Time[i]);
            }
            printf(" (Nearest Palindromic number less \"than secret number\")\n");
            break;
        }
    }
    index = 0;
    Binary(secret_number, Time, &index);
    for(int i = 0; i < index; i++){
        Time[i] = 0;
        printf("%d", Time[i]);
    }
    printf(" (Time got destroyed)\n\"Something Cool\"");

    return 0;
}
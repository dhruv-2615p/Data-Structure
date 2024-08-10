#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void separate(char *str, char *alpha, char *nums){
    int i = 0, j = 0, k = 0;
    for(i = 0; str[i]; i++){
        if(isalpha(str[i])){
            alpha[j++] = str[i];
        }
        else if (isdigit(str[i]) || str[i] == '-'){
            nums[k++] = str[i];
        }
    }

    alpha[j] = '\0';
    nums[k] = '\0';
}

int compare(const void *a, const void *b){
    char char1 = *(const char *)a;
    char char2 = *(const char *)b;

    if(isdigit(char1) && isdigit(char2)){
        return (char1 - char2);
    }
    else if(char1 == '-' && isdigit(char2)){
        return -1;
    }
    else if(isdigit(char1) && char2 == '-'){
        return 1;
    }
    else    return char1 - char2;
}

void sortCombine(char *str,char *alphas, char *nums, int sort){
    if(sort == 3){
        qsort(alphas, sizeof(alphas), sizeof(char), compare);
        qsort(nums, sizeof(nums), sizeof(char), compare);
    }

    int i = 0, j = 0, k = 0;
    while(alphas[i] || nums[j]){
        if(sort == 1){
            if(alphas[i])   str[k++] = alphas[i++];
            else   str[k++] = nums[j++];
        }

        else if(sort == 2){
            if(nums[j]) str[k++] = nums[j++];
            else    str[k++] = alphas[i++];
        }

        else if(sort == 3){
            if(alphas[i] && nums[j] && isalpha(alphas[i]) && isdigit(nums[j])){
                str[k++] = (alphas[i] < nums[j]) ? alphas[i++] : nums[j++];
            }
            else if(alphas[i])  str[k++] = alphas[i++];
            else    str[k++] = nums[j++];
        }
    }
}

int main(){

    char c[1000], alphas[1000], nums[1000];
    printf("Enter a sequence: \n");
    fgets(c, sizeof(c), stdin);
    c[strcspn(c, "\n")] = '\0';

    separate(c, alphas, nums);

    char sorted1[1000], sorted2[1000], sorted3[1000];

    strcpy(sorted1, c);
    strcpy(sorted2, c);
    strcpy(sorted3, c);

    sortCombine(sorted1, alphas, nums, 1);
    sortCombine(sorted2, alphas, nums, 2);
    sortCombine(sorted3, alphas, nums, 3);

    printf("Original: %s\n", c);
    printf("%s \n", sorted1);
    printf("%s \n", sorted2);
    printf("%s \n", sorted3);

    return 0;
}
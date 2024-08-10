#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int edeges;
    printf("Enter number of edges: ");
    scanf("%d", &edeges);

    int **matrix = (int **) calloc(n, sizeof(int*));

    for(int i = 0; i < n; i++){
        matrix[i] = (int *) calloc(n, sizeof(int));
    }

    int v, u;
    printf("Enter edges in formate(v, u): \n");
    for(int i = 0; i < edeges; i++){
        scanf("%d %d", &v, &u);

        matrix[v][u] = 1;
    }

    printf("Showing Matrix: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
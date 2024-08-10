#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    int **matrix = (int **) calloc(n, sizeof(int *));
    
    for(int i = 0; i < n; i++){
        matrix[i] = (int *) calloc(n, sizeof(int));
    }

    int v, u;
    printf("Enter edges in formate(v, u): \n");
    for(int i = 0; i < edges; i++){
        scanf("%d %d", &v, &u);

        matrix[v][u] = 1; // for 1 based indexing use v - 1, u - 1
        matrix[u][v] = 1;
    }

    printf("Showing Matrix: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%3d", matrix[i][j]);
        }printf("\n");
    }

    free(matrix);
    return 0;
}
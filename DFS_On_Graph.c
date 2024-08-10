#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef enum { WHITE, GRAY, BLACK } Color;
int time = 0;

typedef struct Vertex_t* Vertex;
struct Vertex_t{
    Color color;
    int discover;
    int finish;
    int pi;
};

typedef struct Graph_t* Graph;
struct Graph_t{
    int numVertices;
    Vertex* vertex;
    int** adj;
};

Vertex newVertex(){
    Vertex vertex = (Vertex) calloc(1, sizeof(struct Vertex_t));
    assert(vertex);

    vertex->color = WHITE;
    vertex->discover = INT_MAX;
    vertex->finish = INT_MAX;
    vertex->pi = INT_MAX;

    return vertex;
}

Graph newGraph(int numVertices){
    Graph graph = (Graph) calloc(1, sizeof(struct Graph_t));
    assert(graph);

    graph->numVertices = numVertices;

    graph->vertex = (Vertex *) calloc(numVertices, sizeof(Vertex));
    assert(graph->vertex);

    for(int i = 0; i < numVertices; i++){
        graph->vertex[i] = newVertex();
    }

    graph->adj = (int **) calloc(numVertices, sizeof(int *));
    assert(graph->adj);

    for(int i =0; i < numVertices; i++){
        graph->adj[i] = (int *) calloc(numVertices, sizeof(int ));
        assert(graph->adj[i]);
    }

    return graph;
}

void DFS_Visit(Graph graph, int u){
    time = time + 1;
    graph->vertex[u]->discover = time;
    graph->vertex[u]->color = GRAY;

    for(int i = 0; i < graph->numVertices; i++){
        if(graph->adj[i][u] && graph->vertex[i]->color == WHITE){
            graph->vertex[i]->pi = u;
            DFS_Visit(graph, i);
        }
    }

    time = time + 1;
    graph->vertex[u]->color = BLACK;
    graph->vertex[u]->finish = time;
    printf("%d ", u);

}

void DFSonGraph(Graph graph){
    for(int i = 0; i < graph->numVertices; i++){
        graph->vertex[i]->color = WHITE;
        graph->vertex[i]->pi = 0;
    }

    for(int i = 0; i < graph->numVertices; i++){
        if(graph->vertex[i]->color == WHITE){
            DFS_Visit(graph, i);
        }
    }
}

int main(){
    int numVertex;
    printf("Enter number of vertices: ");
    scanf("%d", &numVertex);

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    Graph graph = newGraph(numVertex);

    int v, u;
    printf("Enter edges in formate(v, u): \n");
    for(int i = 0; i < edges; i++){
        scanf("%d %d", &v, &u);

        graph->adj[v][u] = 1; 
        graph->adj[u][v] = 1;
    }

    printf("Showing Graph's Adjoint Matrix: \n");
    for(int i = 0; i < numVertex; i++){
        for(int j = 0; j < numVertex; j++){
            printf("%3d", graph->adj[i][j]);
        }printf("\n");
    }

    DFSonGraph(graph);

    return 0;
}

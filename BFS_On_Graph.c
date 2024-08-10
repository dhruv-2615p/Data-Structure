#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>

typedef enum { White, Gray, Black } Color;
typedef struct Queue_t* Queue;
struct Queue_t{
    int capacity;
    int front;
    int rear;
    int *array;
    int size;
};

Queue newQueue(int size){
    Queue queue = (Queue) calloc(1, sizeof(struct Queue_t));
    assert(queue);

    queue->array = (int *) calloc(size, sizeof(int));
    queue->capacity = size;
    queue->front = 0;
    queue->rear = size - 1;
    queue->size = 0;

    return queue;
}

void enqueue(Queue queue, int data){
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = data;
    queue->size++;
    
    return ;
}

bool isEmpty(Queue queue){
    return queue->size == 0;
}

int dequeue(Queue queue){
    
    if(isEmpty(queue))  return 0;
    
    int data = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return data;
}

typedef struct Vertex_t* Vertex;
struct Vertex_t{
    Color color;
    int pi;
    int d;
};

typedef struct Graph_t* Graph;
struct Graph_t{
    int numVertices;
    Vertex* vertex;
    int** adjoint;
};

Vertex newVertex(){
    Vertex vertex = (Vertex) calloc(1, sizeof(struct Vertex_t));
    assert(vertex);

    vertex->color = White;
    vertex->pi = INT_MAX;
    vertex->d = INT_MAX;

    return vertex;
}

Graph newGraph(int numVertices){
    Graph graph = (Graph) calloc(1, sizeof(struct Graph_t));
    assert(graph);

    graph->vertex = (Vertex *) calloc(numVertices, sizeof(Vertex));
    assert(graph->vertex);

    for(int i = 0; i < numVertices; i++){
        graph->vertex[i] = newVertex();
    }

    graph->adjoint = (int **) calloc(numVertices, sizeof(int *));
    assert(graph->adjoint);

    for(int i = 0; i < numVertices; i++){
        graph->adjoint[i] = (int *) calloc(numVertices, sizeof(int));
        assert(graph->adjoint[i]);
    }
    graph->numVertices = numVertices;

    return graph;
}

void BFSonGraph(Graph graph, int s){
    graph->vertex[s]->color = Gray;
    graph->vertex[s]->d = 0;
    graph->vertex[s]->pi = 0;

    Queue queue = newQueue(graph->numVertices);
    enqueue(queue, s);

    while(!isEmpty(queue)){
        int u = dequeue(queue);

        for(int v = 0; v < graph->numVertices; v++){
            if(graph->adjoint[u][v] && graph->vertex[v]->color == White){
                graph->vertex[v]->color = Gray;
                graph->vertex[v]->d = graph->vertex[u]->d + 1;
                graph->vertex[v]->pi = u;

                enqueue(queue, v);
            }
        }

        graph->vertex[u]->color = Black;
        printf("%d\t", u);
    }
    printf("\n");
}

void print_path(Graph graph, int s, int v){
    if(v == s){
        printf("%d ", s);
        return;
    }

    else if(graph->vertex[v]->pi == INT_MAX){
        printf(" .\n");
        return ;
    }

    else print_path(graph, s, graph->vertex[v]->pi);
        printf("%d ", v);
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

        graph->adjoint[v][u] = 1; 
        graph->adjoint[u][v] = 1;
    }

    printf("Showing Graph's Adjoint Matrix: \n");
    for(int i = 0; i < numVertex; i++){
        for(int j = 0; j < numVertex; j++){
            printf("%3d", graph->adjoint[i][j]);
        }printf("\n");
    }

    int source = 1;
    BFSonGraph(graph, source);

    int a;
    printf("Enter vertex number for which you want path from source: ");
    scanf("%d", &a);

    printf("Minimum path between %d and %d is: \n", source, a);
    print_path(graph, source, a);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Graph_t* Graph;
typedef struct Node_t* Node;
struct Graph_t{
    int numVertices;
    Node* array;
};

struct Node_t{
    int data;
    Node next;
};

Graph newGraph(int vertices){
    Graph graph = (Graph) calloc(1, sizeof(struct Graph_t));
    assert(graph);
    graph->numVertices = vertices;
    
    graph->array = (Node *) calloc(vertices, sizeof(Node));
    assert(graph->array);

    return graph;
}

Node newNode(Node list, int data){
    Node node = (Node) calloc(1, sizeof(struct Node_t));
    assert(node);

    node->data = data;
    node->next = list;

    return node;
}

Node addFirst(Node node, int data){
    return newNode(node, data);
}

void printList(Node node){
    if(!node)   return ;

    Node p = node;
    for(; p->next ; p = p->next){
        printf("[%d | -]> ", p->data);
    }
    printf("[%d | -]> NULL", p->data);
}

void show(Graph graph, int vertices){
    if(!graph)  return ;
    int i;
    for(i = 0; i < vertices; i++){
        printf("[%d] -> ", i);
        printList(graph->array[i]);
        printf("\n");
    }
}

int main(){
    int vertices;
    printf("Enter number vertices: ");
    scanf("%d", &vertices);

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    Graph graph = newGraph(vertices);
    
    printf("Enter edges in formate (v, u): \n");
    int v, u;
    for(int i = 0; i < edges; i++){
        scanf("%d %d", &v, &u);
        graph->array[v] = addFirst(graph->array[v], u);  // for 1 indexing use v - 1
    }

    show(graph, vertices);

    return 0;
}
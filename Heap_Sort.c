#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define parent(i)   ((i) / 2)
#define left(i)    (2*(i) + 1)
#define right(i)   (2*(i) + 2)


typedef struct Heap_t* Heap;
struct Heap_t{
    int* array;
    int heap_Size;
    int array_Size;
};

Heap newHeap(int size){
    Heap heap = (Heap) calloc(1, sizeof(struct Heap_t));
    assert(heap);

    heap->array = (int *) calloc(size, sizeof(int));
    assert(heap->array);

    heap->heap_Size = 0;
    heap->array_Size = size;

    return heap;
}

void max_heapify(Heap heap, int i){
    int l = left(i);
    int r = right(i);

    int largest;
    if(l < heap->heap_Size && heap->array[l] > heap->array[i])  largest = l;
    else    largest = i;

    if(r < heap->heap_Size && heap->array[r] > heap->array[largest])    largest = r;

    if(largest != i){
        int temp = heap->array[i];
        heap->array[i] = heap->array[largest];
        heap->array[largest] = temp;

        max_heapify(heap, largest);
    }
}

void build_max_heap(Heap heap, int n){
    heap->heap_Size = n;
    
    for(int i = n / 2 - 1; i >= 0; i--)
        max_heapify(heap, i);

}

void heap_Sort(Heap heap, int n){
    build_max_heap(heap, n);
    
    for(int i = n - 1; i >= 1; i--){
        int temp = heap->array[0];
        heap->array[0] = heap->array[i];
        heap->array[i] = temp;

        heap->heap_Size--;
        max_heapify(heap, 0);
    }
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    Heap heap = newHeap(n);
    printf("Enter elemets for array: \n");
    for(int i = 0; i < n; i++){
        scanf("%d", &heap->array[i]);
    }

    printf("Before applying heap-sort: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", heap->array[i]);
    }
    printf("\n");

    heap_Sort(heap, n);
    
    printf("After applying heap-sort: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", heap->array[i]);
    }

    return 0;
}
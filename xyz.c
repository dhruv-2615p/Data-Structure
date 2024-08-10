#include <stdio.h>

// Function to heapify a subtree rooted at index i
void maxHeapify(int arr[], int heapSize, int i) {
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < heapSize && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < heapSize && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != i) {
        // Swap arr[i] and arr[largest]
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected subtree
        maxHeapify(arr, heapSize, largest);
    }
}

// Function to build a max heap
void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

// Heap sort function
void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);

    for (int i = n - 1; i >= 1; i--) {
        // Swap arr[0] (root) with arr[i]
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Reduce heap size and re-heapify
        maxHeapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    heapSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

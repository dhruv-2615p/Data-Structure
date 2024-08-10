#include <stdio.h>

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void bubbleSort(int arr[], int n) {
  int i, j, swap = 1;

  for (i = 0; swap && i < n-1; i++) {
    swap = 0;
    for (j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
         int temp = arr[j];
         arr[j] = arr[j+1];
         arr[j+1] = temp;
         swap = 1;
        }
        }
    }
}

void printArray(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main() {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr)/sizeof(arr[0]);

  printf("array: \n");
  printArray(arr, n);
  
  bubbleSort(arr, n);
  
  printf("Sorted array by bubblesort: \n");
  printArray(arr, n);
  return 0;
}

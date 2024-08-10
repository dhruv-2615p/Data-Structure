#include <stdio.h>

int partition (int arr[], int p, int r) {
  int pivot = arr[r];
  int i = (p - 1), temp, j;

  for (j = p; j <= r- 1; j++) {
    if (arr[j] <= pivot){
      i++;

      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  temp = arr[i+1];
  arr[i+1] = arr[r];
  arr[r] = temp;

  return (i + 1);
}

void quickSort(int arr[], int p, int r) {
  if (p < r) {
    int q = partition(arr, p, r);

    quickSort(arr, p, q - 1);
    quickSort(arr, q + 1, r);
  }
}

void printArray(int arr[], int size) {
  int i;
  for( i = 0; i < size; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  int arr[] = {10, 7, 8, 9, 1, 5};
  int n = sizeof(arr)/sizeof(arr[0]);

  printf("Before quick sort apply: \n");
  printArray(arr, n);
  quickSort(arr, 0, n-1);

  printf("After quick sort apply: \n");
  printArray(arr, n);

  return 0;
}

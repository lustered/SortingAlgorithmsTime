#include "algorithms/bubble_sort.h"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/utils.h"
#include <iostream>

void heapify(int *arr, int size, int largest);
void merge(int *arr, const int l, const int m, const int r, const int size);
int partition(int *arr, int lo, int hi);

void bubbleSort(int *arr, const int size) {

  for (size_t i = 0; i < size - 1; ++i)
    for (size_t j = 0; j < size - i - 1; ++j)
      if (arr[j] > arr[j + 1])
        std::swap(arr[j], arr[j + 1]);

  /* arrayinfo(arr, size); */
}

void selectionSort(int *arr, const int size) {
  int low, j;

  for (size_t i = 1; i < size; ++i) {
    low = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > low) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = low;
  }

  /* arrayinfo(arr, size); */
}

int partition(int *arr, int lo, int hi) {
  int pivot = arr[lo];
  int i = lo;
  int j;

  for (j = lo + 1; j < hi; j++)
    if (arr[j] <= pivot) {
      i = i + 1;
      std::swap(arr[i], arr[j]);
    }

  std::swap(arr[i], arr[lo]);
  return i;
}

void quickSort(int *arr, int lo, int hi) {
  int pivot;
  if (lo < hi) {
    pivot = partition(arr, lo, hi);
    quickSort(arr, lo, pivot);
    quickSort(arr, pivot + 1, hi);
  }

  /* arrayinfo(arr, hi); */
}

void heapify(int *arr, int size, int lrg) {
  int tmplrg = lrg;
  int l = 2 * lrg + 1;
  int r = 2 * lrg + 2;

  // If left child is larger than root
  if (l < size && arr[l] > arr[tmplrg])
    tmplrg = l;

  // If right child is larger than largest so far
  if (r < size && arr[r] > arr[tmplrg])
    tmplrg = r;

  // If largest is not root
  if (tmplrg != lrg) {
    std::swap(arr[lrg], arr[tmplrg]);

    // Recursively heapify the affected sub-tree
    heapify(arr, size, tmplrg);
  }
}

void heapSort(int *arr, int size) {
  // Build heap (rearrange array)
  for (int i = size / 2 - 1; i >= 0; i--)
    heapify(arr, size, i);

  // One by one extract an element from heap
  for (int i = size - 1; i > 0; i--) {
    // Move current root to end
    std::swap(arr[0], arr[i]);

    // call max heapify on the reduced heap
    heapify(arr, i, 0);
  }

  /* arrayinfo(arr, size); */
}

void merge(int* arr, const int l, const int m, const int r, const int size) {
  int n1 = m - l + 1;
  int n2 = r - m;

  // Create temp arrays
  int L[n1], R[n2];

  // Copy data to temp arrays L[] and R[]
  for (int i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  // Merge the temp arrays back into arr[l..r]

  // Initial index of first subarray
  int i = 0, j = 0;
  int k = l;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of
  // L[], if there are any
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  // Copy the remaining elements of
  // R[], if there are any
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }

  /* arrayinfo(arr, size); */
}

void mergeSort(int *arr, int l, int r, const int size) {
  if (l >= r) {

    return; 
  }

  /* Get middle point */
  int m = l + (r - l) / 2;

  /* Sort left and right recursively */
  mergeSort(arr, l, m, size);
  mergeSort(arr, m + 1, r, size);

  /* merge halves */
  merge(arr, l, m, r, size);
}

void insertionSort(int *arr, const int size) {
  int i, pivot, j;
  for (i = 1; i < size; i++) {
    pivot = arr[i];
    j = i - 1;

    /* Move elements of arr[0..i-1], that are
    greater than pivot, to one position ahead
    of their current position */
    while (j >= 0 && arr[j] > pivot) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = pivot;
  }
  /* arrayinfo(arr, size); */
}

/* Create a helper function to print an array inside a vector */
void arrayinfo(int *arr, const int size) {
  std::cout << size << " elements" << std::endl;
  std::cout << "And the last element is: " << arr[size - 1] << std::endl;

  for (int i = 1; i < size; i++) {
    std::cout << arr[i] << " ";
  }
}

/* *************** DEBUG *************** */
/* int main() { */

/* int arr[]{5, 4, 6, 4, 2, 10, 40, 10, 2}; */

/* bubbleSort(arr, 9); */
/* selectionSort(arr, 9); */
/* quickSort(arr, 0, 9); */
/* heapSort(arr, 9); */
/* mergeSort(arr, 0, 9 - 1, 9); */
/* insertionSort(arr, 9); */

/* return 0; */
/* } */

#include "algorithms/bubble_sort.h"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/utils.h"
#include <iostream>
#include <string>

void bubbleSort(unsigned int *arr, const int &size) 
// Sorts an array using bubble sort
{

  /* Classic bubble sort, not "optimized" */
  for (int i = 0; i < size - 1; ++i)
    for (int j = 0; j < size - i - 1; ++j)
      if (arr[j] > arr[j + 1])
        std::swap(arr[j], arr[j + 1]);

  /* arrayinfo(arr, size); */
} // End bubbleSort

void selectionSort(unsigned int *arr, const int &size) 
// Sorts an array using selecton sort
{
  int min;

  /* Iterate up until the second to last element */
  for (int i = 0; i < size - 1; i++) 
  {

    min = i;

    /* Find a smaller element */
    for (int j = i + 1; j < size; j++)
      if (arr[j] < arr[min])
        min = j;

    /* Swap the new min with the initial one */
    std::swap(arr[min], arr[i]);
  } // End for
} // End selectionSort

int partition(unsigned int *arr, const int &lo, const int &hi) 
// Helper function for the quickSort algorithm
{
  int pivot = arr[lo];
  int i = lo;

  for (int j = lo + 1; j < hi; j++)
    if (arr[j] <= pivot) 
    {
      i = i + 1;
      std::swap(arr[i], arr[j]);
    }

  std::swap(arr[i], arr[lo]);
  return i;
} // End partition

void quickSort(unsigned int *arr, const int &lo, const int &hi) 
// Sorts an array using quick sort
{
  int pivot;

  if (lo < hi) 
  {
    pivot = partition(arr, lo, hi);

    /* Sort left partition */
    quickSort(arr, lo, pivot);

    /* Sort right partition */
    quickSort(arr, pivot + 1, hi);
  }

  /* arrayinfo(arr, hi); */
} // End quickSort

void buildHeap(unsigned int *arr, const int &size, const int &lrg) 
// Helper function for heap sort
{
  int tmplrg = lrg;
  int leftnode = 2 * lrg + 1;
  int rightnode = 2 * lrg + 2;

  /* Check if the left node is bigger */ 
  if (leftnode < size && arr[leftnode] > arr[tmplrg])
    tmplrg = leftnode;

  /* Check if the right node is bigger */ 
  if (rightnode < size && arr[rightnode] > arr[tmplrg])
    tmplrg = rightnode;

  /* If there is a new largest, set it as root node */
  if (tmplrg != lrg) 
  {
    std::swap(arr[lrg], arr[tmplrg]);

    /* call function recursively using the new largest */
    buildHeap(arr, size, tmplrg);
  }
} // End buildHeap

void heapSort(unsigned int *arr, const int &size) 
// Sorts an array using heap sort
{
  /* Build max heap */
  for (int i = size / 2 - 1; i >= 0; i--)
    buildHeap(arr, size, i);

  /* Heap sort */
  for (int i = size - 1; i > 0; i--) 
  {

    std::swap(arr[0], arr[i]);

    /* Get the largest element as root node */
    buildHeap(arr, i, 0);
  }

  /* arrayinfo(arr, size); */
} // End heapSort

void merge(unsigned int *arr, const int &l, const int &m, const int &r, const int &size) 
// Implementation of the merge sort
{
  int size1 = m - l + 1;
  int size2 = r - m;

  /* Left and right halves: This might become an issue with an array that */
  /* doesn't fit on the stack, then we'd need to create them on the heap */
  /* int left[size1]; */
  /* int right[size2]; */

  /* Which we implement here */
  unsigned int* left = new unsigned int[size1];
  unsigned int* right = new unsigned int[size2];

  /* Populate the arrays */
  for (int i = 0; i < size1; i++)
    left[i] = arr[l + i];

  for (int j = 0; j < size2; j++)
    right[j] = arr[m + 1 + j];

  /* Keep track of both tmp arrays indexes and main arr */
  int i = 0, j = 0;
  int k = l;

  while (i < size1 && j < size2) 
  {
    if (left[i] <= right[j]) 
    {
      arr[k] = left[i];
      i++;
    } else 
    {
      arr[k] = right[j];
      j++;
    }
    k++;
  }

  /* Move the elements left from both tmp arrays back */
  while (i < size1) 
  {
    arr[k] = left[i];
    i++;
    k++;
  }

  while (j < size2) 
  {
    arr[k] = right[j];
    j++;
    k++;
  }

  delete[] left;
  delete[] right;

  /* arrayinfo(arr, size); */

} //End merge 

void mergeSort(unsigned int *arr, const int &l, const int &r, const int &size) 
// Sorts an array using merge sort
{
  if (l >= r) 
  {
    return;
  }

  /* Get middle point */
  int m = l + (r - l) / 2;

  /* Sort left and right recursively */
  mergeSort(arr, l, m, size);
  mergeSort(arr, m + 1, r, size);

  /* merge halves */
  merge(arr, l, m, r, size);
} // End mergeSort

void insertionSort(unsigned int *arr, const int &size) 
// Sorts an array using insertion sort
{
  int low, j;

  /* Iterate from the second to last element */
  for (int i = 1; i < size; ++i) 
  {
    low = arr[i];
    j = i - 1;

    /* Push elements if they're greater than curr key*/
    while (j >= 0 && arr[j] > low) 
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = low;
  }

  /* arrayinfo(arr, size); */
} // End insertionSort

void arrayinfo(unsigned int *arr, const int &size) 
// Prints all the elements in an array within the defined size as well as other
// information
{
  std::cout << "\n\n" << size << " elements\n";
  std::cout << "And the last element is: " << arr[size - 1] << "\n";

  for (int i = 0; i < size; i++) 
    std::cout << arr[i] << " ";
}

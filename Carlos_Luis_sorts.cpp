#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "algorithms/carlosluis_bubble_sort.h"
#include "algorithms/carlosluis_heap_sort.h"
#include "algorithms/carlosluis_insertion_sort.h"
#include "algorithms/carlosluis_merge_sort.h"
#include "algorithms/carlosluis_quick_sort.h"
#include "algorithms/carlosluis_selection_sort.h"
#include "algorithms/carlosluis_utils.h"

void generateDatasets();
void createArraysFromDatasets();

/* size for every dataset */
const int CHUNKSIZE[]{1000,  4000,   8000,   10000,  40000,
                      80000, 100000, 400000, 800000, 1000000};

/* amount of datasets */
const int chunkslen = sizeof(CHUNKSIZE) / sizeof(CHUNKSIZE[0]);

int main() {
  generateDatasets();
  createArraysFromDatasets();

  /********************* DEBUG ********************* */
  /* int test[]{10, 8, 0, 9, 4, 1, -5}; */
  /* insertionSort(test, 7); */
  /* selectionSort(test, 7); */
  /* quickSort(test, 0, 7); */
  /* mergeSort(test, 0, 7, 7); */
  /* bubbleSort(test, 7); */
  /* heapSort(test, 7); */
  /* arrayinfo(test, 7); */

  /* return 0; */
}

void generateDatasets() {
  srand(777);

  /* Iterate over the pre-defined sizes*/
  for (size_t i = 0; i < chunkslen; i++) {

    std::string chunk = "";

    /* Concatenate the proper amount of random integers into a chunk */
    for (int j = 0; j < CHUNKSIZE[i]; j++)
      chunk += std::to_string(rand() % 1000000) + ",";

    /* Write chunk to file named "<size>_dataset.txt" */
    std::ofstream outfile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");
    outfile << chunk;
    outfile.close();
  }

  std::cout << "Datasets generated" << std::endl;
}

void createArraysFromDatasets() {

  for (size_t tmp = 0; tmp < 3; ++tmp) {

    /* Notes:
     * This is an unsafe workaround allocating dynamic memory to store varying
     * size arrays. It'd be safer(ideally) to use std::vector<std::vector> or my
     * own implementation of an array struct.
     *
     * This workaround is merely used for terms of simplicity and reduction of
     * repetition Since the assignment requires arrays
     * */

    /* Create a vector of pointers to contain the arrays to sort*/
    std::vector<int *> uns_arrays = std::vector<int *>();
    uns_arrays.reserve(10);

    /* Populate vector with arrays to sort with its correct size */
    for (size_t i = 0; i < chunkslen; ++i)
      uns_arrays.push_back(new int[CHUNKSIZE[i]]);

    /* **************************************** */

    /* Iterate through every file */
    for (size_t i = 0; i < chunkslen; ++i) {

      /* Read file with proper size/name */
      std::ifstream infile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");

      /* tmp string to grab the int */
      std::string data = "";
      /* index to insert data */
      int j = 0;

      /* Read line using comma as delimeter */
      while (std::getline(infile, data, ',') && !infile.eof()) {
        std::stringstream ss(data);

        /* Insert the data */
        ss >> uns_arrays[i][j];
        j++;
      }

      /* Close every file after done with it */
      infile.close();
    }

    std::cout << "\nArrays populated" << std::endl;

    std::cout << "\n\nRun: " << tmp + 1 << std::endl;
    calculateTime(uns_arrays, false);

    /* free up memory */
    for (auto &arr : uns_arrays)
      delete arr;

    uns_arrays.clear();
  }
}

/* *********************************************************************** */

/* IMPLEMENTATION OF SORTS AND UTILITY FUNCTIONS */

void calculateTime(std::vector<int *> &uns_arrays, bool print) {

  for (size_t i = 0; i < chunkslen; ++i) {

    /************************************************
     *                                              *
     *     Uncomment the algorithm to test          *
     *                                              *
     ************************************************/

    /* Start measuring time */
    auto start = std::chrono::system_clock::now();

    selectionSort(uns_arrays[i], CHUNKSIZE[i]);
    /* bubbleSort(uns_arrays[i], CHUNKSIZE[i]); */
    /* insertionSort(uns_arrays[i], CHUNKSIZE[i]); */
    /* mergeSort(uns_arrays[i], 0, CHUNKSIZE[i] - 1, CHUNKSIZE[i]); */
    /* quickSort(uns_arrays[i], 0, CHUNKSIZE[i]); */
    /* heapSort(uns_arrays[i], CHUNKSIZE[i]); */

    /* Stop measuring time */
    auto end = std::chrono::system_clock::now();

    if (print == true)
      arrayinfo(uns_arrays[i], CHUNKSIZE[i]);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                  .count();

    std::cout << "Runtime: " << ms << " ms for " << CHUNKSIZE[i] << " elements"
              << std::endl;
  }
}

void bubbleSort(int *arr, const int &size) {

  /* Classic bubble sort, not "optimized" */
  for (int i = 0; i < size - 1; ++i)
    for (int j = 0; j < size - i - 1; ++j)
      if (arr[j] > arr[j + 1])
        std::swap(arr[j], arr[j + 1]);

  /* arrayinfo(arr, size); */
}

void selectionSort(int *arr, const int &size) {
  int min;

  /* Iterate up until the second to last element */
  for (int i = 0; i < size - 1; i++) {

    min = i;

    /* Find a smaller element */
    for (int j = i + 1; j < size; j++)
      if (arr[j] < arr[min])
        min = j;

    /* Swap the new min with the initial one */
    std::swap(arr[min], arr[i]);
  }
}

int partition(int *arr, const int &lo, const int &hi) {
  int pivot = arr[lo];
  int i = lo;

  for (int j = lo + 1; j < hi; j++)
    if (arr[j] <= pivot) {
      i = i + 1;
      std::swap(arr[i], arr[j]);
    }

  std::swap(arr[i], arr[lo]);
  return i;
}

void quickSort(int *arr, const int &lo, const int &hi) {
  int pivot;

  if (lo < hi) {
    pivot = partition(arr, lo, hi);

    /* Sort left partition */
    quickSort(arr, lo, pivot);

    /* Sort right partition */
    quickSort(arr, pivot + 1, hi);
  }

  /* arrayinfo(arr, hi); */
}

void buildHeap(int *arr, const int &size, const int &lrg) {

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
  if (tmplrg != lrg) {
    std::swap(arr[lrg], arr[tmplrg]);

    /* call function recursively using the new largest */
    buildHeap(arr, size, tmplrg);
  }
}

void heapSort(int *arr, const int &size) {

  /* Build max heap */
  for (int i = size / 2 - 1; i >= 0; i--)
    buildHeap(arr, size, i);

  /* Heap sort */
  for (int i = size - 1; i > 0; i--) {

    std::swap(arr[0], arr[i]);

    /* Get the largest element as root node */
    buildHeap(arr, i, 0);
  }

  /* arrayinfo(arr, size); */
}

void merge(int *arr, const int &l, const int &m, const int &r, const int &size) {
  int size1 = m - l + 1;
  int size2 = r - m;

  /* Left and right halves: This might become an issue with an array that */
  /* doesn't fit on the stack, then we'd need to create them on the heap */
  int left[size1];
  int right[size2];

  /* Populate the arrays */
  for (int i = 0; i < size1; i++)
    left[i] = arr[l + i];

  for (int j = 0; j < size2; j++)
    right[j] = arr[m + 1 + j];

  /* Keep track of both tmp arrays indexes and main arr */
  int i = 0, j = 0;
  int k = l;

  while (i < size1 && j < size2) {
    if (left[i] <= right[j]) {
      arr[k] = left[i];
      i++;
    } else {
      arr[k] = right[j];
      j++;
    }
    k++;
  }

  /* Move the elements left from both tmp arrays back */
  while (i < size1) {
    arr[k] = left[i];
    i++;
    k++;
  }

  while (j < size2) {
    arr[k] = right[j];
    j++;
    k++;
  }

  /* arrayinfo(arr, size); */
}

void mergeSort(int *arr, const int &l, const int &r, const int &size) {
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

void insertionSort(int *arr, const int &size) {
  int low, j;

  /* Iterate from the second to last element */
  for (int i = 1; i < size; ++i) {
    low = arr[i];
    j = i - 1;

    /* Push elements if they're greater than curr key*/
    while (j >= 0 && arr[j] > low) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = low;
  }

  /* arrayinfo(arr, size); */
}

void arrayinfo(int *arr, const int &size) {
  std::cout << "\n\n" << size << " elements" << std::endl;
  std::cout << "And the last element is: " << arr[size - 1] << std::endl;

  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
}

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

  return 0;
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

    std::cout << "\n\nRun: " << tmp+1 << std::endl;
    calculateTime(uns_arrays, false);

    /* free up memory */
    for (auto &arr : uns_arrays)
      delete arr;

    uns_arrays.clear();
  }
}

/* *********************************************************************** */

/* IMPLEMENTATION OF SORTS AND UTILITY FUNCTIONS */

void calculateTime(std::vector<int *> uns_arrays, bool print) {

  for (size_t i = 0; i < chunkslen; ++i) {

    /************************************************
     *                                              *
     *     Uncomment the algorithm to test          *
     *                                              *
     ************************************************/

    /* Start measuring time */
    auto start = std::chrono::system_clock::now();

    /* selectionSort(uns_arrays[i], CHUNKSIZE[i]); */
    bubbleSort(uns_arrays[i], CHUNKSIZE[i]);
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

void bubbleSort(int *arr, const int size) {

  for (int i = 0; i < size - 1; ++i)
    for (int j = 0; j < size - i - 1; ++j)
      if (arr[j] > arr[j + 1])
        std::swap(arr[j], arr[j + 1]);

  /* arrayinfo(arr, size); */
}

void selectionSort(int *arr, const int size) {
  int low, j;

  for (int i = 1; i < size; ++i) {
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

void merge(int *arr, const int l, const int m, const int r, const int size) {
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
  std::cout << "\n\n" << size << " elements" << std::endl;
  std::cout << "And the last element is: " << arr[size - 1] << std::endl;

  for (int i = 1; i < size; i++) {
    std::cout << arr[i] << " ";
  }
}

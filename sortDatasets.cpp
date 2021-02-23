#include <array>
#include <chrono>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include "algorithms/bubble_sort.h"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/utils.h"

int pcopy(const int *arr, int beg, int end);
void generateDatasets();
void createArraysFromDatasets();
void calculateTime(int *uns_arrays, bool print);

/* Fixed sizes for every dataset */
 const int CHUNKSIZE[] { 1000,  4000,   8000,   10000,  40000, 80000, 100000,
                        400000, 800000, 1000000 };

/* const int CHUNKSIZE[]{400000,  1000000, 2000000, 3000000, 4000000,  5000000, */
/*                       6000000, 7000000, 8000000, 9000000, 10000000, 20000000}; */

/* const int CHUNKSIZE[]{20000000}; */

/* Amount of datasets */
const int chunkslen = sizeof(CHUNKSIZE) / sizeof(CHUNKSIZE[0]);

int main() {
  generateDatasets();
  createArraysFromDatasets();

  return 0;
}

void generateDatasets()
// Creates datasets files
{
  srand(777);

  /* Iterate over the pre-defined sizes*/
  for (size_t i = 0; i < chunkslen; i++) {

    std::string chunk = "";
    chunk.reserve(640000);

    /* Concatenate the proper amount of random integers into a chunk */
    for (int j = 0; j < CHUNKSIZE[i]; j++)
      chunk += std::to_string(rand() % 1000000) + ",";

    /* Write chunk to file named "<size>_dataset.txt" */
    std::ofstream outfile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");
    outfile << chunk;
    outfile.close();
  }

  std::cout << "Datasets generated\n";
} // End generateDatasets

void createArraysFromDatasets()
// Creates and populates arrays using dataset files. Calls the calculateTime
// three times
{

  /* for (size_t tmp = 0; tmp < 3; ++tmp) { */
  int **uns_arrays = new int *[chunkslen];

  /* Populate vector with arrays to sort with its correct size */
  for (size_t i = 0; i < chunkslen; ++i)
    uns_arrays[i] = new int[CHUNKSIZE[i]];

  /* **************************************** */

  /* Iterate through every file */
  for (unsigned int i = 0; i < chunkslen; ++i) {

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
  } // End for

  std::cout << "\nArrays populated\n";

  /* std::cout << "\n\nRun: " << tmp + 1 << "\n"; */
  calculateTime(*uns_arrays, false);

  /* free up memory */

  delete[] uns_arrays;

  /* } // End of outer for */
} // End createArraysFromDatasets

/*          IMPLEMENTATION OF SORTS AND UTILITY FUNCTIONS */
/************************************************************************/
int **fragmt(int *arr, const size_t size) {
  int **ret = new int *[2];
  /* ls */
  *ret[0] = pcopy(arr, 0, size / 2 + 1);
  /* rs */
  *ret[1] = pcopy(arr, size / 2 + 1, size);
  return ret;
}

void calculateTime(int *uns_arrays, bool print)
// Sorts all of the datasets with a selected sort algorithm  and calculates time
{

  for (size_t i = 0; i < chunkslen; ++i) {

    /************************************************
     *                                              *
     *     Uncomment the algorithm to test          *
     *                                              *
     ************************************************/

    /* Start measuring time */
    auto start = std::chrono::system_clock::now();

    /* selectionSort(&uns_arrays[i], CHUNKSIZE[i]); */
    /* bubbleSort(&uns_arrays[i], CHUNKSIZE[i]); */
    /* insertionSort(&uns_arrays[i], CHUNKSIZE[i]); */
    mergeSort(&uns_arrays[i], 0, CHUNKSIZE[i] - 1, CHUNKSIZE[i]);
    /* quickSort(&uns_arrays[i], 0, CHUNKSIZE[i]); */
    /* heapSort(&uns_arrays[i], CHUNKSIZE[i]); */

    /* Stop measuring time */
    auto end = std::chrono::system_clock::now();

    /* if (print == true) */
      arrayinfo(&uns_arrays[i], CHUNKSIZE[i]);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                  .count();

    std::cout << "\n\nRuntime: " << ms << " ms for " << CHUNKSIZE[i] << " elements\n";
              
  } // End for
} // End calculateTime

int pcopy(const int *arr, int beg, int end) {
  int *ret = new int[end];

  for (int i = beg; i < end; ++i)
    ret[i] = arr[i];

  return *ret;
}

/* TODO */
/* merge arrays of pointers */ 
/* int pmerge(const int arr, int* arr, int &size1, int &size2) { */

/* } */

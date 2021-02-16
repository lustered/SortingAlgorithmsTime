#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "algorithms/bubble_sort.h"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/utils.h"

void generateDatasets();
void createArraysFromDatasets();
void arrayinfo(int *arr, int size);

const int CHUNKSIZE[]{1000,  4000,   8000,   10000,  40000,
                      80000, 100000, 400000, 800000, 1000000};
const int chunkslen = sizeof(CHUNKSIZE) / sizeof(CHUNKSIZE[0]);

int main() {

  generateDatasets();
  createArraysFromDatasets();
  return 0;
}

void generateDatasets() {
  /* create chunk */
  srand(777);

  for (size_t i = 0; i < chunkslen; i++) {

    std::string chunk = "";

    for (int j = 0; j < CHUNKSIZE[i]; j++)
      chunk += std::to_string(rand() % 1000000) + ",";

    /* Write chunk to file */
    std::ofstream outfile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");
    outfile << chunk;
    outfile.close();
  }

  std::cout << "Datasets generated" << std::endl;
}

void createArraysFromDatasets() {

  /* Create a vector of arrays pointers */
  std::vector<int *> uns_arrays = std::vector<int *>();
  uns_arrays.reserve(10);

  /* Populate vector with arrays */
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

  std::cout << "Arrays populated" << std::endl;
  mergeSort(uns_arrays[9], 0, CHUNKSIZE[9]-1, CHUNKSIZE[9]);
  /* bubbleSort(uns_arrays[9], CHUNKSIZE[9]); */
  arrayinfo(uns_arrays[9], CHUNKSIZE[9]);

  /* print all the arrays */
  /* for (size_t i = 0; i < chunkslen; ++i) */
  /*     arrayinfo(uns_arrays[i], CHUNKSIZE[i]); */

  /* free up memory */
  for (auto arr : uns_arrays)
    delete arr;

  uns_arrays.clear();
}

/* Create a helper function to print an array inside a vector */
void arrayinfo(int *arr, const int size) {
  std::cout << size << " elements" << std::endl;
  std::cout << "And the last element is: " << arr[size - 1] << std::endl;

  for (int i = 1; i < size; i++) {
    std::cout << arr[i] << " ";
  }

  std::cout << "\n\n";
}

## Compilation and execution instructions

    g++ -std=c++11 -Wall Carlos_Luis_sorts.cpp
    ./a.out

#### To choose the algorithm, uncomment the lines 166-171. A single algorithm was tested each run.

    /* selectionSort(uns_arrays[i], CHUNKSIZE[i]); */
    /* bubbleSort(uns_arrays[i], CHUNKSIZE[i]); */
    /* insertionSort(uns_arrays[i], CHUNKSIZE[i]); */
    mergeSort(uns_arrays[i], 0, CHUNKSIZE[i] - 1, CHUNKSIZE[i]);
    /* quickSort(uns_arrays[i], 0, CHUNKSIZE[i]); */
    /* heapSort(uns_arrays[i], CHUNKSIZE[i]); */

## Verbose output of sorted arrays

#### If you want verbose output of the arrays after being sorted, change the second param to true in line 136.

##### Example

    calculateTime(uns_arrays, true)

#### Function signature

    void calculateTime(std::vector<int*> &uns_arrays, bool print = false);


| print |                                |
| ----- | ------------------------------ |
| false (default)| Does not print array when done |
| true           | Prints array when done         |

### The pre-defined sizes-to-index for the datasets:

| Size    | index |
| ------- | ----- |
| 1000    | 0     |
| 4000    | 1     |
| 8000    | 2     |
| 10000   | 3     |
| 40000   | 4     |
| 80000   | 5     |
| 100000  | 6     |
| 400000  | 7     |
| 800000  | 8     |
| 1000000 | 9     |

## Misc

### System properties

    Ubuntu linux kernel: 4.15.0-72-generic
    g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
    16 GB DDR4 RAM
    Solid State Drive
    Intel i7-6700HQ CPU


### Method used to create data.log using a bash script

    ./run.sh >> data.log

### Creating and running executable  

    g++ -Wall -o Carlos_Luis_sorts.exe Carlos_Luis_sorts.cpp
    ./Carlos_Luis_sorts.exe

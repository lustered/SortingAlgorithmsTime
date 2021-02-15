#ifndef HELPERS_H
#define HELPERS_H
 
void createArrays(){
    /* Hold arrays with values */
    std::vector<int*> uns_arrays = std::vector<int*>();

    for (int i = 0; i < chunkslen; i++) {

        /* Open the files in order */
        std::fstream infile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt", std::ios_base::in);

        std::string data;

        /* Create a temporary array to hold the values in the files. We will use this */
        /* to push them onto the vector containing all the values. */
        int tmparr[CHUNKSIZE[i]];

        int j = 0;
        while(getline(infile, data, ',')){
            tmparr[j] = std::stoi(data);
            j++;
        }

        std::cout << i+1 << " Arrays populated with ." << j << "elements" << std::endl;

        uns_arrays.push_back(tmparr);
    }

    std::cout << uns_arrays.at(0)[990];
    /* std::cout << uns_arrays.at(0)[0]; */
}


/* This seems rather ugly in my opinion */
int arr0[CHUNKSIZE[0]]; 
int arr1[CHUNKSIZE[1]]; 
int arr2[CHUNKSIZE[2]]; 
int arr3[CHUNKSIZE[3]]; 
int arr4[CHUNKSIZE[4]]; 
int arr5[CHUNKSIZE[5]]; 
int arr6[CHUNKSIZE[6]]; 
int arr7[CHUNKSIZE[7]]; 
int arr8[CHUNKSIZE[8]]; 
int arr9[CHUNKSIZE[9]]; 

    /* const size_t size = 10; */
    /* int** uns_arrays = new int*[size]; */

    /* /1* Initialize the correct sizes for the arrays *1/ */
    /* for (size_t i = 0; i < chunkslen; ++i) { */
    /*     uns_arrays[i] = new int[CHUNKSIZE[i]]; */

    /*     std::ifstream infile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt"); */
    /*     std::string line; */
    /*     int* arr */

    /*     while(std::getline(infile, line)) */
    /*     { */
    /*         std::istringstream iss(line); */
    /*         int n; */
    /*         while(iss >> n) */
    /*             uns_arrays[i] */ 
            
    /*     } */

    /* } */

    /* /1* free up memory on the heap *1/ */
    /* for (size_t i = 0; i < chunkslen; ++i) */
    /*     delete uns_arrays[i]; */

    /* delete uns_arrays; */
#endif

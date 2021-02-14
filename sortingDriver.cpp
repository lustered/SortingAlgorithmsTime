#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

void generateDatasets();
void createArraysFromDatasets();
void displayArraysInVector(int arr[], int size);

const int CHUNKSIZE[] {1000, 4000, 8000, 10000, 40000, 80000, 100000, 400000, 800000, 1000000};
const int chunkslen = sizeof(CHUNKSIZE) / sizeof(CHUNKSIZE[0]); 

int main(){

    /* generateDatasets(); */
    createArraysFromDatasets();
    return 0;
}

void generateDatasets(){
    /* create chunk */
    std::string chunk = "";

    for (size_t i = 0; i < 10; i++) {

        for (size_t j = 0; j < CHUNKSIZE[i]; j++) 
            /* chunk +=  std::to_string(rand() % 1000000) + ","; */ 
            chunk +=  std::to_string(rand() % 10) + ","; 

        /* Write chunks to file */
        std::ofstream outfile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");
        outfile << chunk;
        outfile.close();
    }

    std::cout << "Datasets generated" << std::endl;
}

void createArraysFromDatasets(){
    
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

/* Create a helper function to print an array inside a vector */
void displayArraysInVector(int arr[], int size){
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] <<  " , ";
    }
}

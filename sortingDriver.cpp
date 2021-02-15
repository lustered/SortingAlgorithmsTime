#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

void generateDatasets();
void createArraysFromDatasets();
void arrayinfo(int* arr, int size);

const int CHUNKSIZE[] {1000, 4000, 8000, 10000, 40000, 80000, 100000, 400000, 800000, 1000000};
const int chunkslen = sizeof(CHUNKSIZE) / sizeof(CHUNKSIZE[0]); 

int main(){

    generateDatasets();
    createArraysFromDatasets();
    return 0;
}

void generateDatasets(){
    /* create chunk */
    std::string chunk = "";
    srand(777);

    for (size_t i = 0; i < 10; i++) {

        for (size_t j = 0; j < CHUNKSIZE[i]; j++) 
            chunk +=  std::to_string(rand() % 1000000) + "," + "\n"; 

        /* Write chunks to file */
        std::ofstream outfile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");
        outfile << chunk;
        outfile.close();
    }

    std::cout << "Datasets generated" << std::endl;
}

void createArraysFromDatasets(){
    
    std::vector<int*> uns_arrays = std::vector<int*>();

    /* Populate vector with arrays on the heap. Arrays in RAM will
     * overflow. */
    for (size_t i = 0; i < chunkslen; ++i) {
        uns_arrays.push_back(new int[CHUNKSIZE[i]]);
    }

    for (size_t i = 0; i < chunkslen-1; ++i) {

    /* std::ifstream infile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt", std::ios_base::in); */
        std::ifstream infile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");

        std::string data = "";
        /* data.reserve(1748576); */
        int j = 0;

        while(std::getline(infile, data, ','))
        {
            try{
                uns_arrays.at(i)[j] = std::stoi(data);
            }
            catch(std::invalid_argument){
                std::cout << "Bad input" << std::endl;
            }

            j++;
        }

        infile.close();
    }

    /* std::cout << uns_arrays.at(0)[999] << std::endl; */
    arrayinfo(uns_arrays.at(0),CHUNKSIZE[0]);
}

/* Create a helper function to print an array inside a vector */
void arrayinfo(int* arr, int size){
    std::cout << size << " elements" << std::endl;
    std::cout << "And the last element is: " << arr[size-1] << std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << arr[i] <<  "  ";
    }

    std::cout << std::endl << std::endl;
}

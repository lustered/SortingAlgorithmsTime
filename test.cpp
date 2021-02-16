#include <iostream>
#include <fstream>
#include <sstream>

void replace(int* arr, int val);

const int CHUNKSIZE[] {1000, 4000, 8000, 10000, 40000, 80000, 100000, 400000, 800000, 1000000};

int main(){
    int* arr = new int[10];
    arr[0] = 5;
    /* int tmp = 0; */
    
    std::cout << "Array [0] before swap " << arr[0] << std::endl;
    replace(arr, 10);
    std::cout << "Array [0] after swap " << arr[0] << std::endl;

    /* while(tmp < 1000001) */
    /* { */
    /*     arr[tmp] = tmp; */
    /*     tmp++; */
    /* } */

    /* std::cout << tmp << std::endl; */

    return 0;
}

void replace(int arr[], int val){
   arr[0] = val;
}

void generateDatasets(){
    /* create chunk */
    std::string chunk = "";
    srand(777);

    for (size_t i = 0; i < 10; i++) {

        for (int j = 0; j < CHUNKSIZE[i]; j++) 
            chunk +=  std::to_string(rand() % 1000000) + ","; 

        /* Write chunk to file */
        std::ofstream outfile(std::to_string(CHUNKSIZE[i]) + "_dataset.txt");
        outfile << chunk;
        outfile.close();

    }

    std::cout << "Datasets generated" << std::endl;
}

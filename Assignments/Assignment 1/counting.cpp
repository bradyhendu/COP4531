#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "generatearrays.h"



void countingSort(std::vector<int>& arr){
    int n = arr.size();
    std::vector<int> output(n);
    int max = arr[0];
    for(int i = 1; i < n; ++i){
        if(arr[i] > max){
            max = arr[i];
        }
    }

    std::vector<int> count(max + 1, 0);

    for(int i = 0; i < n; ++i){
        count[arr[i]]++;
    }

    for(int i = 1; i <= max; ++i){
        count[i] += count[i - 1];
    }

    for(int i = n - 1; i >= 0; --i){
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for(int i = 0; i < n; ++i){
        arr[i] = output[i];
    }
}

void runCountingSort(std::vector<int>& arr, std::ofstream& outfile){
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    countingSort(arr);
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}

int main(){
    //print a message to the user
    std::cout << "Running counting sort file" << std::endl;

    //open a file to write the results to
    std::ofstream outfile("counting.csv");

    if(!outfile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //write the header of the csv file
    outfile << "Array Size,Time" << std::endl;

    // Array sizes to be tested
    std::vector<int> sizes = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    // Loop over each size, generate array, and run heap sort
    for (int size : sizes) {
        std::vector<int> array = generateArray(size);
        runCountingSort(array, outfile);
    }

    //close the file
    outfile.close();

    //print a message to the user
    std::cout << "Counting sort file has finished running" << std::endl;
}
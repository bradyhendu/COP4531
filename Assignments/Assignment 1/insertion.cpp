#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
//include the generateArray function from generatearrays.cpp
#include "generatearrays.h"

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void runInsertionSort(std::vector<int>& arr, std::ofstream& outfile) {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    insertionSort(arr);
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}

int main (){
    //print a message to the user
    std::cout << "Running insertion sort file" << std::endl;

    //open a file to write the results to
    std::ofstream outfile("insertion.csv");

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
        runInsertionSort(array, outfile);
    }

    //close the file
    outfile.close();

    //print a message to the user
    std::cout << "Insertion sort file has finished running" << std::endl;

    return 0;
}
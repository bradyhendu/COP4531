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

    std::cout << "Elapsed time to run insertion sort with array of size " << arr.size() << ": " << elapsed.count() << " seconds" << std::endl;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}

int main (){
    //open a file to write the results to
    std::ofstream outfile("insertion.csv");

    if(!outfile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //write the header of the csv file
    outfile << "Array Size,Time" << std::endl;


    //generate an array of 10 random integers
    std::vector<int> array = generateArray(10);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 50
    array = generateArray(50);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 100
    array = generateArray(100);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 500
    array = generateArray(500);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 1000
    array = generateArray(1000);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 5000
    array = generateArray(5000);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 10000
    array = generateArray(10000);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 50000
    array = generateArray(50000);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 100000
    array = generateArray(100000);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 500000
    array = generateArray(500000);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //generate an array of 1000000
    array = generateArray(1000000);

    //run the insertion sort algorithm on the array
    runInsertionSort(array, outfile);

    //close the file
    outfile.close();

    return 0;
}
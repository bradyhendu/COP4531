#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "generatearrays.h"


int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            std::swap(arr[i], arr[j]); // Swap the elements
        }
    }
    std::swap(arr[i + 1], arr[high]); //Puts the pivot in the correct position
    return (i + 1); //Returns the position of the pivot
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void runQuickSort(std::vector<int>& arr, std::ofstream& outfile) {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    quickSort(arr, 0, arr.size() - 1);
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}

int main(){
    //open a file to write the results to
    std::ofstream outfile("quicksort.csv");

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
        runQuickSort(array, outfile);
    }

    //close the file
    outfile.close();

    return 0;
}
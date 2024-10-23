#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

//include the generateArray function from generatearrays.cpp
#include "generatearrays.h"

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Same as (left + right) / 2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void runMergeSort(std::vector<int>& arr, std::ofstream& outfile) {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    mergeSort(arr, 0, arr.size() - 1);
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}

int main(){
    //print a message to the user
    std::cout << "Running merge sort file" << std::endl;

    //open a file to write the results to
    std::ofstream outfile("merge.csv");

    if(!outfile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //write the header of the csv file
    outfile << "Array Size,Time" << std::endl;

    // Array sizes to be tested
    std::vector<int> sizes = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    // Loop over each size, generate array, and run merge sort
    for (int size : sizes) {
        std::vector<int> array = generateArray(size);
        runMergeSort(array, outfile);
    }

    //close the file
    outfile.close();

    //print a message to the user
    std::cout << "Merge sort file complete" << std::endl;

    return 0;
}

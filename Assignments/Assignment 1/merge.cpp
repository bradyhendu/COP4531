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
    //open a file to write the results to
    std::ofstream outfile("merge.csv");

    if(!outfile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //write the header of the csv file
    outfile << "Array Size,Time" << std::endl;

    //generate an array of 10 random integers
    std::vector<int> array = generateArray(10);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 50
    array = generateArray(50);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 100
    array = generateArray(100);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 500
    array = generateArray(500);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 1000
    array = generateArray(1000);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 5000
    array = generateArray(5000);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 10000
    array = generateArray(10000);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 50000
    array = generateArray(50000);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 100000
    array = generateArray(100000);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 500000
    array = generateArray(500000);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //generate an array of 1000000
    array = generateArray(1000000);

    //run the merge sort algorithm on the array
    runMergeSort(array, outfile);

    //close the file
    outfile.close();

    return 0;
}

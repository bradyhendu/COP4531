#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "generatearrays.h"

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Use recursion to heapify the sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract an element from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // pass the reduced heap to heapify
        heapify(arr, i, 0);
    }
}

void runHeapSort(std::vector<int>& arr, std::ofstream& outfile) {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    heapSort(arr);
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}

int main (){
    //open a file to write the results to
    std::ofstream outfile("heapsort.csv");

    if(!outfile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //write the header of the csv file
    outfile << "Array Size,Time" << std::endl;

    //generate an array of 10 random integers
    std::vector<int> array = generateArray(10);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 50
    array = generateArray(50);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 100
    array = generateArray(100);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 500
    array = generateArray(500);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 1000
    array = generateArray(1000);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 5000
    array = generateArray(5000);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 10000
    array = generateArray(10000);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 50000
    array = generateArray(50000);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 100000
    array = generateArray(100000);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 500000
    array = generateArray(500000);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //generate an array of 1000000
    array = generateArray(1000000);

    //run the heap sort algorithm on the array
    runHeapSort(array, outfile);

    //close the file
    outfile.close();

    return 0;
}
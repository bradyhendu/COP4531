#include <iostream>
#include <chrono>
//include the generateArray function from generatearrays.cpp
#include "generatearrays.h"

void insertionSort(int arr[], int n) {
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

int main (){
    //generate an array of 10 random integers
    std::vector<int> array = generateArray(10);
    int n = array.size();
    int arr[n];
    //copy the vector to an array
    for (int i = 0; i < n; ++i) {
        arr[i] = array[i];
    }
    //print the array before sorting
    std::cout << "Array before sorting: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    //sort the array
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(arr, n);
    auto end = std::chrono::high_resolution_clock::now();
    //print the array after sorting
    std::cout << "Array after sorting: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::endl << "Time it takes to run operation: " << duration.count() << std::endl;
    return 0;
}
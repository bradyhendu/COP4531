#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "generatearrays.h"

void radixSort(std::vector<int>& arr) {
    // Find the maximum number to know the number of digits
    int n = arr.size();
    int max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Do counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        std::vector<int> output(n);
        std::vector<int> count(10, 0);

        for (int i = 0; i < n; ++i) {
            count[(arr[i] / exp) % 10]++;
        }
        
        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; --i) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; ++i) {
            arr[i] = output[i];
        }
    }
}

void runRadixSort(std::vector<int>& arr, std::ofstream& outfile) {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    radixSort(arr);

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}

int main() {
    //print a message to the user
    std::cout << "Running radix sort file" << std::endl;

    //open a file to write the results to
    std::ofstream outfile("radix.csv");

    if (!outfile.is_open()) {
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
        runRadixSort(array, outfile);
    }

    //close the file
    outfile.close();

    //print a message to the user
    std::cout << "Finished running radix sort file" << std::endl;

    return 0;
}
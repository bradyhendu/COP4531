#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "generatearrays.h"


void bucketInsertionSort(std::vector<float>& bucket){
    int n = bucket.size();
    for(int i = 1; i < n; ++i){
        float key = bucket[i];
        int j = i - 1;

        while(j >= 0 && bucket[j] > key){
            bucket[j + 1] = bucket[j];
            j = j - 1;
        }
        bucket[j + 1] = key;
    }
}

void bucketSort(std::vector<float>& arr){
    int n = arr.size();
    std::vector<std::vector<float>> bucket(n);

    for(int i = 0; i < n; ++i){
        int bucketIndex = n * arr[i];
        bucket[bucketIndex].push_back(arr[i]);
    }

    for(int i = 0; i < n; ++i){
        bucketInsertionSort(bucket[i]);
    }

    int index = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < bucket[i].size(); ++j){
            arr[index++] = bucket[i][j];
        }
    }
}

void runBucketSort(std::vector<float>& arr, std::ofstream& outfile){
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    bucketSort(arr);
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    outfile << arr.size() << "," << elapsed.count() << std::endl;
}



int main(){
    //print a message to the user
    std::cout << "Running bucket sort file" << std::endl;

    //open a file to write the results to
    std::ofstream outfile("bucket.csv");

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
        std::vector<float> array = generateArrayReals(size);
        runBucketSort(array, outfile);
    }

    
    //close the file
    outfile.close();

    //print a message to the user
    std::cout << "Bucket sort file has finished running" << std::endl;

    return 0;
}
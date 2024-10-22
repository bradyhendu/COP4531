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
    //open a file to write the results to
    std::ofstream outfile("bucket.csv");

    if(!outfile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //write the header of the csv file
    outfile << "Array Size,Time" << std::endl;

    //generate an array of 10 random reals
    std::vector<float> array = generateArrayReals(10);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 50 random reals
    array = generateArrayReals(50);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 100 random reals
    array = generateArrayReals(100);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 500 random reals
    array = generateArrayReals(500);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 1000 random reals
    array = generateArrayReals(1000);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 5000 random reals
    array = generateArrayReals(5000);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 10000 random reals
    array = generateArrayReals(10000);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 50000 random reals
    array = generateArrayReals(50000);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 100000 random reals
    array = generateArrayReals(100000);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 500000 random reals
    array = generateArrayReals(500000);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    //generate an array of 1000000 random reals
    array = generateArrayReals(1000000);

    //run the bucket sort algorithm on the array
    runBucketSort(array, outfile);

    
    //close the file
    outfile.close();

    return 0;
}
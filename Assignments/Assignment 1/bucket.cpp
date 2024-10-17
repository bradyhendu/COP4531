#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "generatearrays.h"



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

    


    //close the file
    outfile.close();

    return 0;
}
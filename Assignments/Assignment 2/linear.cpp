#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>

const int TABLE_SIZE = 1000000; // Hash table size
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(-2147483647, 2147483647);

// Hash table class with linear probing
class HashTable {
private:
    std::vector<int> table;
    int probeCount;

public:
    HashTable() : table(TABLE_SIZE, -1), probeCount(0) {}

    int hash(int key) {
        return abs(key) % TABLE_SIZE; // Primary hash function
    }

    void insert(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i) % TABLE_SIZE] != -1) { // Linear probing
            ++i;
            ++probeCount;
        }
        table[(index + i) % TABLE_SIZE] = key;
        ++probeCount; // Count the successful probe
    }

    double getAverageProbes(int keysInserted) const {
        return static_cast<double>(probeCount) / keysInserted;
    }
};


int main() {
    std::srand(std::time(nullptr));
    std::vector<double> loadFactors = {0.5, 0.6, 0.7, 0.8, 0.9};

    // Open a file to write results
    std::ofstream outputFile("linear_probing_results.csv");
    if (!outputFile) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return 1;
    }

    // Write CSV header
    outputFile << "Load Factor,Average Probes" << std::endl;

    for (double alpha : loadFactors) {
        int keysToInsert = static_cast<int>(alpha * TABLE_SIZE);
        HashTable hashTable;

        for (int i = 0; i < keysToInsert; ++i) {
            int key = dist(rng);
            hashTable.insert(key);
        }

        double avgProbes = hashTable.getAverageProbes(keysToInsert);
        std::cout << "Load Factor: " << alpha
                  << " | Avg Probes: " << avgProbes << std::endl;

        // Write the results to the file
        outputFile << alpha << "," << avgProbes << std::endl;
    }

    outputFile.close();
    std::cout << "Results written to linear_probing_results.csv" << std::endl;
    return 0;
}
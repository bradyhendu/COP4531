#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>

const int TABLE_SIZE = 1000000; // Hash table size
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(-2147483647, 2147483647);

// Hash table class with double hashing
class HashTable {
private:
    std::vector<int> table;
    int probeCount;

    int hash1(int key) {
        return abs(key) % TABLE_SIZE; // Primary hash function
    }

    int hash2(int key) {
        int step = 1 + (abs(key) % (TABLE_SIZE - 1)); // Secondary hash function
        return (step % 2 == 0) ? step + 1 : step; // Ensure step is odd
    }

public:
    HashTable() : table(TABLE_SIZE, -1), probeCount(0) {}

    void insert(int key) {
        int index1 = hash1(key);
        int step = hash2(key);
        int i = 0;

        // Probe sequence: (index1 + i * step) % TABLE_SIZE
        while (table[(index1 + i * step) % TABLE_SIZE] != -1) {
            ++i;
            ++probeCount;
        }
        table[(index1 + i * step) % TABLE_SIZE] = key;
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
    std::ofstream outputFile("double_hashing_results.csv");
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
    std::cout << "Results written to double_hashing_results.csv" << std::endl;
    return 0;
}

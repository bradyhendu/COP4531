#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>

const int TABLE_SIZE = 1000000; // Hash table size
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(-2147483647, 2147483647);

class HashTable {
private:
    std::vector<int> table;
    int probeCount;

    // Initial hash function h1(k)
    int hash1(int key) {
        return abs(key) % TABLE_SIZE; // Simple modulo-based hash
    }

    // Jump sequence function f(i)
    int jumpSequence(int i) {
        return i * i + 7 * i; // Quadratic probing with offset
    }

public:
    HashTable() : table(TABLE_SIZE, -1), probeCount(0) {}

    void insert(int key) {
        int index1 = hash1(key);
        int i = 0;

        while (i < TABLE_SIZE) { // Ensure we probe at most TABLE_SIZE times
            int newIndex = (index1 + jumpSequence(i)) % TABLE_SIZE;
            if (table[newIndex] == -1) { // Found an empty slot
                table[newIndex] = key;
                ++probeCount;
                return;
            }
            if (i % 100000 == 0 && i > 0) { // Debugging: Print progress
                std::cout << "Probing key: " << key << ", Probe count: " << i << ", Current index: " << newIndex << std::endl;
            }
            ++i;
            ++probeCount;
        }

        std::cerr << "Error: Hash table is full. Unable to insert key: " << key << std::endl;
    }

    double getAverageProbes(int keysInserted) const {
        return static_cast<double>(probeCount) / keysInserted;
    }
};

int main() {
    std::srand(std::time(nullptr));
    std::vector<double> loadFactors = {0.5, 0.6, 0.7, 0.8, 0.9};

    std::ofstream outputFile("part1_probing_results.csv");
    if (!outputFile) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return 1;
    }

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

        outputFile << alpha << "," << avgProbes << std::endl;
    }

    outputFile.close();
    std::cout << "Results written to part1_probing_results.csv" << std::endl;
    return 0;
}

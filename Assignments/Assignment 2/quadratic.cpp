#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>

const int TABLE_SIZE = 1000003; // Prime table size
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(-2147483647, 2147483647);

class HashTable {
private:
    std::vector<int> table;
    int probeCount;

    int hash1(int key) {
        return abs(key) % TABLE_SIZE; // Primary hash function
    }

public:
    HashTable() : table(TABLE_SIZE, -1), probeCount(0) {}

    void insert(int key) {
        int index1 = hash1(key);
        int i = 0;

        // Probe sequence: (index1 + c1 * i + c2 * i^2) % TABLE_SIZE
        while (i < TABLE_SIZE) { // Terminate after TABLE_SIZE probes
            int newIndex = (index1 + i + i * i) % TABLE_SIZE; // c1 = 1, c2 = 1
            if (table[newIndex] == -1) {
                table[newIndex] = key;
                ++probeCount;
                return;
            }
            if (i % 100000 == 0 && i > 0) { // Debugging: Print every 100,000 probes
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

    std::ofstream outputFile("quadratic_probing_results.csv");
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
    std::cout << "Results written to quadratic_probing_results.csv" << std::endl;
    return 0;
}
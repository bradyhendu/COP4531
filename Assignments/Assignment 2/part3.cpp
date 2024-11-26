#include <iostream>
#include <unordered_map>
#include <cmath>
#include <random>
#include <fstream>

const unsigned int MODULO = 2147483647; // 2^31 - 1 (prime modulus)
const unsigned int PRIMITIVE_ROOT = 7;  // Generator g

// Modular multiplication
unsigned int modmult(unsigned int a, unsigned int b) {
    return ((uint64_t)a * b) % MODULO; // Use 64-bit multiplication
}

// Modular exponentiation
unsigned int modexp(unsigned int base, unsigned int exp) {
    unsigned int result = 1;
    unsigned int power = base;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = modmult(result, power);
        }
        power = modmult(power, power);
        exp /= 2;
    }
    return result;
}

// Baby-step giant-step algorithm
unsigned int discreteLog(unsigned int g, unsigned int x, unsigned int hashTableSize, unsigned int& steps) {
    unsigned int m = (unsigned int)sqrt(MODULO) + 1;

    // Step 1: Create hash table for baby steps
    std::unordered_map<unsigned int, unsigned int> hashTable;
    unsigned int babyStep = 1;

    steps = 0;
    for (unsigned int j = 0; j < m; ++j) {
        hashTable[babyStep] = j; // Store baby step value and index
        babyStep = modmult(babyStep, g); // g^k (mod MODULO)
        steps++; // Count baby step insertion
    }

    // Step 2: Compute giant steps
    unsigned int giantStep = modexp(g, MODULO - m - 1); // g^(-m) mod MODULO
    unsigned int current = x;

    for (unsigned int i = 0; i < m; ++i) {
        steps++; // Count giant step computation
        auto it = hashTable.find(current);
        if (it != hashTable.end()) {
            return i * m + it->second; // Match found
        }
        current = modmult(current, giantStep); // x * g^(-jm) mod MODULO
    }

    return -1;  // Logarithm not found
}

int main() {
    std::ofstream outputFile("part3_results.csv");
    if (!outputFile) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return 1;
    }

    outputFile << "Hash Table Size,Average Search Length" << std::endl;

    std::mt19937 rng(std::random_device{}());
    unsigned int m = (unsigned int)sqrt(MODULO) + 1; // Precompute m

    for (int n = 10; n <= 17; ++n) {
        unsigned int hashTableSize = 1 << n; // Hash table size is exactly 2^n
        unsigned int totalSteps = 0;
        int testCount = 1000;

        for (int i = 0; i < testCount; ++i) {
            unsigned int x = rng() % MODULO; // Generate random x
            unsigned int steps = 0;
            unsigned int result = discreteLog(PRIMITIVE_ROOT, x, hashTableSize, steps);

            totalSteps += steps; // Accumulate total steps
        }

        double averageSearchLength = (double)totalSteps / testCount;
        std::cout << "Hash Table Size: " << hashTableSize
                  << " | Average Search Length: " << averageSearchLength << std::endl;

        outputFile << hashTableSize << "," << averageSearchLength << std::endl;
    }

    outputFile.close();
    std::cout << "Results written to part3_results.csv" << std::endl;

    return 0;
}











#include <iostream>
#include <vector>
#include <random>
#include "generatearrays.h"

using namespace std;

vector<int> generateArray(int N) {
    vector<int> array(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 65535);

    for (int i = 0; i < N; ++i) {
        array[i] = dis(gen);
    }

    return array;
}
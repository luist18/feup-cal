#include "sum.h"
#include <chrono>
#include <limits>

int getArraySum(int *sequence, int starter, int length);

string calcSum(int *sequence, int size) {
    int index[size];
    int subsequenceSum[size];

    for (int length = 1; length <= size; length++) {
        int bestIndex = 0;
        int bestSum = INT_MAX;

        for (int starter = 0; starter <= size - length; starter++) {
            int sum = getArraySum(sequence, starter, length);
            if (sum < bestSum) {
                bestIndex = starter;
                bestSum = sum;
            }
        }

        index[length - 1] = bestIndex;
        subsequenceSum[length - 1] = bestSum;
    }

    string result = "";

    for (int i = 0; i < size; i++) {
        result += to_string(subsequenceSum[i]) + "," + to_string(index[i]) + ";";
    }

    return result;
}

int getArraySum(int *sequence, int starter, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        sum += sequence[starter + i];
    }

    return sum;
}


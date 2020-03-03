#include <malloc.h>
#include "partitioning.h"


int s_recursive(int n, int k) {
    if (k == n || k == 1)
        return 1;
    else return s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
}

int s_dynamic(int n, int k) {
    if (k == 1 || k == n)
        return 1;

    int maxSize = n - k + 1;
    int values[maxSize];

    for (int i = 0; i < maxSize; i++)
        values[i] = 1;

    for (int i = 1; i < k; i++)
        for (int j = 1; j < maxSize; j++)
            values[j] = values[j] + (i + 1) * values[j - 1];

    return values[maxSize - 1];
}


int b_recursive(int n) {
    int result = 0;

    for (int i = 1; i <= n; i++) {
        result += s_recursive(n, i);
    }

    return result;
}

// ctrlMarcio
int b_dynamic(int n) {
    int *last = (int *) malloc(sizeof(int)); // the array of the last n
    int *current; // the current array
    int sum = 0;

    for (int i = 0; i < n; i++) {
        current = (int *) malloc(sizeof(int) * i + 1);

        current[0] = 1;
        for (int j = 1; j < i; j++) {
            current[j] = last[j - 1] + (j + 1) * last[j];
            if (i == n - 1)
                sum += current[j]; // sums all numbers in the array except for the first and the last, which are one (spoiler: summed later)
        }
        current[i] = 1;

        free(last); // since last = current in the next line, this frees the array that won't be useful anymore, aka used "last" or the previous "current"
        last = current;
    }
    free(last);

    sum += 2; // (this is later (first and last number of the array, which are 1))

    return sum;
}



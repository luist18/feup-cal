#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

#define IllegalArgumentException -1

class Sudoku {
    int numbers[9][9];

    int countFilled;
    bool columnHasNumber[9][10];
    bool lineHasNumber[9][10];
    bool block3x3HasNumber[3][3][10];

    void initialize();

public:
    Sudoku();

    Sudoku(int nums[9][9]);

    int **getNumbers();

    bool isComplete();

    bool solve();

    void print();

    int minimumPossibilities();

    set<int> getPossibilities(int x, int y);
};

#endif /* SUDOKU_H_ */

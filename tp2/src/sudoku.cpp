#include "sudoku.h"

Sudoku::Sudoku() {
    this->initialize();
}

Sudoku::Sudoku(int nums[9][9]) {
    this->initialize();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (nums[i][j] != 0) {
                int n = nums[i][j];
                numbers[i][j] = n;
                lineHasNumber[i][n] = true;
                columnHasNumber[j][n] = true;
                block3x3HasNumber[i / 3][j / 3][n] = true;
                countFilled++;
            }
        }
    }
}

void Sudoku::initialize() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int n = 0; n < 10; n++) {
                numbers[i][j] = 0;
                lineHasNumber[i][n] = false;
                columnHasNumber[j][n] = false;
                block3x3HasNumber[i / 3][j / 3][n] = false;
            }
        }
    }

    this->countFilled = 0;
}

int **Sudoku::getNumbers() {
    int **ret = new int *[9];

    for (int i = 0; i < 9; i++) {
        ret[i] = new int[9];

        for (int a = 0; a < 9; a++)
            ret[i][a] = numbers[i][a];
    }

    return ret;
}

bool Sudoku::isComplete() {
    return countFilled == 9 * 9;
}

bool Sudoku::solve() {
    int possibilities = minimumPossibilities();
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {

        }
    }

    return false;
}

void Sudoku::print() {
    for (int i = 0; i < 9; i++) {
        for (int a = 0; a < 9; a++)
            cout << this->numbers[i][a] << " ";

        cout << endl;
    }
}

int Sudoku::minimumPossibilities() {
    int minimum = 10;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (numbers[i][j] != 0) continue;

            int amount = 0;

            for (int n = 1; n <= 9; n++) {
                if (!lineHasNumber[i][n] && !columnHasNumber[j][n] && !block3x3HasNumber[i / 3][j / 3][n])
                    amount++;
            }

            if (amount < minimum)
                minimum = amount;
        }
    }

    return minimum;
}

set<int> Sudoku::getPossibilities(int x, int y) {
    set<int> result_set;

    if (numbers[x][y])
        return result_set;

    for (int n = 1; n < 10; n++) {
        if (!lineHasNumber[x][n] && !columnHasNumber[y][n] && !block3x3HasNumber[x / 3][y / 3][n])
            result_set.insert(n);
    }

    return result_set;
}

#include "labyrinth.h"
#include <iostream>

using namespace std;

Labyrinth::Labyrinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labyrinth[i][j] = values[i][j];

    initializeVisited();
}

void Labyrinth::initializeVisited() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            visited[i][j] = false;
}

void Labyrinth::printLabyrinth() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            cout << labyrinth[i][j] << " ";

        cout << endl;
    }
}

bool Labyrinth::findGoal(int x, int y) {
    if (labyrinth[x][y] == 2)
        return true;
    if (labyrinth[x][y] == 0 || visited[x][y])
        return false;

    visited[x][y] = true;

    if (x + 1 < 10 && findGoal(x + 1, y))
        return true;
    if (x - 1 >= 0 && findGoal(x - 1, y))
        return true;
    if (y + 1 < 10 && findGoal(x, y + 1))
        return true;
    if (y - 1 >= 0 && findGoal(x, y - 1))
        return true;

    visited[x][y] = false;

    return false;
}

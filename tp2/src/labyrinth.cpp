#include "labyrinth.h"
#include <iostream>

using namespace std;

Labyrinth::Labyrinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labyrinth[i][j] = values[i][j];
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
    return false;
}

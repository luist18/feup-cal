#ifndef LABYRINTH_H_
#define LABYRINTH_H_

class Labyrinth {
	int labyrinth[10][10];
	bool visited[10][10];

	void initializeVisited();

public:
	Labyrinth(int values[10][10]);

	void printLabyrinth();

	bool findGoal(int x, int y);
};

#endif

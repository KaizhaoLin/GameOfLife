#ifndef GAMERULE_H
#define GAMERULE_H

#include <vector>
using namespace std;

const int COL = 50;
const int ROW = 50;

/* GameRule class defines the rules for cell survival and reproduction */
class GameRule {
public:
	GameRule(int row, int col);
	~GameRule();

	// Getters for the survival and reproduction rules
	/* Minimum neighbors for a cell to stay alive */
	int getMinAlive() const;

	/* Maximum neighbors for a cell to stay alive */
	int getMaxAlive() const;

	/* Minimum neighbors to reproduce */
	int getMinReproduce() const;

	/* Maximum neighbors to reproduce */
	int getMaxReproduce() const;


	/* Set the survival and reproduction rules */
	void setSurviveRule(int min_alive = 2, int max_alive = 3, int min_reproduce = 3, int max_reproduce = 3);

private:
	int row; // Number of rows in the board
	int col; // Number of columns in the board

	// Rule variables for survival and reproduction
	int minAlive; // Minimum number of neighbors for a cell to survive
	int maxAlive; // Maximum number of neighbors for a cell to survive
	int minReproduce; // Minimum number of neighbors to reproduce
	int maxReproduce; // Maximum number of neighbors to reproduce
};

#endif

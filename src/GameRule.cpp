#include "GameRule.h"

/* Constructor: Initializes the game rule with grid size */
GameRule::GameRule(int row, int col)
	: row(row), col(col), 
	  minAlive(2), maxAlive(3), minReproduce(3), maxReproduce(3) {}

GameRule::~GameRule() {}

// Getters for the survival and reproduction rules
int GameRule::getMinAlive() const {
	return minAlive;
}
int GameRule::getMaxAlive() const {
	return maxAlive;
}
int GameRule::getMinReproduce() const {
	return minReproduce;
}
int GameRule::getMaxReproduce() const {
	return maxReproduce;
}

/* Sets the survival and reproduction rules */
void GameRule::setSurviveRule(int min_alive, int max_alive, int min_reproduce, int max_reproduce) {
	minAlive = min_alive;
	maxAlive = max_alive;
	minReproduce = min_reproduce;
	maxReproduce = max_reproduce;
}

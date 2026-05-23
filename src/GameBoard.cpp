#include "GameRule.h"
#include "GameBoard.h"

/* Constructor : Initializes GameBoard with game rule */
GameBoard::GameBoard(GameRule* rule) 
    : row(0), col(0), 
      board(0, vector<int>(0)), 
      gameRule(rule) {}

/* Constructor : Initializes GameBoard with dimensions and game rule */
GameBoard::GameBoard(int row, int col, GameRule* rule)
    : row(row), col(col), 
      board(row, vector<int>(col, 0)), 
      gameRule(rule) {}

/* Copy constructor*/
GameBoard::GameBoard(const GameBoard& gameboard)
    : row(gameboard.row), col(gameboard.col), 
      board(gameboard.board), 
      gameRule(gameboard.gameRule) {}

/* Deconstructor */
GameBoard::~GameBoard() {}

/* Update the board based on the rule */
void GameBoard::update() {
    vector<vector<int>> curBoard = board;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int neighbors = countNeighbors(i, j); // count live neighbors
            if (getCellStatus(i, j) == 1) {
                // check for survive
                if (neighbors >= gameRule->getMinAlive() && neighbors <= gameRule->getMaxAlive()) {
                    curBoard[i][j] = 1;
                }
                else {
                    curBoard[i][j] = 0;
                }
            }
            else {
                // check for reproduce
                if (neighbors >= gameRule->getMinReproduce() && neighbors <= gameRule->getMaxReproduce()) {
                    curBoard[i][j] = 1;
                }
                else {
                    curBoard[i][j] = 0;
                }
            }
        }
    }
    board = curBoard;
}

/* Clear the board by setting all cells to dead */
void GameBoard::clear() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            setCell(i, j, 0);
        }
    }
}

/* Count alive cells surround a particular cell */
int GameBoard::countNeighbors(int x, int y) const {
    // directions for the 8 neighboring cells
    const int directions[][2] = { {-1, -1}, {-1, 0}, {-1, 1},
                                  { 0, -1},          { 0, 1},
                                  { 1, -1}, { 1, 0}, { 1, 1} };

    int count = 0; // neighbor count
    // iterate the neighbors
    for (int i = 0; i < 8; i++) {
        int neighborX = x + directions[i][0];
        int neighborY = y + directions[i][1];
        if (neighborX >= 0 && neighborX < row && neighborY >= 0 && neighborY < col) {
            count += board[neighborX][neighborY];
        }
    }
    return count;
}

/* Set the status of a particular cell*/
void GameBoard::setCell(int x, int y, int status) {
    if (x >= 0 && x < row && y >= 0 && y < col) {
        board[x][y] = status;
    }
}

/* Returns the status of a specific cell */
int GameBoard::getCellStatus(int x, int y) const {
    if (x >= 0 && x < row && y >= 0 && y < col) {
        return board[x][y];
    }
    return -1; // out of bounds
}

/* Return the number of rows in the board*/
int GameBoard::getRow() const {
    return row;
}

/* Return the number of columns in the board*/
int GameBoard::getCol() const {
    return col;
}

/* Access to the vector */
const vector<vector<int>>& GameBoard::getBoardData() const {
    return board;
}

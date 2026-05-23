#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
using namespace std;

class GameRule;

/* Class representing the state of the game board */
class GameBoard {
public:
    /* Constructor : Initializes GameBoard with game rule */
    GameBoard(GameRule* rule);

    /* Constructor : Initializes GameBoard with dimensions and game rule */
    GameBoard(int row, int col, GameRule* rule);

    /* Copy constructor*/
    GameBoard(const GameBoard& gameboard);

    /* Deconstructor */
    ~GameBoard();



    /* Updates the board state */
    void update();

    /* Clear the board */
    void clear();

    /* Set the status of a specific cell */
    void setCell(int x, int y, int status);

    /* Count alive cells surround a particular cell */
    int countNeighbors(int x, int y) const;

    /* Return the status of a specific cell */
    int getCellStatus(int x, int y) const;

    /* Return the number of rows in the board*/
    int getRow() const;

    /* Return the number of columns in the board*/
    int getCol() const;

    /* Access to the vector */
    const vector<vector<int>>& getBoardData() const;

private:
    /* Number of rows in the board */
    int row;

    /* Number of columns in the board */
    int col;

    /* The vector to hold board states */
    vector<vector<int>> board;

    /* Associated game rule */
    GameRule* gameRule;
};

#endif

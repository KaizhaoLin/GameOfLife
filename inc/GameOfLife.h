#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QTimer>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QTextStream>
#include <QtCore/QString>

#include "ui_GameOfLife.h"


class BoardWidget;
class GameBoard;
class GameRule;
class SettingWindow;

/* Main GameOfLife window */ 
class GameOfLife : public QMainWindow {
    Q_OBJECT

public:
    GameOfLife(QWidget *parent = nullptr);
    ~GameOfLife();

    /* Update the board state */
    void updateBoard();

    /* Return the current board */
    GameBoard& getBoard();

private slots:
    /* Update the board state and refresh the display */
    void updateAndDisplay();

    // Button related slots
    /* Adjust the game speed based on the slider value */
    void updateGameSpeed(int value);

    /* Start or pause the game */
    void toggleGameMode();

    /* Open the game settings window */
    void openSettingPage();
    

    // Menu Bar related slots
    /* Back to the selection page */
    void backToHome();

    /* Exits the application */
    void exit();

    /* Save the current board state to a file */
    void saveBoard();

    /* Display tips */
    void showHelp();

signals:
    /* Signal emitted when the user chooses to exit the game */
    void exitGame();

    /* Signal emitted when the user chooses to return to the home page */
    void goBackToHomePage();

private:
    Ui::GameOfLifeClass ui; // UI elements for the window
    QTimer* timer; // Timer for automatic updates

    GameBoard* gameBoard; // Current board
    GameRule* gameRule; // Game rule
    SettingWindow* settingWindow; // Setting window dialog

    QAction* actionBackToHomePage; // Menu action for returning to the home page
    QAction* actionExit; // Menu action for exiting the game
    QAction* actionSaveBoard; // Menu action for saving the board state
    QAction* actionHelp; // Menu action for displaying help

    BoardWidget* boardWidget; // Widget for displaying board
    QPushButton* toggleButton; // Button to start/pause the game
    
    bool isGameRunning; // Indicating if the game is running
    bool isSettingPageOpened; // Indicating if the settings page is open
};


#endif

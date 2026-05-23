#include "GameOfLife.h"
#include "BoardWidget.h"
#include "GameRule.h"
#include "GameBoard.h"
#include "SettingWindow.h"

/* Constructor: Sets up the main window and initializes the game components */
GameOfLife::GameOfLife(QWidget *parent) 
    : QMainWindow(parent),  
      timer(new QTimer(this)), // Initialize timer
      isGameRunning(false) { // Game starts in a paused state

    ui.setupUi(this);

    isSettingPageOpened = false;

    // Initialize game rules and board
    gameRule = new GameRule(ROW, COL);
    gameBoard = new GameBoard(ROW, COL, gameRule);
    
    // Find the related components in the ui file
    // Menu Bar Actions
    actionBackToHomePage = findChild<QAction*>("actionBackToHomePage");
    actionExit = findChild<QAction*>("actionExit");
    actionSaveBoard = findChild<QAction*>("actionSaveBoard");
    actionHelp = findChild<QAction*>("actionHelp");

    // Widgets
    QWidget* container = findChild<QWidget*>("BoardContainer");
    QSlider* gameSpeedSlider = findChild<QSlider*>("gameSpeedSlider");
    toggleButton = findChild<QPushButton*>("toggleButton");
    QPushButton* settingPageButton = findChild<QPushButton*>("SettingPageButton");

    // Initialize the settings window
    settingWindow = new SettingWindow(this, gameRule);
    settingWindow->setAttribute(Qt::WA_DeleteOnClose, false);

    //test board
    //for (int i = 0; i < ROW; i++) {
    //    for (int j = 0; j < COL; j++) {
    //        gameBoard->setCell(i, j, (i + j) % 2);
    //    }
    //}
    
    // Setup game board display
    boardWidget = new BoardWidget(container, gameBoard);
    gameSpeedSlider->setRange(10, 500); // Speed slider range
    gameSpeedSlider->setValue(10); // Default game speed
   
    // Set the layout for board widget
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->addWidget(boardWidget);
    container->setLayout(layout);

    // Set the main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this); 
    mainLayout->addWidget(gameSpeedSlider);
    mainLayout->addWidget(toggleButton);
    mainLayout->addWidget(settingPageButton);

    // Connect UI components to their respective slots
    connect(actionBackToHomePage, &QAction::triggered, this, &GameOfLife::backToHome);
    connect(actionExit, &QAction::triggered, this, &GameOfLife::exit);
    connect(actionSaveBoard, &QAction::triggered, this, &GameOfLife::saveBoard);
    connect(actionHelp, &QAction::triggered, this, &GameOfLife::showHelp);

    connect(gameSpeedSlider, &QSlider::valueChanged, this, &GameOfLife::updateGameSpeed);
    connect(toggleButton, &QPushButton::clicked, this, &GameOfLife::toggleGameMode);
    connect(settingPageButton, &QPushButton::clicked, this, &GameOfLife::openSettingPage);

    // Timer triggers the game update
    connect(timer, &QTimer::timeout, this, &GameOfLife::updateAndDisplay);
    timer->start(500); // Default interval for the timer
}

/* Update the board state and refresh the display */
void GameOfLife::updateAndDisplay() {
    if (isGameRunning) {
        updateBoard(); // Update the game board state
        update(); // Repaint the window
    }
}

/* Perform the game logic update */
void GameOfLife::updateBoard() {
    gameBoard->update();
}

/* Adjust timer interval based on slider value */
void GameOfLife::updateGameSpeed(int value) {
    timer->setInterval(510-value);
}

/* Toggle between start and pause states */
void GameOfLife::toggleGameMode() {
    if (isGameRunning) {
        isGameRunning = false;
        toggleButton->setText("Start");
    }
    else {
        isGameRunning = true;
        toggleButton->setText("Pause");
    }
}

/* Open the game settings window */
void GameOfLife::openSettingPage() {
    // pause the game if it's running
    if (isGameRunning) {
        toggleGameMode();
        isGameRunning = false;
    }
    settingWindow->show(); // show the settings window
}

/* Back to the selection page */
void GameOfLife::backToHome() {
    QMessageBox::StandardButton warningMessage;
    warningMessage = QMessageBox::question(this, "Warning", "This operation will clear your board. Confirm to go back?",
        QMessageBox::Yes | QMessageBox::No);

    if (warningMessage == QMessageBox::Yes) {
        gameBoard->clear(); // Clear the board
        // pause the game if it's running
        if (isGameRunning) {
            toggleGameMode();
            isGameRunning = false;
        }
        goBackToHomePage(); // Emit return signal
    }
}

/* Exits the application */
void GameOfLife::exit() {
    QMessageBox::StandardButton warningMessage;
    warningMessage = QMessageBox::question(this, "Warning", "Are you sure you want to quit the game?",
        QMessageBox::Yes | QMessageBox::No);

    if (warningMessage == QMessageBox::Yes) {
        exitGame(); // Emit exit signal
    }
}

/* Save the current board state to a file */
void GameOfLife::saveBoard() {
    // pause the game if it's running
    if (isGameRunning) {
        toggleGameMode();
        isGameRunning = false;
    }

    // File dialog to select save location
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save File",
        "",
        "csv Files (*.csv)"
    );

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, tr("Error"), tr("Failed to open file for writing."));
            return;
        }
        QTextStream out(&file);
        // write board status to csv file
        for (int i = 0; i < 50; ++i) {
            for (int j = 0; j < 50; ++j) {
                out << gameBoard->getBoardData()[i][j];
                if (j < 49) {
                    out << ",";
                }
            }
            out << "\n";
        }

        file.close();
        QMessageBox::information(this, tr("File Saved"), tr("File saved to: %1").arg(filePath));
    }
}

/* Display tips */
void GameOfLife::showHelp() {
    // pause the game if it's running
    if (isGameRunning) {
        toggleGameMode();
        isGameRunning = false;
    }
    QString helpMessage =
        "Welcome to Game of Life!\n\n"
        "Instructions:\n"
        "1. Click the \"Start\" button to start the program, and use the \"Pause\" button to pause it.\n"
        "2. You can change the state of the cells at any time by clicking with the mouse.\n"
        "3. Adjust the game speed using the slider.\n"
        "4. Click the \"Save\" option in the menu to save the current cell state to a file.\n"
        "5. To exit the game, use the \"Exit\" option in the menu.\n";

    // Display the help message to the user
    QMessageBox::information(this, "Help", helpMessage);
}

/* Return the current board */
GameBoard& GameOfLife::getBoard() {
    return *gameBoard;
}

/* Deconstructor */
GameOfLife::~GameOfLife() {
    delete gameBoard;
    delete gameRule;
}

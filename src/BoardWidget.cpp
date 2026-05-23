#include "BoardWidget.h"
#include "GameBoard.h"

/* Constructor for BoardWidget */
BoardWidget::BoardWidget(QWidget* parent, GameBoard* newBoard) 
	: QWidget(parent), 
	  board(newBoard) {};

/* Destructor for BoardWidget */
BoardWidget::~BoardWidget() {}

/* Set the board */
void BoardWidget::setBoard(GameBoard* newBoard) {
	board = newBoard;
	update(); //request a redraw
}

/* Paint event to draw the board */
void BoardWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	// Guard against empty board data
	if (board->getBoardData().empty() || board->getBoardData()[0].empty()) {
		return;
	}

	// Calculate the size of cell
	int boardWidth = board->getBoardData()[0].size();
	int boardHeight = board->getBoardData().size();
	int cellWidth = width() / boardWidth;
	int cellHeight = height() / boardHeight;

	// Draw each cell in the board
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			QRect cell(j * cellWidth, i * cellHeight, cellWidth, cellHeight);
			if (board->getCellStatus(i, j) == 1) {
				painter.fillRect(cell, Qt::black); // Alive cell
			}
			else {
				painter.fillRect(cell, Qt::white); // Dead cell
			}
			painter.drawRect(cell);
		}
	}
}

/* Handle mouse clicks to toggle cell state */
void BoardWidget::mousePressEvent(QMouseEvent* event) {
	// calculate the size of cell
	int boardWidth = board->getBoardData()[0].size();
	int boardHeight = board->getBoardData().size();
	int cellWidth = width() / boardWidth;
	int cellHeight = height() / boardHeight;

	// get mouse position
	QPointF pos = event->position();
	int y = pos.x() / cellWidth;
	int x = pos.y() / cellHeight;

	//change the status of clicked cell
	if (x >= 0 && x < boardHeight && y >= 0 && y < boardWidth) {
		board->setCell(x, y, 1 - board->getCellStatus(x,y));
		update();
	}
}

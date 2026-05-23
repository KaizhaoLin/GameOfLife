#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class GameBoard;

/* Custom widget to display the game board */ 
class BoardWidget : public QWidget {
	Q_OBJECT

public:
	BoardWidget(QWidget* parent, GameBoard* newBoard);
	~BoardWidget();

	/* Set the game board for this widget */ 
	void setBoard(GameBoard* newBoard);

protected:
	// Event overrides for painting and mouse interactions
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	/* The associated game board */
	GameBoard* board;
};

#endif

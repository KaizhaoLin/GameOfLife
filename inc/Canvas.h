#ifndef CANVAS_H
#define CANVAS_H

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QDialogButtonBox>

#include "ui_Canvas.h"

class GameBoard;
class BoardWidget;

/* Dialog for the drawing canvas */
class Canvas : public QDialog {
	Q_OBJECT

public:
	Canvas(GameBoard* board, QWidget* parent = nullptr);
	~Canvas();

private slots:
	/* Slots for OK button action */
	void onClicked();
	/* Slots for Cancel button action */
	void onCanceled();

signals:
	// Signals emitted on canvas events 
	void finishDrawing();
	void backToPrevPage();

private:
	Ui::Canvas ui; // UI elements for the dialog


	GameBoard* gameBoard;

	QWidget* container; // Container for the board

	BoardWidget* boardWidget;

	QDialogButtonBox* confirmDrawingButtonBox; // Button box for actions
};

#endif

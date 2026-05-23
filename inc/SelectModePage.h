#ifndef SELECTMODEPAGE_H
#define SELECTMODEPAGE_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtWidgets/QMessageBox>
#include "ui_SelectModePage.h"

class GameBoard;

/* Dialog for choosing the game mode */
class SelectModePage : public QDialog {
	Q_OBJECT

public:
	SelectModePage(GameBoard* board, QWidget* parent = nullptr);
	~SelectModePage();

private slots:
	/* Slot triggered when draw mode is selected */
	void DrawModeSelected();

	/* Slot triggered when template mode is selected */
	void TemplateModeSelected();

	/* Slot triggered when file mode is selected */
	void FileModeSelected();

	/* Show tips */
	void ShowTips();

signals:
	/* signal for opening the canvas page */
	void openCanvas();

	/* signal for opening the template page */
	void openTemplatePage();

	/* signal indicating a valid file is chosen */
	void fileChosen();

private:
	Ui::SelectModePage ui;

	// Buttons for selecting different modes
	QPushButton* DrawModeButton;
	QPushButton* TemplateModeButton;
	QPushButton* FileModeButton;
	QPushButton* HelpButton;

	GameBoard* gameBoard; // The relevant board
};


#endif

#ifndef TEMPLATEPAGE_H
#define TEMPLATEPAGE_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDialogButtonBox>
#include "ui_TemplatePage.h"

class GameBoard;

/* TemplatePage allows the user to select predefined board */
class TemplatePage : public QDialog {
	Q_OBJECT

public:
	TemplatePage(GameBoard* gameBoard, QWidget* parent = nullptr);
	~TemplatePage();

private slots:
	// Slots to set specific templates for the board
	/* Set the Glider Gun template */
	void GliderGunSelected();

	/* Set the Copperhead template */
	void CopperheadSelected();

	/* Set the Loop template */
	void LoopSelected();


	// Handle confirmation and cancellation actions
	void onClicked();
	void onCanceled();

signals:
	/* Signal indicating a template is selected */
	void finishGenerating();
	/* Signal indicating selection is cancelled */
	void backToPrevPage();

private:
	Ui::TemplatePage ui;

	// Template selection radio buttons
	QRadioButton* GliderGunSelection;
	QRadioButton* CopperheadSelection;
	QRadioButton* LoopSelection;

	// Button for confirming or canceling changes
	QDialogButtonBox* ConfirmationButtonBox;

	// Relevant game board
	GameBoard* board;
};

#endif

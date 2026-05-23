#include "TemplatePage.h"
#include "GameBoard.h"

/* Constructor */
TemplatePage::TemplatePage(GameBoard* gameBoard, QWidget* parent) 
	: QDialog(parent),
	  board(gameBoard){

	ui.setupUi(this);

	// Find the related components in the ui file
	GliderGunSelection = findChild<QRadioButton*>("GliderGunSelection");
	CopperheadSelection = findChild<QRadioButton*>("CopperheadSelection");
	LoopSelection = findChild<QRadioButton*>("LoopSelection");
	ConfirmationButtonBox = findChild<QDialogButtonBox*>("ConfirmationButtonBox");

	// Set the Glider Gun template as the default selection
	GliderGunSelection->setChecked(true);

	// Connect confirmation and cancellation actions
	connect(ConfirmationButtonBox, &QDialogButtonBox::accepted, this, &TemplatePage::onClicked);
	connect(ConfirmationButtonBox, &QDialogButtonBox::rejected, this, &TemplatePage::backToPrevPage);
	
}

/* Deconstructor */
TemplatePage::~TemplatePage() {}

/* Sets the Glider Gun template */
void TemplatePage::GliderGunSelected() {
	vector<vector<int>> gliderGunBoard = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	// Apply the template to the game board
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 36; j++) {
			board->setCell(i + 12, j + 8, gliderGunBoard[i][j]);
		}
	}
}

/* Sets the Copperhead template */
void TemplatePage::CopperheadSelected() {
	vector<vector<int>> copperheadBoard = {
		{ 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0 },
	};

	// Apply the template to the game board
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 12; j++) {
			board->setCell(i + 20, j + 20, copperheadBoard[i][j]);
		}
	}
}

/* Sets the Loop template */
void TemplatePage::LoopSelected() {
	vector<vector<int>> loopBoard = {
		{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 }
	};

	// Apply the template to the game board
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 10; j++) {
			board->setCell(i + 23, j + 20, loopBoard[i][j]);
		}
	}
}

/* Handle confirmation actions */
void TemplatePage::onClicked() {
	// Determine which template is selected
	if (GliderGunSelection->isChecked()) {
		GliderGunSelected();
	}
	else if (CopperheadSelection->isChecked()) {
		CopperheadSelected();
	}
	else if (LoopSelection->isChecked()) {
		LoopSelected();
	}

	// Emit signal and close the dialog
	finishGenerating();
	accept();
}

/* Handle cancellation actions */
void TemplatePage::onCanceled() {
	// Emit signal and reject the dialog
	backToPrevPage();
	reject();
}

#include "Canvas.h"
#include "GameBoard.h"
#include "BoardWidget.h"

const int COL = 50;
const int ROW = 50;

/* Constructor for Canvas */
Canvas::Canvas(GameBoard* board, QWidget* parent) 
	: QDialog(parent) {
	
	ui.setupUi(this); // Initialize the UI

	gameBoard = board;

	// Find widgets in ui
	container = findChild<QWidget*>("BoardWidget");
	confirmDrawingButtonBox = findChild<QDialogButtonBox*>("ConfirmDrawingButtonBox");

	// Create board within the container
	boardWidget = new BoardWidget(container, gameBoard);
	
	// Display the board
	QVBoxLayout* layout = new QVBoxLayout(container);
	layout->addWidget(boardWidget);
	container->setLayout(layout);

	// Connect button actions to respective slots
	connect(confirmDrawingButtonBox, &QDialogButtonBox::accepted, this, &Canvas::onClicked);
	connect(confirmDrawingButtonBox, &QDialogButtonBox::rejected, this, &Canvas::onCanceled);

}

/* Destructor for Canvas */
Canvas::~Canvas() {}

/* Slot called when OK button is clicked */
void Canvas::onClicked() {
	finishDrawing(); // emit signal to indicate drawing is completed
	accept(); // close the dialog
}

/* Slot called when Cancel button is clicked */
void Canvas::onCanceled() {
	backToPrevPage(); // emit signal to go back
	gameBoard->clear(); // clear the board
	reject(); // close the dialog
}

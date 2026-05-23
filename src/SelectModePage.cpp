#include "SelectModePage.h"
#include "GameBoard.h"

/* Constructor */
SelectModePage::SelectModePage(GameBoard* board, QWidget* parent)
	: QDialog(parent) {

	ui.setupUi(this);

	gameBoard = board; // Initialize the board

	// Find the related components in the ui file
	DrawModeButton = findChild<QPushButton*>("DrawModeButton");
	TemplateModeButton = findChild<QPushButton*>("TemplateModeButton");
	FileModeButton = findChild<QPushButton*>("FileModeButton");
	HelpButton = findChild<QPushButton*>("HelpButton");

	// Connect buttons to their respective slots
	connect(DrawModeButton, &QPushButton::clicked, this, &SelectModePage::DrawModeSelected);
	connect(TemplateModeButton, &QPushButton::clicked, this, &SelectModePage::TemplateModeSelected);
	connect(FileModeButton, &QPushButton::clicked, this, &SelectModePage::FileModeSelected);
	connect(HelpButton, &QPushButton::clicked, this, &SelectModePage::ShowTips);
}

/* Deconstructor */
SelectModePage::~SelectModePage() {}

/* Slot triggered when draw mode is selected */
void SelectModePage::DrawModeSelected() {
	openCanvas();
}

/* Slot triggered when template mode is selected */
void SelectModePage::TemplateModeSelected() {
	openTemplatePage();
}

/* Slot triggered when file mode is selected */
void SelectModePage::FileModeSelected() {

	// Open a file dialog to select a CSV file
	QString filePath = QFileDialog::getOpenFileName(
		this,
		"Select file",
		"",
		"csv Files (*.csv)"
	);
	if (!filePath.isEmpty()) {
		QFile file(filePath);
		// Attempt to open the file
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::critical(this, tr("Error"), tr("Failed to open file for reading."));
			return;
		}

		// Read the file line by line
		QTextStream in(&file);
		QString line;
		int i = 0;

		while (!in.atEnd() && i < 50) {
			line = in.readLine();
			QStringList fields = line.split(",");
			// Read the board status from the file
			for (int j = 0; j < fields.size() && j < 50; j++) {
				gameBoard->setCell(i, j, fields[j].toInt());
			}
			i++;
		}

		file.close();
		// Emit signal to indicate a valid file is chosen
		fileChosen();
	}
	else {
		// No file is chosen
		QMessageBox::warning(this, "Warning", "You did not choose any file!");
	}
}

/* Show tips */
void SelectModePage::ShowTips() {
	QString helpMessage =
		"Welcome to Game of Life!\n\n"
		"Choose a mode to generate the board:\n"
		"- Draw Mode: Manually draw the cell states on the board.\n"
		"- Template Mode: Select predefined cell states.\n"
		"- File Mode: Load board from a CSV file.\n";

	// Display the help message to the user
	QMessageBox::information(this, "Help", helpMessage);
	
}

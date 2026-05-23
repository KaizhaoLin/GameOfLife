#include "SettingWindow.h"
#include "GameRule.h"

/* Constructor */
SettingWindow::SettingWindow(QWidget* parent, GameRule* rule) 
	: QDialog(parent), 
	  minAlive(2),
	  maxAlive(3),
	  minReproduce(3),
	  maxReproduce(3),
	  gameRule(rule) {

	ui.setupUi(this);

	// Find the related components in the ui file
	MinAliveSpinBox = findChild<QSpinBox*>("MinAliveSpinBox");
	MaxAliveSpinBox = findChild<QSpinBox*>("MaxAliveSpinBox");
	MinReproduceSpinBox = findChild<QSpinBox*>("MinReproduceSpinBox");
	MaxReproduceSpinBox = findChild<QSpinBox*>("MaxReproduceSpinBox");
	SettingPageButtonBox = findChild<QDialogButtonBox*>("SettingPageButtonBox");

	// Set ranges for spin boxes
	MinAliveSpinBox->setRange(0, 8);
	MaxAliveSpinBox->setRange(0, 8);
	MinReproduceSpinBox->setRange(0, 8);
	MaxReproduceSpinBox->setRange(0, 8);

	// Set default values for spin boxes
	MinAliveSpinBox->setValue(2);
	MaxAliveSpinBox->setValue(3);
	MinReproduceSpinBox->setValue(3);
	MaxReproduceSpinBox->setValue(3);

	// Connect spin boxes to their respective slots
	connect(MinAliveSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::getMinAliveFromSpinBox);
	connect(MaxAliveSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::getMaxAliveFromSpinBox);
	connect(MinReproduceSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::getMinReproduceFromSpinBox);
	connect(MaxReproduceSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::getMaxReproduceFromSpinBox);

	// Make sure max >= min
	connect(MinAliveSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::adjustMinAliveValue);
	connect(MaxAliveSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::adjustMaxAliveValue);
	connect(MinReproduceSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::adjustMinReproduceValue);
	connect(MaxReproduceSpinBox, &QSpinBox::valueChanged, this, &SettingWindow::adjustMaxReproduceValue);

	// Connect dialog buttons to apply or cancel actions
	connect(SettingPageButtonBox, &QDialogButtonBox::accepted, this, &SettingWindow::applySettings);
}

/* Deconstructor */
SettingWindow::~SettingWindow() {} 


// Getters for the survival and reproduction value
/* Get minAlive value from relevant spin box */
void SettingWindow::getMinAliveFromSpinBox(int value) {
	minAlive = value;
}

/* Get minAlive value from relevant spin box */
void SettingWindow::getMaxAliveFromSpinBox(int value) {
	maxAlive = value;
}

/* Get minAlive value from relevant spin box */
void SettingWindow::getMinReproduceFromSpinBox(int value) {
	minReproduce = value;
}

/* Get minAlive value from relevant spin box */
void SettingWindow::getMaxReproduceFromSpinBox(int value) {
	maxReproduce = value;
}


// Adjust spin box constraints dynamically
/* Make sure minAlive <= maxAlive */
void SettingWindow::adjustMinAliveValue(int value) {
	if (MaxAliveSpinBox->value() < value) {
		MaxAliveSpinBox->setValue(value);
	}
}

/* Make sure maxAlive >= minAlive */
void SettingWindow::adjustMaxAliveValue(int value) {
	if (MinAliveSpinBox->value() > value) {
		MinAliveSpinBox->setValue(value);
	}
}

/* Make sure minReproduce <= maxReproduce */
void SettingWindow::adjustMinReproduceValue(int value) {
	if (MaxReproduceSpinBox->value() < value) {
		MaxReproduceSpinBox->setValue(value);
	}
}

/* Make sure maxReproduce >= minReproduce */
void SettingWindow::adjustMaxReproduceValue(int value) {
	if (MinReproduceSpinBox->value() > value) {
		MinReproduceSpinBox->setValue(value);
	}
}

/* Apply the current settings and updates the game rule */
void SettingWindow::applySettings() {
	gameRule->setSurviveRule(minAlive, maxAlive, minReproduce, maxReproduce);
	this->accept(); // close the dialog
}
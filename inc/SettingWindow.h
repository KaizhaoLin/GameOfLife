#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDialogButtonBox>
#include "ui_SettingPage.h"

class GameRule;

/* SettingWindow allows the user to adjust game rules interactively */
class SettingWindow : public QDialog {
	Q_OBJECT

public:
	SettingWindow(QWidget* parent, GameRule* gameRule);
	~SettingWindow();

private slots:
	// Slots to update game rules from spin box values
	void getMinAliveFromSpinBox(int value);
	void getMaxAliveFromSpinBox(int value);
	void getMinReproduceFromSpinBox(int value);
	void getMaxReproduceFromSpinBox(int value);

	// Slots to adjust spin box constraints dynamically
	/* Make sure minAlive <= maxAlive */
	void adjustMinAliveValue(int value);

	/* Make sure maxAlive >= minAlive */
	void adjustMaxAliveValue(int value);

	/* Make sure minReproduce <= maxReproduce */
	void adjustMinReproduceValue(int value);

	/* Make sure maxReproduce >= minReproduce */
	void adjustMaxReproduceValue(int value);


	/* Apply the current settings and updates the game rule */
	void applySettings();

private:
	Ui::SettingWindowClass ui;

	GameRule* gameRule; // Relevant game rule

	// Spin boxes for rule adjustments
	QSpinBox* MinAliveSpinBox;
	QSpinBox* MaxAliveSpinBox;
	QSpinBox* MinReproduceSpinBox;
	QSpinBox* MaxReproduceSpinBox;

	// Buttons for confirming or canceling changes
	QDialogButtonBox* SettingPageButtonBox;

	// Rule variables for survival and reproduction
	int minAlive;
	int maxAlive;
	int minReproduce;
	int maxReproduce;
};

#endif

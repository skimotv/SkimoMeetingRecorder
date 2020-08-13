#pragma once

#include <memory>
#include <QDialog>

#include "ui_SkimoAbout.h"

class SkimoAbout : public QDialog {
	Q_OBJECT

public:
	explicit SkimoAbout(QWidget *parent = 0);

	std::unique_ptr<Ui::SkimoAbout> ui;

private slots:
	void ShowAbout();
	void ShowAuthors();
	void ShowLicense();
};

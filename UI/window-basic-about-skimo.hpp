#pragma once

#include <memory>
#include <QDialog>
#include <QPointer>

#include "ui_SkimoAbout.h"
#include "window-basic-about.hpp"

class SkimoAbout : public QDialog {
	Q_OBJECT

public:
	explicit SkimoAbout(QWidget *parent = 0);

	std::unique_ptr<Ui::SkimoAbout> ui;

private slots:
	void ShowAbout();
	void ShowAuthors();
	void ShowLicense();
	void on_aboutOBS_clicked();

private:
	QPointer<OBSAbout> about;
};

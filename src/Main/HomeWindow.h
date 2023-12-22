#pragma once
#include "ui_HomeWindow.h"
#include <QStackedWidget>

class HomeWindow : public QWidget
{
public:
	HomeWindow(QStackedWidget* parent = nullptr);
	~HomeWindow();

	void reset_window();
	
public slots:
	void onGoButton();

private:
	Ui_Home* ui;
	QStackedWidget* stack;
};


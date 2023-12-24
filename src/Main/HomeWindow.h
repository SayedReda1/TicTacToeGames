#pragma once
#include "ui_HomeWindow.h"
#include <QStackedWidget>
#include <QStatusBar>

class HomeWindow : public QWidget
{
public:
	HomeWindow(QStackedWidget* parent = nullptr);
	~HomeWindow();

	void reset_window();
	
public slots:
	void onGoButton();
	void onGameChange();
	void onModeChange();

private:
	Ui_Home* ui;
	QStackedWidget* stack;
};


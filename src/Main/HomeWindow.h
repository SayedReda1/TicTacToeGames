#pragma once
#include "ui_HomeWindow.h"
#include <QStackedWidget>


class HomeWindow : public QWidget
{
public:
	HomeWindow(QStackedWidget* parent = nullptr);
	~HomeWindow();

	void resetWindow();
	
	// Disablers
	void enable(QWidget*);
	void disable(QWidget*, const QString&);

public slots:
	void onGoButton();
	void onGameChange();
	void onModeChange();

private:
	Ui_Home* ui;
	QStackedWidget* stack;
};


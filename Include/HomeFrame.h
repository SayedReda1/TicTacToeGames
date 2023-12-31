#ifndef _MAIN_FRAME_H
#define _MAIN_FRAME_H

#include "ui_HomeFrame.h"
#include <QStackedWidget>

class HomeFrame : public QWidget
{
public:
	
	HomeFrame(QStackedWidget* parent = nullptr);
	~HomeFrame();

	void resetWindow();
	void enable(QWidget* widget);
	void disable(QWidget* widget, const QString& style);


public slots:
	void onGoButton();
	void onGameChange();
	void onModeChange();

private:
	Ui_Home* ui;
	QStackedWidget* stack;
};

#endif

#ifndef _RESULT_FRAME_H
#define _RESULT_FRAME_H

#include "ui_ResultFrame.h"
#include <QStackedWidget>

class ResultFrame : public QWidget
{
public:
	ResultFrame(const QString& msg, bool status, QStackedWidget* parent);

public slots:
	void onBackButton();
	void onHomeButtonClick();

private:
	QStackedWidget* stack;
	Ui_Widget* ui;
};

#endif
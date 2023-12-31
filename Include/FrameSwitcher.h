#ifndef _WINDOW_SWITCHER_H
#define _WINDOW_SWITCHER_H

#include <QStackedWidget>

class FrameSwitcher : public QStackedWidget
{
public:
    FrameSwitcher(QStackedWidget* parent = nullptr);
	~FrameSwitcher();

public slots:
	void onCurrentChange();
};

#endif

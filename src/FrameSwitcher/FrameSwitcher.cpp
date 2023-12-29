#include "FrameSwitcher.h"
#include <QPropertyAnimation>


FrameSwitcher::FrameSwitcher(QStackedWidget* parent)
	: QStackedWidget(parent)
{
	connect(this, &QStackedWidget::currentChanged, this, &FrameSwitcher::onCurrentChange);
}

FrameSwitcher::~FrameSwitcher()
{
	QWidget* widget = this->widget(0);
	this->removeWidget(widget);

	delete widget;
}

////////////// SLOTS /////////////////////
void FrameSwitcher::onCurrentChange()
{
	int currentCount = this->count();

	for (int i = currentIndex() + 1; i < currentCount; ++i)
	{
		QWidget* widget = this->widget(i);
		
		if (widget != nullptr)
		{
			this->removeWidget(widget);
			delete widget;
		}
	}
}
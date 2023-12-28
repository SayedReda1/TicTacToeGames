#include "FrameSwitcher.h"


FrameSwitcher::FrameSwitcher(QStackedWidget* parent)
	: QStackedWidget(parent)
{
	connect(this, &QStackedWidget::currentChanged, this, &FrameSwitcher::onCurrentChange);
}

void FrameSwitcher::onCurrentChange()
{
	int currentCount = this->count();

	for (int i = currentIndex() + 1; i < currentCount; ++i)
	{
		QWidget* widget = this->widget(i);
		this->removeWidget(widget);

		delete widget;
	}
}
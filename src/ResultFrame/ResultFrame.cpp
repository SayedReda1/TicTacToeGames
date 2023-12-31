#include "ResultFrame.h"

ResultFrame::ResultFrame(const QString& msg, bool status, QStackedWidget* parent)
	: QWidget(parent), stack(parent), ui(new Ui_Widget)
{
	ui->setupUi(this);
	
	ui->label->setText(msg);

	if (status)
	{
		// Play Win sound
		PlaySound(TEXT("media/win.wav"), NULL, SND_ASYNC);

		ui->mainFrame->setStyleSheet(
			"QFrame { background-color: #005B41; border-radius: 10px;  color: white; }"
		);

		ui->buttonsFrame->setStyleSheet(
			"QPushButton { background-color: #005B41; border-radius: 10px; }\nQPushButton::hover { background-color: #008170; }\n"
		);
	}
	else
	{
		// Play tie sound
		PlaySound(TEXT("media/tie.wav"), NULL, SND_ASYNC);

		ui->mainFrame->setStyleSheet(
			"QFrame { background-color: #526D82; border-radius: 10px;  color: white; }"
		);

		ui->buttonsFrame->setStyleSheet(
			"QPushButton { background-color: #526D82; border-radius: 10px; }\nQPushButton::hover { background-color: #9DB2BF; }\n"
		);
	}

	connect(ui->backButton, &QPushButton::clicked, this, &ResultFrame::onBackButton);
	connect(ui->homeButton, &QPushButton::clicked, this, &ResultFrame::onHomeButtonClick);
}

void ResultFrame::onBackButton()
{
	stack->setCurrentIndex(1);
}

void ResultFrame::onHomeButtonClick()
{
	stack->setCurrentIndex(0);
}



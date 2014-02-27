#include "StartWindow.h"
#include <QtGui/QDesktopWidget>

StartWindow::StartWindow(void) :
	QDialog(NULL),
	first_time_show(true)
{
	ui.setupUi(this);
}

void StartWindow::showEvent(QShowEvent* event) {
	(void)event;

	if (first_time_show) {
		move(
			QApplication::desktop()->availableGeometry().center()
			- rect().center()
		);
		first_time_show = false;
	}
}

void StartWindow::on_nickname_editor_textEdited(const QString& text) {
	ui.login_button->setEnabled(!text.isEmpty());
}

void StartWindow::on_login_button_clicked(void) {
	hide();
	emit login(ui.nickname_editor->text());
}

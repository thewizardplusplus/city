#include "StartWindow.h"
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QDesktopWidget>
#else
	#include <QtGui/QDesktopWidget>
#endif

StartWindow::StartWindow(void) :
	QDialog(NULL),
	first_time_show(true)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
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

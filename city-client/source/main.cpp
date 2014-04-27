#include "MainWindow.h"
#include <QtCore/QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QApplication>
#else
	#include <QtGui/QApplication>
#endif

int main(int arguments_number, char* arguments[]) {
	QApplication application(arguments_number, arguments);

	MainWindow main_window;
	main_window.show();

	int exit_code = application.exec();
	return exit_code;
}

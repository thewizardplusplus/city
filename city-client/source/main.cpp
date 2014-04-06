#include "MainWindow.h"
#include <QtGui/QApplication>

int main(int arguments_number, char* arguments[]) {
	QApplication application(arguments_number, arguments);

	MainWindow main_window;
	main_window.show();

	int exit_code = application.exec();
	return exit_code;
}

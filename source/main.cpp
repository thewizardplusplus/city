#include "MainWindow.h"
#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>

int main(int arguments_number, char* arguments[]) {
	QApplication application(arguments_number, arguments);

	QTranslator translator;
	translator.load(
		"qt_ru",
		QLibraryInfo::location(QLibraryInfo::TranslationsPath)
	);
	application.installTranslator(&translator);

	MainWindow main_window;
	main_window.show();

	int exit_code = application.exec();
	return exit_code;
}

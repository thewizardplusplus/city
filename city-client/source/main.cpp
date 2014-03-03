#include "StartWindow.h"
#include "MainWindow.h"
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QApplication>
#else
	#include <QtGui/QApplication>
#endif
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

	StartWindow start_window;
	MainWindow main_window;
	QObject::connect(
		&start_window,
		SIGNAL(login(QString)),
		&main_window,
		SLOT(start(QString))
	);

	start_window.show();

	int exit_code = application.exec();
	return exit_code;
}

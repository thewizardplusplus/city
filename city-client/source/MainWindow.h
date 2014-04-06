#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(void);

private:
	void createUi(void);
};
#endif

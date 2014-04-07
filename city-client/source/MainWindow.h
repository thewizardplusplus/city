#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(void);
	virtual bool eventFilter(QObject* watched_object, QEvent* event);

private:
	QGraphicsScene* graphics_scene;

	void createUi(void);
	void loadLevel(void);
};
#endif

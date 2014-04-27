#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MoveDirection.h"
#include "DynamicSprite.h"
#include "Client.h"
#include <QtCore/QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QMainWindow>
	#include <QtWidgets/QGraphicsScene>
#else
	#include <QtGui/QMainWindow>
	#include <QtGui/QGraphicsScene>
#endif
#include <QtCore/QThread>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(void);
	virtual ~MainWindow(void);
	virtual bool eventFilter(QObject* watched_object, QEvent* event);

signals:
	void move(MoveDirection::Types direction);

public slots:
	void updateLevel(const QString& description);

private:
	static const size_t INVALID_ID = -1;

	QGraphicsScene* graphics_scene;
	QGraphicsItemGroup* root_item;
	Client* client;
	QThread client_thread;
	QMap<size_t, DynamicSprite*> castles;
	size_t player_id;
	QMap<size_t, DynamicSprite*> players;
	QMap<size_t, DynamicSprite*> skeletons;

	void createUi(void);
	void loadLevel(void);
	void start(void);
};
#endif

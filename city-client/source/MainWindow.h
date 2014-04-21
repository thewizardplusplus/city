#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MoveDirection.h"
#include "DynamicSprite.h"
#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(void);
	virtual bool eventFilter(QObject* watched_object, QEvent* event);

signals:
	void move(MoveDirection::Types direction);

public slots:
	void updateLevel(const QString& description);

private:
	static const size_t INVALID_ID = -1;

	QGraphicsScene* graphics_scene;
	QGraphicsItemGroup* root_item;
	QMap<size_t, DynamicSprite*> castles;
	size_t player_id;
	QMap<size_t, DynamicSprite*> players;

	void createUi(void);
	void loadLevel(void);
};
#endif

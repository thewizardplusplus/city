#include "MainWindow.h"
#include "GraphicsScene.h"
#include <QtGui/QKeyEvent>
#include <QtGui/QGridLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QApplication>
#include <QtCore/QFile>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtGui/QGraphicsPixmapItem>

MainWindow::MainWindow(void) :
	graphics_scene(NULL),
	root_item(NULL)
{
	setWindowTitle("2D RTS");

	QSize size(12 * 75, 8 * 75);
	setMinimumSize(size);
	setMaximumSize(size);

	createUi();
	loadLevel();
}

bool MainWindow::eventFilter(QObject* watched_object, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		switch (key_event->key()) {
			case Qt::Key_Left:
				root_item->setPos(root_item->pos() + QPointF(75.0f, 0.0f));
				break;
			case Qt::Key_Right:
				root_item->setPos(root_item->pos() + QPointF(-75.0f, 0.0f));
				break;
			case Qt::Key_Up:
				root_item->setPos(root_item->pos() + QPointF(0.0f, 75.0f));
				break;
			case Qt::Key_Down:
				root_item->setPos(root_item->pos() + QPointF(0.0f, -75.0f));
				break;
		}

		return true;
	} else {
		return QMainWindow::eventFilter(watched_object, event);
	}
}

void MainWindow::createUi(void) {
	QWidget* central_widget = new QWidget(this);
	setCentralWidget(central_widget);

	QGridLayout* central_widget_layout = new QGridLayout(central_widget);
	central_widget_layout->setContentsMargins(0, 0, 0, 0);

	QGraphicsView* graphics_view = new QGraphicsView(central_widget);
	graphics_view->installEventFilter(this);
	graphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphics_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphics_view->setRenderHint(QPainter::SmoothPixmapTransform, true);
	central_widget_layout->addWidget(graphics_view, 0, 0);

	graphics_scene = new GraphicsScene(graphics_view);
	graphics_view->setScene(graphics_scene);
}

void MainWindow::loadLevel(void) {
	QFile level_file(":/level.lvl");
	if (!level_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::critical(
			NULL,
			trUtf8("Ошибка!"),
			trUtf8("Не удалось загрузить файл уровня.")
		);
		std::exit(EXIT_FAILURE);
	}

	root_item = new QGraphicsItemGroup();
	graphics_scene->addItem(root_item);

	QString level_description = level_file.readAll();
	QStringList lines = level_description.split('\n');
	QRegExp pattern(
		"(0|[1-9]\\d*) (tree|mountain|castle) (0|[1-9]\\d*) (0|[1-9]\\d*)"
	);
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].isEmpty()) {
			continue;
		}

		int matched = pattern.indexIn(lines[i]);
		if (matched == -1) {
			qDebug()
				<< QString("Warning! Invalid line %1 in level file.")
					.arg(i + 1);
			continue;
		}

		QString entity_type = pattern.cap(2);
		QGraphicsItem* graphics_item = NULL;
		if (entity_type == "tree") {
			graphics_item = graphics_scene->addPixmap(QPixmap(":/tree.png"));
		} else if (entity_type == "mountain") {
			graphics_item = graphics_scene->addPixmap(
				QPixmap(":/mountain.png")
			);
		} else if (entity_type == "castle") {
			graphics_item = graphics_scene->addPixmap(
				QPixmap(":/grey_castle.png")
			);
		} else {
			qDebug()
				<< QString(
					"Warning! Invalid entity type \"%1\" on line %2 in level "
					"file."
				).arg(entity_type).arg(i + 1);
			continue;
		}

		root_item->addToGroup(graphics_item);
		graphics_item->setPos(
			75 * pattern.cap(3).toInt(),
			75 * pattern.cap(4).toInt()
		);
	}
}

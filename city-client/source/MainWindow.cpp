#include "MainWindow.h"
#include "GraphicsScene.h"
#include "DynamicSprite.h"
#include <QtGui/QKeyEvent>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QGridLayout>
	#include <QtWidgets/QGraphicsView>
	#include <QtWidgets/QApplication>
	#include <QtWidgets/QMessageBox>
	#include <QtWidgets/QGraphicsPixmapItem>
#else
	#include <QtGui/QGridLayout>
	#include <QtGui/QGraphicsView>
	#include <QtGui/QApplication>
	#include <QtGui/QMessageBox>
	#include <QtGui/QGraphicsPixmapItem>
#endif

MainWindow::MainWindow(void) :
	graphics_scene(NULL),
	root_item(NULL),
	player_id(INVALID_ID)
{
	setWindowTitle("2D RTS");

	QSize size(12 * 75, 8 * 75);
	setMinimumSize(size);
	setMaximumSize(size);

	createUi();
	loadLevel();

	start();
}

MainWindow::~MainWindow(void) {
	client_thread.exit();
	client_thread.wait(1000);
}

bool MainWindow::eventFilter(QObject* watched_object, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		switch (key_event->key()) {
			case Qt::Key_Left:
				emit move(MoveDirection::LEFT);
				break;
			case Qt::Key_Right:
				emit move(MoveDirection::RIGHT);
				break;
			case Qt::Key_Up:
				emit move(MoveDirection::UP);
				break;
			case Qt::Key_Down:
				emit move(MoveDirection::DOWN);
				break;
			case Qt::Key_Escape:
				QApplication::quit();
				break;
		}

		return true;
	} else {
		return QMainWindow::eventFilter(watched_object, event);
	}
}

void MainWindow::updateLevel(const QString& description) {
	foreach (size_t player_id, players.keys()) {
		delete players[player_id];
	}
	players.clear();
	foreach (size_t skeleton_id, skeletons.keys()) {
		delete skeletons[skeleton_id];
	}
	skeletons.clear();

	QStringList entities_description = description.split(';');
	foreach (QString entity_description, entities_description) {
		QStringList entity_data = entity_description.split(':');
		if (entity_data[0] == "c") {
			size_t castle_id = entity_data[1].toULong();
			if (castles.contains(castle_id)) {
				castles[castle_id]->setParameter(entity_data[2].toULong());
				castles[castle_id]->setState(
					entity_data[3].toULong()
				);
			}
		} else if (entity_data[0] == "p") {
			size_t player_id = entity_data[1].toULong();
			players[player_id] = new DynamicSprite(
				QStringList() << "green_player" << "red_player"
			);
			players[player_id]->setParameter(entity_data[2].toULong());
			players[player_id]->setState(player_id != this->player_id);

			root_item->addToGroup(players[player_id]);
			players[player_id]->setPos(
				75 * entity_data[3].toFloat(),
				75 * entity_data[4].toFloat()
			);
			if (player_id == this->player_id) {
				root_item->setPos(
					QPointF(12 * 75, 8 * 75) / 2
					- players[player_id]->pos()
				);
			}
		} else if (entity_data[0] == "s") {
			size_t skeleton_id = entity_data[1].toULong();
			skeletons[skeleton_id] = new DynamicSprite(
				QStringList() << "skeleton"
			);
			skeletons[skeleton_id]->setParameter(entity_data[2].toULong());

			root_item->addToGroup(skeletons[skeleton_id]);
			skeletons[skeleton_id]->setPos(
				75 * entity_data[3].toFloat(),
				75 * entity_data[4].toFloat()
			);
		}
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
			size_t castle_id = pattern.cap(1).toULong();
			castles[castle_id] = new DynamicSprite(
				QStringList()
				<< "grey_castle"
				<< "green_castle"
				<< "red_castle"
			);
			graphics_item = castles[castle_id];
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

void MainWindow::start(void) {
	client = new Client();
	this->player_id = client->getPlayerId();
	client->moveToThread(&client_thread);
	connect(
		&client_thread,
		#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
			SIGNAL(finished()),
		#else
			SIGNAL(terminated()),
		#endif
		client,
		SLOT(deleteLater())
	);
	qRegisterMetaType<MoveDirection::Types>("MoveDirection::Types");
	connect(
		this,
		SIGNAL(move(MoveDirection::Types)),
		client,
		SLOT(move(MoveDirection::Types))
	);
	connect(
		client,
		SIGNAL(updateLevel(QString)),
		this,
		SLOT(updateLevel(QString))
	);
	client_thread.start();
}

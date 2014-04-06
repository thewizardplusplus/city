#include "MainWindow.h"
#include <QtGui/QGridLayout>
#include <QtGui/QGraphicsView>

MainWindow::MainWindow(void) {
	setWindowTitle("2D RTS");
	createUi();
}

void MainWindow::createUi(void) {
	QWidget* central_widget = new QWidget(this);
	setCentralWidget(central_widget);

	QGridLayout* central_widget_layout = new QGridLayout(central_widget);
	central_widget_layout->setContentsMargins(0, 0, 0, 0);

	QGraphicsView* graphics_view = new QGraphicsView(central_widget);
	graphics_view->setBackgroundBrush(QColor(0x22, 0x8b, 0x22));
	central_widget_layout->addWidget(graphics_view, 0, 0);

	QGraphicsScene* graphics_scene = new QGraphicsScene(graphics_view);
	graphics_view->setScene(graphics_scene);
}

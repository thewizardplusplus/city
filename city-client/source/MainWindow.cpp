#include "MainWindow.h"
#include "GraphicsScene.h"
#include <QtGui/QGridLayout>
#include <QtGui/QGraphicsView>

MainWindow::MainWindow(void) {
	setWindowTitle("2D RTS");

	QSize size(12 * 75, 8 * 75);
	setMinimumSize(size);
	setMaximumSize(size);

	createUi();
}

void MainWindow::createUi(void) {
	QWidget* central_widget = new QWidget(this);
	setCentralWidget(central_widget);

	QGridLayout* central_widget_layout = new QGridLayout(central_widget);
	central_widget_layout->setContentsMargins(0, 0, 0, 0);

	QGraphicsView* graphics_view = new QGraphicsView(central_widget);
	central_widget_layout->addWidget(graphics_view, 0, 0);

	QGraphicsScene* graphics_scene = new GraphicsScene(graphics_view);
	graphics_view->setScene(graphics_scene);
}

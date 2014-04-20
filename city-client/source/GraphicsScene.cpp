#include "GraphicsScene.h"
#include <QtGui/QPainter>
#include <cmath>

GraphicsScene::GraphicsScene(QObject* parent) :
	QGraphicsScene(parent)
{}

void GraphicsScene::drawBackground(QPainter* painter, const QRectF& rectangle) {
	painter->fillRect(rectangle, QColor(0x22, 0x8b, 0x22));
}

void GraphicsScene::drawForeground(QPainter* painter, const QRectF& rectangle) {
	painter->save();
	painter->setPen(QPen(Qt::gray, 2));

	int y_start =
		rectangle.top()
		- std::abs(static_cast<int>(std::floor(rectangle.top())) % 75);
	for (int y = y_start; y < rectangle.bottom(); y += 75) {
		painter->drawLine(rectangle.left(), y, rectangle.right(), y);
	}

	int x_start =
		rectangle.left()
		- std::abs(static_cast<int>(std::floor(rectangle.left())) % 75);
	for (int x = x_start; x < rectangle.right(); x += 75) {
		painter->drawLine(x, rectangle.top(), x, rectangle.bottom());
	}

	painter->restore();
}

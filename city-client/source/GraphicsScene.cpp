#include "GraphicsScene.h"
#include <QtGui/QPainter>

GraphicsScene::GraphicsScene(QObject* parent) :
	QGraphicsScene(parent)
{}

void GraphicsScene::drawBackground(QPainter* painter, const QRectF& rectangle) {
	painter->fillRect(rectangle, QColor(0x22, 0x8b, 0x22));

	painter->save();
	painter->setPen(QPen(Qt::gray, 2));
	for (int y = rectangle.top(); y < rectangle.bottom(); y += 75) {
		painter->drawLine(rectangle.left(), y, rectangle.right(), y);
	}
	for (int x = rectangle.left(); x < rectangle.right(); x += 75) {
		painter->drawLine(x, rectangle.top(), x, rectangle.bottom());
	}
	painter->restore();
}

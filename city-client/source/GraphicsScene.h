#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QtGui/QGraphicsScene>

class GraphicsScene : public QGraphicsScene {
Q_OBJECT

public:
	explicit GraphicsScene(QObject* parent);

protected:
	virtual void drawBackground(QPainter* painter, const QRectF& rectangle);
	virtual void drawForeground(QPainter* painter, const QRectF& rectangle);
};
#endif

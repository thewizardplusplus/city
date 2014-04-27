#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QtCore/QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QGraphicsScene>
#else
	#include <QtGui/QGraphicsScene>
#endif

class GraphicsScene : public QGraphicsScene {
Q_OBJECT

public:
	explicit GraphicsScene(QObject* parent);

protected:
	virtual void drawBackground(QPainter* painter, const QRectF& rectangle);
	virtual void drawForeground(QPainter* painter, const QRectF& rectangle);
};
#endif

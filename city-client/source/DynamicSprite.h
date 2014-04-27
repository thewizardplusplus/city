#ifndef DYNAMICSPRITE_H
#define DYNAMICSPRITE_H

#include <QtCore/QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QGraphicsItemGroup>
#else
	#include <QtGui/QGraphicsItemGroup>
#endif

class DynamicSprite : public QGraphicsItemGroup {
public:
	explicit DynamicSprite(const QStringList& sprites_filenames);
	void setState(size_t state);
	void setParameter(size_t value);

private:
	QGraphicsTextItem* label;
	QList<QGraphicsItem*> graphics_items;
};
#endif

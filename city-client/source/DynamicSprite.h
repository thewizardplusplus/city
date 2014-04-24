#ifndef DYNAMICSPRITE_H
#define DYNAMICSPRITE_H

#include <QtGui/QGraphicsItemGroup>

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

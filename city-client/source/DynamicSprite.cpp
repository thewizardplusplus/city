#include "DynamicSprite.h"
#include <QtGui/QFont>

DynamicSprite::DynamicSprite(const QStringList& sprites_filenames) :
	label(NULL)
{
	QFont label_font;
	label_font.setStyleHint(QFont::Monospace);
	label_font.setBold(true);
	label_font.setPixelSize(75 / 4);

	label = new QGraphicsTextItem(this);
	label->setFont(label_font);
	label->setDefaultTextColor(Qt::white);
	addToGroup(label);

	setParameter(0);

	foreach (const QString& sprite, sprites_filenames) {
		QGraphicsItem* graphics_item = new QGraphicsPixmapItem(
			":/" + sprite + ".png",
			this
		);
		addToGroup(graphics_item);
		graphics_items << graphics_item;
	}

	setState(0);
}

void DynamicSprite::setState(size_t state) {
	for (size_t i = 0; i < static_cast<size_t>(graphics_items.size()); ++i) {
		graphics_items[i]->setVisible(i == state);
	}
}

void DynamicSprite::setParameter(size_t value) {
	label->setPlainText(QString::number(value));
}

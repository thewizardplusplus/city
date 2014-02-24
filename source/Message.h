#ifndef MESSAGE_H
#define MESSAGE_H

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QDateTime>

class Message {
public:
	typedef QList<Message> Group;

	QString nickname;
	QDateTime date;
	QString text;

	Message(
		const QString& nickname,
		const QDateTime& date,
		const QString& text
	);
};
#endif

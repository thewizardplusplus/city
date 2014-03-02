#ifndef MESSAGE_H
#define MESSAGE_H

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QDateTime>

class Message {
public:
	typedef QList<Message> Group;

	QString nickname;
	QDateTime time;
	QString text;

	Message(
		const QString& nickname,
		const QDateTime& time,
		const QString& text
	);
};
#endif

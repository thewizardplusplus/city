#include "Client.h"
#include <QtCore/QStringList>

Client::Client(
	const QString& host,
	const unsigned short port,
	const QString& nickname
) :
	connection(host, port),
	nickname(nickname)
{
	last_timestamp = QDateTime::currentDateTime();
	startTimer(0);
}

void Client::sendMessage(const QString& message) {
	connection.send(
		QString("%1:%2:%3")
			.arg(nickname)
			.arg(QDateTime::currentDateTime().toTime_t())
			.arg(message)
	);

	QString reply = connection.receive();
	if (reply.startsWith("error;")) {
		emit error(reply.mid(6));
	}
}

void Client::timerEvent(QTimerEvent* event) {
	(void)event;

	getInterlocutors();
	getMessages();
}

void Client::getInterlocutors(void) {
	connection.send(QString("%1:interlocutors").arg(nickname));

	QString reply = connection.receive();
	if (reply.startsWith("error;")) {
		emit error(reply.mid(6));
		return;
	}

	emit interlocutors(reply.split(';'));
}

void Client::getMessages(void) {
	connection.send(
		QString("%1:history:%2").arg(nickname).arg(last_timestamp.toTime_t())
	);

	QString reply = connection.receive();
	if (reply.startsWith("error;")) {
		emit error(reply.mid(6));
		return;
	}

	QStringList reply_parts = reply.split(';');
	Message::Group result;
	foreach (QString message, reply_parts) {
		QStringList message_parts = message.split(':');
		last_timestamp = QDateTime::fromTime_t(message_parts[1].toUInt());
		result.append(
			Message(message_parts[0], last_timestamp, message_parts[2])
		);
	}

	emit messages(result);
}

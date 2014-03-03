#include "Client.h"
#include <QtCore/QStringList>

Client::Client(
	const QString& host,
	const uint port,
	const QString& nickname
) :
	connection(host, port),
	nickname(nickname)
{
	last_time = QDateTime::currentDateTime();
	startTimer(1000);
}

void Client::sendMessage(const QString& message) {
	request(QString("%1;message;%2").arg(nickname).arg(message));
}

void Client::timerEvent(QTimerEvent* event) {
	(void)event;

	getInterlocutors();
	getMessages();
}

QString Client::request(const QString& message) {
	connection.send(message);

	QString reply = connection.receive();
	if (reply.startsWith("error;")) {
		emit error(reply.mid(6));
		return "";
	}

	return reply;
}

void Client::getInterlocutors(void) {
	QString reply = request(QString("%1;interlocutors").arg(nickname));
	if (!reply.isEmpty()) {
		emit interlocutors(reply.split(';'));
	}
}

void Client::getMessages(void) {
	QString reply = request(
		QString("%1;history;%2").arg(nickname).arg(last_time.toTime_t())
	);
	if (reply.isEmpty()) {
		return;
	}

	Message::Group result;
	QStringList reply_parts = reply.split(';');
	foreach (QString message, reply_parts) {
		QStringList message_parts = message.split(':');
		if (message_parts.size() != 3) {
			emit error("invalid message");
		}

		last_time = QDateTime::fromTime_t(message_parts[1].toUInt());
		result.append(
			Message(message_parts[0], last_time, message_parts[2])
		);
	}

	emit messages(result);
}

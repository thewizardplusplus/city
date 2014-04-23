#include "Client.h"

Client::Client(void) :
	player_id(INVALID_ID)
{
	player_id = QString::fromStdString(connection.request("r")).toULong();
	startTimer(100);
}

size_t Client::getPlayerId(void) const {
	return player_id;
}

void Client::move(MoveDirection::Types direction) {
	connection.request(
		QString("m:%1:%2").arg(player_id).arg(direction).toStdString()
	);
}

void Client::timerEvent(QTimerEvent* event) {
	(void)event;
	emit updateLevel(
		QString::fromStdString(
			connection.request(QString("w:%1").arg(player_id).toStdString())
		)
	);
}

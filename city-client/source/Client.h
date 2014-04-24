#ifndef CLIENT_H
#define CLIENT_H

#include "MoveDirection.h"
#include "Connection.h"
#include <QtCore/QObject>

class Client : public QObject {
Q_OBJECT

public:
	Client(void);
	size_t getPlayerId(void) const;

signals:
	void updateLevel(const QString& description);

public slots:
	void move(MoveDirection::Types direction);

protected:
	virtual void timerEvent(QTimerEvent* event);

private:
	static const size_t INVALID_ID = -1;

	Connection connection;
	size_t player_id;
};
#endif

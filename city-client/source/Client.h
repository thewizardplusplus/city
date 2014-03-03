#ifndef CLIENT_H
#define CLIENT_H

#include "Message.h"
#include "Connection.h"

class Client : public QObject {
Q_OBJECT

public:
	Client(
		const QString& host,
		const uint port,
		const QString& nickname
	);

signals:
	void error(const QString& message);
	void interlocutors(const QStringList& interlocutors);
	void messages(const Message::Group& messages);

public slots:
	void sendMessage(const QString& message);

protected:
	virtual void timerEvent(QTimerEvent* event);

private:
	Connection connection;
	QString nickname;
	QDateTime last_time;

	QString request(const QString& message);
	void getInterlocutors(void);
	void getMessages(void);
};
#endif

#ifndef CONNECTIONPRIVATE_H
#define CONNECTIONPRIVATE_H

#include <QtCore/QString>
#include <boost/asio.hpp>

class Connection {
public:
	Connection(const QString& host, const unsigned short port);
	void send(const QString& message);
	QString receive(void);

private:
	static const unsigned short LOCAL_PORT = 0;
	static const size_t MAXIMAL_REPLY_LENGTH = 1024;

	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint receiver_endpoint;

	boost::asio::ip::udp::endpoint resolve(
		const QString& host,
		const unsigned short port
	);
};
#endif

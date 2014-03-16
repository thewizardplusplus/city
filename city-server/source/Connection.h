#ifndef CONNECTIONPRIVATE_H
#define CONNECTIONPRIVATE_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class Connection {
public:
	Connection(const uint port);
	void send(const std::string& message);
	std::string receive(void);

private:
	static const size_t MAXIMAL_REPLY_LENGTH = 1024;

	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint receiver_endpoint;
};

typedef boost::shared_ptr<Connection> ConnectionSmartPointer;
#endif

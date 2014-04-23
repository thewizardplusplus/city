#ifndef CONNECTIONPRIVATE_H
#define CONNECTIONPRIVATE_H

#include "ConnectionOptions.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

class Connection {
public:
	Connection(void);
	std::string request(const std::string& message);

private:
	static const unsigned short LOCAL_PORT = 0;
	static const size_t MAXIMAL_REPLY_LENGTH = 1024;

	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint receiver_endpoint;
	boost::mutex mutex;

	ConnectionOptions loadConnectionOptions(void) const;
	boost::asio::ip::udp::endpoint resolve(
		const ConnectionOptions& connection_options
	);
	void send(const std::string& message);
	std::string receive(void);
};

typedef boost::shared_ptr<Connection> ConnectionSmartPointer;
#endif

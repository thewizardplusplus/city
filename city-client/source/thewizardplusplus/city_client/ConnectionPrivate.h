#ifndef CONNECTIONPRIVATE_H
#define CONNECTIONPRIVATE_H

#include <boost/asio.hpp>

namespace thewizardplusplus {
namespace city_client {

class ConnectionPrivate {
public:
	ConnectionPrivate(const std::string& host, const unsigned short port);
	~ConnectionPrivate(void);
	boost::asio::ip::udp::endpoint resolve(
		const std::string& host,
		const unsigned short port
	);
	void send(const std::string& message);
	std::string receive(void);

private:
	static const unsigned short LOCAL_PORT = 0;
	static const size_t MAXIMAL_REPLY_LENGTH = 1024;

	boost::asio::io_service io_service;
	boost::asio::ip::udp::endpoint local_endpoint;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint receiver_endpoint;
	char reply_buffer[MAXIMAL_REPLY_LENGTH];
	boost::asio::ip::udp::endpoint sender_endpoint;
};

}
}
#endif

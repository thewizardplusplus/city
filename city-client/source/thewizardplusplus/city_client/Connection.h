#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>

namespace thewizardplusplus {
namespace city_client {

class Connection {
public:
	static const size_t MAXIMAL_REPLY_LENGTH = 1024;

	explicit Connection(const std::string& host_ip, const unsigned short port);
	virtual ~Connection(void);
	void sendMessage(const std::string& message);

protected:
	virtual void onReceiveMessage(const std::string& message) = 0;

private:
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint receiver_endpoint;
	boost::asio::ip::udp::endpoint sender_endpoint;
};

}
}
#endif

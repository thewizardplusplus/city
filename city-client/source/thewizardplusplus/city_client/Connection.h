#ifndef CONNECTION_H
#define CONNECTION_H

#include "ReceiveMessageListener.h"
#include <boost/asio.hpp>
#include <list>

namespace thewizardplusplus {
namespace city_client {

class Connection {
public:
	typedef ReceiveMessageListener::Pointer Listener;

	explicit Connection(const std::string& host_ip, const unsigned short port);
	~Connection(void);
	void addReceiveMessageListener(const Listener& listener);
	void removeReceiveMessageListener(const Listener& listener);
	void sendMessage(const std::string& message);

private:
	typedef std::list<ReceiveMessageListener::Pointer> ListenerGroup;

	static const unsigned short LOCAL_PORT = 0;
	static const size_t MAXIMAL_REPLY_LENGTH = 1024;

	boost::asio::io_service io_service;
	boost::asio::ip::udp::endpoint local_endpoint;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint receiver_endpoint;
	boost::asio::ip::udp::endpoint sender_endpoint;
	ListenerGroup listeners;
};

}
}
#endif

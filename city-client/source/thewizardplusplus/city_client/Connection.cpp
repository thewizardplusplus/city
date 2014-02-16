#include "Connection.h"

using namespace thewizardplusplus::city_client;
using namespace boost::asio;
using namespace boost::asio::ip;

Connection::Connection(const std::string& host_ip, const unsigned short port) :
	local_endpoint(udp::v4(), LOCAL_PORT),
	socket(io_service, local_endpoint),
	receiver_endpoint(address::from_string(host_ip), port)
{}

Connection::~Connection(void) {
	if (socket.is_open()) {
		socket.close();
	}
}

void Connection::addReceiveMessageListener(
	const Connection::Listener& listener
) {
	ListenerGroup::const_iterator group_begin = listeners.begin();
	ListenerGroup::const_iterator group_end = listeners.end();
	if (std::find(group_begin, group_end, listener) == group_end) {
		listeners.push_back(listener);
	}
}

void Connection::removeReceiveMessageListener(
	const Connection::Listener& listener
) {
	listeners.remove(listener);
}

void Connection::sendMessage(const std::string& message) {
	socket.send_to(buffer(message), receiver_endpoint);

	char reply_buffer[MAXIMAL_REPLY_LENGTH];
	size_t reply_length = socket.receive_from(
		buffer(reply_buffer),
		sender_endpoint
	);
	std::string reply(reply_buffer, reply_length);

	ListenerGroup::const_iterator i = listeners.begin();
	for (; i != listeners.end(); ++i) {
		(*i).get()->onReceiveMessage(reply);
	}
}

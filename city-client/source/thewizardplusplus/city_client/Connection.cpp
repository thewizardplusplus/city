#include "Connection.h"

using namespace thewizardplusplus::city_client;
using namespace boost::asio;
using namespace boost::asio::ip;

Connection::Connection(const std::string& host_ip, const unsigned short port) :
	socket(io_service, udp::endpoint(udp::v4(), 0)),
	receiver_endpoint(address::from_string(host_ip), port)
{}

Connection::~Connection(void) {
	if (socket.is_open()) {
		socket.close();
	}
}

void Connection::sendMessage(const std::string& message) {
	socket.send_to(buffer(message), receiver_endpoint);

	char reply_buffer[MAXIMAL_REPLY_LENGTH];
	size_t reply_length = socket.receive_from(
		buffer(reply_buffer),
		sender_endpoint
	);
	onReceiveMessage(std::string(reply_buffer, reply_length));
}

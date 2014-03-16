#include "Connection.h"

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

Connection::Connection(const uint port) :
	socket(io_service, udp::endpoint(udp::v4(), port))
{}

void Connection::send(const std::string& message) {
	socket.send_to(buffer(message), receiver_endpoint);
}

std::string Connection::receive(void) {
	char reply_buffer[MAXIMAL_REPLY_LENGTH];
	size_t reply_length = socket.receive_from(
		buffer(reply_buffer),
		receiver_endpoint
	);

	return std::string(reply_buffer, reply_length);
}

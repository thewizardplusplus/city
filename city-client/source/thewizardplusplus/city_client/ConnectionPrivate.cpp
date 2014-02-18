#include "ConnectionPrivate.h"
#include <boost/lexical_cast.hpp>

using namespace thewizardplusplus::city_client;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

ConnectionPrivate::ConnectionPrivate(
	const std::string& host,
	const unsigned short port
) :
	local_endpoint(udp::v4(), LOCAL_PORT),
	socket(io_service, local_endpoint)
{
	receiver_endpoint = resolve(host, port);
}

ConnectionPrivate::~ConnectionPrivate(void) {
	if (socket.is_open()) {
		socket.close();
	}
}

udp::endpoint ConnectionPrivate::resolve(
	const std::string& host,
	const unsigned short port
) {
	udp::resolver resolver(io_service);
	udp::resolver::query query(
		udp::v4(),
		host,
		lexical_cast<std::string>(port)
	);
	udp::resolver::iterator iterator = resolver.resolve(query);

	return *iterator;
}

void ConnectionPrivate::send(const std::string& message) {
	socket.send_to(buffer(message), receiver_endpoint);
}

std::string ConnectionPrivate::receive(void) {
	size_t reply_length = socket.receive_from(
		buffer(reply_buffer),
		sender_endpoint
	);
	return std::string(reply_buffer, reply_length);
}

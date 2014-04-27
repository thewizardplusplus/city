#include "Connection.h"
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::program_options;

Connection::Connection(void) :
	socket(io_service, udp::endpoint(udp::v4(), LOCAL_PORT))
{
	//ConnectionOptions connection_options = loadConnectionOptions();
	ConnectionOptions connection_options("46.36.222.89", 8001);
	receiver_endpoint = resolve(connection_options);
}

std::string Connection::request(const std::string& message) {
	lock_guard<boost::mutex> guard(mutex);

	send(message);
	return receive();
}

ConnectionOptions Connection::loadConnectionOptions(void) const {
	options_description options;
	options.add_options()
		("2D RTS.host", value<std::string>()->required())
		("2D RTS.port", value<unsigned short>()->required());

	variables_map parameters;
	store(
		parse_config_file<char>("settings.ini", options),
		parameters
	);
	notify(parameters);

	return ConnectionOptions(
		parameters["2D RTS.host"].as<std::string>(),
		parameters["2D RTS.port"].as<unsigned short>()
	);
}

udp::endpoint Connection::resolve(
	const ConnectionOptions& connection_options
) {
	udp::resolver resolver(io_service);
	udp::resolver::query query(
		udp::v4(),
		connection_options.host,
		lexical_cast<std::string>(connection_options.port)
	);

	return *resolver.resolve(query);
}

void Connection::send(const std::string& message) {
	socket.send_to(buffer(message), receiver_endpoint);
}

std::string Connection::receive(void) {
	char reply_buffer[MAXIMAL_REPLY_LENGTH];
	udp::endpoint sender_endpoint;
	size_t reply_length = socket.receive_from(
		buffer(reply_buffer),
		sender_endpoint
	);

	return std::string(reply_buffer, reply_length);
}

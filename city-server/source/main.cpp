#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace boost;
using namespace boost::program_options;
using namespace boost::asio;
using namespace boost::asio::ip;

static const size_t MAXIMAL_MESSAGE_LENGTH = 1024;

unsigned short ParseCommandLineArguments(
	int arguments_number,
	char* arguments[]
) {
	options_description options;
	options.add_options()
		("port", value<unsigned short>()->required());

	variables_map parameters;
	store(
		command_line_parser(arguments_number, arguments)
			.options(options)
			.run(),
		parameters
	);
	notify(parameters);

	return parameters["port"].as<unsigned short>();
}

void StartServer(unsigned short port) {
	io_service service;
	udp::socket socket(service, udp::endpoint(udp::v4(), port));

	while (true) {
		char message_buffer[MAXIMAL_MESSAGE_LENGTH];
		udp::endpoint sender_endpoint;
		size_t message_length = socket.receive_from(
			buffer(message_buffer),
			sender_endpoint
		);
		socket.send_to(buffer(message_buffer, message_length), sender_endpoint);
	}
}

int main(int arguments_number, char* arguments[]) try {
	unsigned short port = ParseCommandLineArguments(
		arguments_number,
		arguments
	);
	StartServer(port);
} catch(const std::exception& exception) {
	std::cerr
		<< format("City client error: %s.")
			% to_lower_copy(std::string(exception.what()))
		<< std::endl;
}

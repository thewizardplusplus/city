#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace boost;
using namespace boost::program_options;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::algorithm;

typedef std::map<std::string, time_t> InterlocutorTimestampGroup;

static const size_t MAXIMAL_MESSAGE_LENGTH = 1024;

InterlocutorTimestampGroup interlocutor_timestamps;

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

void ProcessCommandInterlocutors(udp::socket& socket, udp::endpoint& endpoint) {
	std::string reply;
	InterlocutorTimestampGroup::const_iterator i =
		interlocutor_timestamps.begin();
	for (; i != interlocutor_timestamps.end(); ++i) {
		reply += i->first + '/';
	}
	if (!reply.empty()) {
		reply = reply.substr(0, reply.length() - 1);
	} else {
		reply = "empty";
	}

	socket.send_to(buffer(reply), endpoint);
}

void ProcessMessage(
	const std::string& message,
	udp::socket& socket,
	udp::endpoint& endpoint
) {
	std::vector<std::string> message_parts;
	split(message_parts, message, is_any_of("/"), token_compress_on);
	if (message_parts.size() < 2) {
		throw std::runtime_error("missed command");
	}

	std::string nickname = message_parts[0];
	interlocutor_timestamps[nickname] = std::time(NULL);

	std::string command = message_parts[1];
	if (command == "interlocutors") {
		ProcessCommandInterlocutors(socket, endpoint);
	} else {
		throw std::runtime_error(
			(format("unknown command \"%s\"") % command).str()
		);
	}
}

void StartServer(unsigned short port) {
	io_service service;
	udp::socket socket(service, udp::endpoint(udp::v4(), port));
	udp::endpoint sender_endpoint;

	while (true) try {
		char message_buffer[MAXIMAL_MESSAGE_LENGTH];
		size_t message_length = socket.receive_from(
			buffer(message_buffer),
			sender_endpoint
		);

		ProcessMessage(
			std::string(message_buffer, message_length),
			socket,
			sender_endpoint
		);
	} catch(const std::exception& exception) {
		std::string message = (format("City server error: %s.")
			% to_lower_copy(std::string(exception.what()))).str();
		std::cerr << message << std::endl;
		socket.send_to(buffer(message), sender_endpoint);
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
		<< format("City server error: %s.")
			% to_lower_copy(std::string(exception.what()))
		<< std::endl;
}

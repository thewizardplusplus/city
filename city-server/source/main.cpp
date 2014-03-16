#include "Connection.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <iostream>

using namespace boost;
using namespace boost::algorithm;
using namespace boost::program_options;

static const char MESSAGE_PARTS_SEPARATOR = ':';
static const size_t MAXIMAL_MESSAGE_LENGTH = 1024;
static const regex MESSAGE_PATTERN(
	"^(r|(w:(0|[1-9]\\d*)|m:(0|[1-9]\\d*):[0-3]))$"
);

std::string ConvertCharToString(char symbol) {
	return std::string(1, symbol);
}

void ProcessError(const std::string& message) {
	std::cerr
		<< format("City client error: %s.\n")
			% to_lower_copy(message)
		<< std::flush;
}

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

void ProcessMessage(
	const ConnectionSmartPointer& connection,
	const std::string& message
) {
	if (!regex_match(message, MESSAGE_PATTERN)) {
		throw std::runtime_error("invalid command");
	}

	if (message == "r") {
		connection->send("registration request");
		return;
	}

	std::vector<std::string> message_parts;
	split(
		message_parts,
		message,
		is_any_of(ConvertCharToString(MESSAGE_PARTS_SEPARATOR))
	);

	if (starts_with(message, "w")) {
		connection->send(
			(format("world request, player id: #%s")
				% message_parts[1]).str()
		);
	} else if (starts_with(message, "m")) {
		std::vector<std::string> directions;
		directions.push_back("up");
		directions.push_back("right");
		directions.push_back("down");
		directions.push_back("left");

		connection->send(
			(format("player move request to %s, player id: #%s")
				% directions.at(lexical_cast<size_t>(message_parts[2]))
				% message_parts[1]).str()
		);
	}
}

void StartServer(const ConnectionSmartPointer& connection) {
	while (true) try {
		std::string message = connection->receive();
		ProcessMessage(connection, message);
	} catch(const std::exception& exception) {
		ProcessError(exception.what());
		connection->send(
			(format("error%c%s")
				% MESSAGE_PARTS_SEPARATOR
				% exception.what()).str()
		);
	}
}

int main(int arguments_number, char* arguments[]) try {
	unsigned short port = ParseCommandLineArguments(
		arguments_number,
		arguments
	);
	ConnectionSmartPointer connection(new Connection(port));
	StartServer(connection);
} catch(const std::exception& exception) {
	ProcessError(exception.what());
}

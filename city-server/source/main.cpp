#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <iostream>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::algorithm;
using namespace boost::program_options;

typedef
	tuple<shared_ptr<io_service>, shared_ptr<udp::socket>, udp::endpoint>
	ConnectionContext;

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

ConnectionContext OpenConnection(unsigned short port) {
	shared_ptr<io_service> service(new io_service());
	return make_tuple(
		service,
		new udp::socket(*service.get(), udp::endpoint(udp::v4(), port)),
		udp::endpoint()
	);
}

std::string ReceiveMessage(ConnectionContext& connection_context) {
	char message_buffer[MAXIMAL_MESSAGE_LENGTH];
	size_t message_length = connection_context.get<1>()->receive_from(
		buffer(message_buffer),
		connection_context.get<2>()
	);

	return std::string(message_buffer, message_length);
}

void SendReply(
	const ConnectionContext& connection_context,
	const std::string& reply
) {
	connection_context.get<1>()->send_to(
		buffer(reply),
		connection_context.get<2>()
	);
}

void ProcessMessage(
	const ConnectionContext& connection_context,
	const std::string& message
) {
	if (!regex_match(message, MESSAGE_PATTERN)) {
		throw std::runtime_error("invalid command");
	}

	if (message == "r") {
		SendReply(connection_context, "registration request");
		return;
	}

	std::vector<std::string> message_parts;
	split(
		message_parts,
		message,
		is_any_of(ConvertCharToString(MESSAGE_PARTS_SEPARATOR))
	);

	if (starts_with(message, "w")) {
		SendReply(
			connection_context,
			(format("world request, player id: #%s")
				% message_parts[1]).str()
		);
	} else if (starts_with(message, "m")) {
		std::vector<std::string> directions;
		directions.push_back("up");
		directions.push_back("right");
		directions.push_back("down");
		directions.push_back("left");

		SendReply(
			connection_context,
			(format("player move request to %s, player id: #%s")
				% directions.at(lexical_cast<size_t>(message_parts[2]))
				% message_parts[1]).str()
		);
	}
}

void StartServer(ConnectionContext& connection_context) {
	while (true) try {
		std::string message = ReceiveMessage(connection_context);
		ProcessMessage(connection_context,message);
	} catch(const std::exception& exception) {
		ProcessError(exception.what());
		SendReply(
			connection_context,
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
	ConnectionContext connection_context = OpenConnection(port);
	StartServer(connection_context);
} catch(const std::exception& exception) {
	ProcessError(exception.what());
}

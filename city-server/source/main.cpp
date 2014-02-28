#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace boost;
using namespace boost::program_options;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::adaptors;
using namespace boost::algorithm;

typedef
	tuple<shared_ptr<io_service>, shared_ptr<udp::socket>, udp::endpoint>
	ConnectionContext;
typedef std::map<std::string, time_t> InterlocutorTimestampGroup;

static const size_t MAXIMAL_MESSAGE_LENGTH = 1024;
static const time_t MAXIMAL_INTERLOCUTOR_TIMEOUT = 10;
static const char MESSAGE_PARTS_SEPARATOR = '/';

InterlocutorTimestampGroup interlocutor_timestamps;

void ProcessError(const std::string& message) {
	std::cerr
		<< format("City client error: %s.\n")
			% to_lower_copy(message);
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
	std::vector<std::string> message_parts;
	split(
		message_parts,
		message,
		is_any_of(std::string(1, MESSAGE_PARTS_SEPARATOR)),
		token_compress_on
	);
	if (message_parts.size() < 2) {
		throw std::runtime_error("missed command");
	}

	std::string nickname = message_parts[0];
	if (nickname.empty()) {
		throw std::runtime_error("invalid nickname");
	}

	std::string command = message_parts[1];
	if (command == "interlocutors") {
		interlocutor_timestamps[nickname] = std::time(NULL);
		SendReply(
			connection_context,
			join(
				interlocutor_timestamps | map_keys,
				std::string(1, MESSAGE_PARTS_SEPARATOR)
			)
		);
	} else {
		throw std::runtime_error(
			(format("unknown command \"%s\"") % command).str()
		);
	}
}

void RemoveLostInterlocutors(void) {
	InterlocutorTimestampGroup::iterator i = interlocutor_timestamps.begin();
	time_t current_timestamp = std::time(NULL);
	while (i != interlocutor_timestamps.end()) {
		if (current_timestamp - i->second >= MAXIMAL_INTERLOCUTOR_TIMEOUT) {
			interlocutor_timestamps.erase(i++);
		} else {
			++i;
		}
	}
}

void StartServer(ConnectionContext& connection_context) {
	while (true) try {
		char message_buffer[MAXIMAL_MESSAGE_LENGTH];
		size_t message_length = connection_context.get<1>()->receive_from(
			buffer(message_buffer),
			connection_context.get<2>()
		);

		ProcessMessage(
			connection_context,
			std::string(message_buffer, message_length)
		);

		RemoveLostInterlocutors();
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

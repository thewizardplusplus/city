#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/regex.hpp>
#include <iostream>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::algorithm;
using namespace boost::program_options;
using namespace boost::adaptors;

typedef
	tuple<shared_ptr<io_service>, shared_ptr<udp::socket>, udp::endpoint>
	ConnectionContext;
typedef std::map<std::string, time_t> InterlocutorTimestampGroup;
typedef tuple<std::string, std::string> Message;
typedef std::map<time_t, Message> MessageGroup;
typedef tuple<InterlocutorTimestampGroup, MessageGroup> ServerData;

static const char MESSAGE_PARTS_GLOBAL_SEPARATOR = ';';
static const regex TIMESTAMP_PATTERN("^[1-9]\\d*$");
static const char MESSAGE_PARTS_INNER_SEPARATOR = ':';
static const time_t MAXIMAL_INTERLOCUTOR_TIMEOUT = 12;
static const size_t MAXIMAL_MESSAGE_LENGTH = 1024;

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

void SendReply(
	const ConnectionContext& connection_context,
	const std::string& reply
) {
	connection_context.get<1>()->send_to(
		buffer(reply),
		connection_context.get<2>()
	);
}

void AddOrUpdateInterlocutor(
	ServerData& server_data,
	const std::string& nickname
) {
	server_data.get<0>()[nickname] = std::time(NULL);
}

std::string FormatMessage(time_t timestamp, const Message& message) {
	return
		(format("%s%c%u%c%s")
			% message.get<0>()
			% MESSAGE_PARTS_INNER_SEPARATOR
			% timestamp
			% MESSAGE_PARTS_INNER_SEPARATOR
			% message.get<1>()).str();
}

void ProcessMessage(
	const ConnectionContext& connection_context,
	ServerData& server_data,
	const std::string& message
) {
	std::vector<std::string> message_parts;
	split(
		message_parts,
		message,
		is_any_of(ConvertCharToString(MESSAGE_PARTS_GLOBAL_SEPARATOR)),
		token_compress_on
	);
	if (message_parts.empty() || message_parts[0].empty()) {
		throw std::runtime_error("missed nickname");
	}
	if (message_parts.size() < 2 || message_parts[1].empty()) {
		throw std::runtime_error("missed command");
	}

	std::string nickname = message_parts[0];
	std::string command = message_parts[1];
	if (command == "interlocutors") {
		AddOrUpdateInterlocutor(server_data, nickname);
		SendReply(
			connection_context,
			join(
				server_data.get<0>() | map_keys,
				ConvertCharToString(MESSAGE_PARTS_GLOBAL_SEPARATOR)
			)
		);
	} else if (command == "message") {
		if (message_parts.size() < 3 || message_parts[2].empty()) {
			throw std::runtime_error("missed message text");
		}

		AddOrUpdateInterlocutor(server_data, nickname);

		time_t timestamp = std::time(NULL);
		Message message(nickname, message_parts[2]);
		server_data.get<1>()[timestamp] = message;
		std::cout << FormatMessage(timestamp, message) << '\n' << std::flush;

		SendReply(connection_context, "ok");
	} else if (command == "history") {
		if (message_parts.size() < 3 || message_parts[2].empty()) {
			throw std::runtime_error("missed timestamp");
		}

		std::string timestamp = message_parts[2];
		if (!regex_match(timestamp, TIMESTAMP_PATTERN)) {
			throw std::runtime_error("invalid timestamp");
		}

		AddOrUpdateInterlocutor(server_data, nickname);

		std::string reply;
		MessageGroup::const_iterator i = server_data.get<1>().upper_bound(
			lexical_cast<time_t>(timestamp)
		);
		for (; i != server_data.get<1>().end(); ++i) {
			reply +=
				(format("%s%c")
					% FormatMessage(i->first, i->second)
					% MESSAGE_PARTS_GLOBAL_SEPARATOR).str();
		}
		if (!reply.empty()) {
			reply = reply.substr(0, reply.length() - 1);
		}

		SendReply(connection_context, reply);
	} else {
		throw std::runtime_error("invalid command");
	}
}

void RemoveLostInterlocutors(ServerData& server_data) {
	InterlocutorTimestampGroup::iterator i = server_data.get<0>().begin();
	time_t current_timestamp = std::time(NULL);
	while (i != server_data.get<0>().end()) {
		if (current_timestamp - i->second >= MAXIMAL_INTERLOCUTOR_TIMEOUT) {
			server_data.get<0>().erase(i++);
		} else {
			++i;
		}
	}
}

void StartServer(ConnectionContext& connection_context) {
	ServerData server_data;
	while (true) try {
		char message_buffer[MAXIMAL_MESSAGE_LENGTH];
		size_t message_length = connection_context.get<1>()->receive_from(
			buffer(message_buffer),
			connection_context.get<2>()
		);

		ProcessMessage(
			connection_context,
			server_data,
			std::string(message_buffer, message_length)
		);

		RemoveLostInterlocutors(server_data);
	} catch(const std::exception& exception) {
		ProcessError(exception.what());
		SendReply(
			connection_context,
			(format("error%c%s")
				% MESSAGE_PARTS_GLOBAL_SEPARATOR
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

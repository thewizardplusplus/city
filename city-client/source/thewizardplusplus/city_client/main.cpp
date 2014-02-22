#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <iostream>

using namespace boost;
using namespace boost::program_options;
using namespace boost::asio;
using namespace boost::asio::ip;

typedef tuple<std::string, unsigned short> ConnectionOptions;
typedef
	tuple<shared_ptr<io_service>, shared_ptr<udp::socket>, udp::endpoint>
	ConnectionContext;

void ProcessError(const std::string& message) {
	std::cerr
		<< format("City client error: %s.")
			% to_lower_copy(message)
		<< std::endl;
}

ConnectionOptions ParseCommandLineArguments(
	int arguments_number,
	char* arguments[]
) {
	options_description options;
	options.add_options()
		("host", value<std::string>()->required())
		("port", value<unsigned short>()->required());

	variables_map parameters;
	store(
		command_line_parser(arguments_number, arguments)
			.options(options)
			.run(),
		parameters
	);
	notify(parameters);

	std::string host = parameters["host"].as<std::string>();
	unsigned short port = parameters["port"].as<unsigned short>();

	return ConnectionOptions(host, port);
}

ConnectionContext OpenConnection(const ConnectionOptions& connection_options) {
	shared_ptr<io_service> service(new io_service());

	udp::resolver resolver(*service.get());
	udp::resolver::query query(
		udp::v4(),
		connection_options.get<0>(),
		lexical_cast<std::string>(connection_options.get<1>())
	);

	return make_tuple(
		service,
		new udp::socket(*service.get(), udp::endpoint(udp::v4(), 0)),
		*resolver.resolve(query)
	);
}

void SendMessage(
	const ConnectionContext& connection_context,
	const std::string& message
) {
	connection_context.get<1>()->send_to(
		buffer(message),
		connection_context.get<2>()
	);

	char reply_buffer[1024];
	udp::endpoint sender_endpoint;
	size_t reply_length = connection_context.get<1>()->receive_from(
		buffer(reply_buffer),
		sender_endpoint
	);
	std::string reply(reply_buffer, reply_length);

	std::cout << format("Server reply: \"%s\".\n") % reply;
}

void StartRepl(const ConnectionContext& connection_context) {
	std::string command;
	while (true) try {
		std::cout << "$ ";
		std::getline(std::cin, command);

		trim(command);
		if (command.empty()) {
			continue;
		}

		if (starts_with(command, "send")) {
			std::string message = command.substr(4);
			trim(message);
			if (message.empty()) {
				throw std::runtime_error(
					"City client error: not allowed send an empty message."
				);
			}

			SendMessage(connection_context, message);
		} else if (command == "exit") {
			break;
		} else {
			throw std::runtime_error(
				(format("City client error: unknown command \"%s\".")
					% command).str()
			);
		}
	} catch(const std::exception& exception) {
		ProcessError(exception.what());
	}
}

int main(int arguments_number, char* arguments[]) try {
	ConnectionOptions connection_options = ParseCommandLineArguments(
		arguments_number,
		arguments
	);
	ConnectionContext connection_context = OpenConnection(connection_options);
	StartRepl(connection_context);
} catch(const std::exception& exception) {
	ProcessError(exception.what());
}

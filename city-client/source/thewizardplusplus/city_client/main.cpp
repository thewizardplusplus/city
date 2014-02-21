#include "exceptions/EmptyMessageException.h"
#include "exceptions/UnknownCommandException.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;
using namespace boost::program_options;

void ShowVersion(void) {
	std::cout << "City client, v0.1" << std::endl;
	std::cout << "(c) thewizardplusplus, 2014" << std::endl;
}

void ShowHelp(const options_description& options) {
	ShowVersion();
	std::cout << std::endl;

	std::cout << "Usage:" << std::endl;
	std::cout << "  city-client [options]" << std::endl;

	std::cout << options << std::endl;

	std::cout << "Commands (REPL):" << std::endl;
	std::cout << "  send arg               - send message;" << std::endl;
	std::cout << "  exit                   - exit." << std::endl;
}

void ProcessOptions(int arguments_number, char** arguments) {
	options_description generic_options("Generic options");
	generic_options.add_options()
		("version,v", " - show version;")
		("help,h", " - show help.");

	options_description connection_options("Connection options");
	connection_options.add_options()
		(
			"host",
			value<std::string>()->required(),
			" - host name or IP (required);"
		)
		(
			"port",
			value<unsigned short>()->required(),
			" - port number (required)."
		);

	options_description all_options;
	all_options.add(generic_options).add(connection_options);

	variables_map generic_parameters;
	store(
		command_line_parser(arguments_number, arguments)
			.options(generic_options)
			.allow_unregistered()
			.run(),
		generic_parameters
	);
	notify(generic_parameters);

	if (generic_parameters.count("version")) {
		ShowVersion();
		std::exit(EXIT_SUCCESS);
	}
	if (generic_parameters.count("help")) {
		ShowHelp(all_options);
		std::exit(EXIT_SUCCESS);
	}

	variables_map connection_parameters;
	store(
		parse_command_line(arguments_number, arguments, connection_options),
		connection_parameters
	);
	notify(connection_parameters);

	std::string host = connection_parameters["host"].as<std::string>();
	unsigned short port = connection_parameters["port"].as<unsigned short>();
	std::cout << format("Host: \"%s\".") % host << std::endl;
	std::cout << format("Port: %u.") % port << std::endl;
}

void ReplStart(void) {
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
				throw EmptyMessageException();
			}

			std::cout << format("Send message \"%s\".") % message << std::endl;
		} else if (command == "exit" || command == "quit") {
			break;
		} else {
			throw UnknownCommandException(command);
		}
	} catch(const CityClientException& exception) {
		std::cerr << exception.what() << std::endl;
	}
}

int main(int arguments_number, char** arguments) try {
	ProcessOptions(arguments_number, arguments);
	ReplStart();
} catch(const std::exception& exception) {
	std::cerr
		<< format("City client unknown error: %s.")
			% to_lower_copy(std::string(exception.what()))
		<< std::endl;
}

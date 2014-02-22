#include "OptionsProcessor.h"
#include "exceptions/EmptyMessageException.h"
#include "exceptions/UnknownCommandException.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace thewizardplusplus::city_client;
using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;

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
		} else if (command == "exit") {
			break;
		} else {
			throw UnknownCommandException(command);
		}
	} catch(const CityClientException& exception) {
		std::cerr << exception.what() << std::endl;
	}
}

int main(int arguments_number, char** arguments) try {
	CommandLineArguments command_line_arguments(arguments_number, arguments);

	OptionsProcessor options_processor;
	ConnectionOptions connection_options = options_processor.process(
		command_line_arguments
	);
	std::cout << format("Host: \"%s\".\n") % connection_options.getHost();
	std::cout << format("Port: %u.\n") % connection_options.getPort();

	//ReplStart();
} catch(const std::exception& exception) {
	std::cerr
		<< format("City client unknown error (%s): %s.")
			% typeid(exception).name()
			% to_lower_copy(std::string(exception.what()))
		<< std::endl;
}

#include "exceptions/EmptyMessageException.h"
#include "exceptions/UnknownCommandException.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;

int main(void) try {
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
} catch(const std::exception& exception) {
	std::cerr
		<< format("City client unknown error: %s.")
			% to_lower_copy(std::string(exception.what()))
		<< std::endl;
}

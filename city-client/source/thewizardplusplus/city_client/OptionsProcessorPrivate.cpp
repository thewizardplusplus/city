#include "OptionsProcessorPrivate.h"

using namespace thewizardplusplus::city_client;
using namespace boost::program_options;

ConnectionOptions OptionsProcessorPrivate::process(
	const CommandLineArguments& arguments
) {
	variables_map generic_parameters = generic_options_parser.parse(arguments);
	processGenericOptions(generic_parameters);

	variables_map connection_parameters = connection_options_parser.parse(
		arguments
	);
	return processConnectionOptions(connection_parameters);
}

void OptionsProcessorPrivate::processGenericOptions(
	const variables_map& parameters
) const {
	if (parameters.count("version")) {
		showVersion();
		std::exit(EXIT_SUCCESS);
	}
	if (parameters.count("help")) {
		showHelp();
		std::exit(EXIT_SUCCESS);
	}
}

ConnectionOptions OptionsProcessorPrivate::processConnectionOptions(
	const variables_map& parameters
) const {
	std::string host = parameters["host"].as<std::string>();
	unsigned short port = parameters["port"].as<unsigned short>();

	return ConnectionOptions(host, port);
}

void OptionsProcessorPrivate::showVersion(void) const {
	std::cout
		<< "City client, v0.1\n"
		<< "(c) thewizardplusplus, 2014\n"
		<< "\n";
}

void OptionsProcessorPrivate::showHelp(void) const {
	showVersion();
	showShortHelp();
}

void OptionsProcessorPrivate::showShortHelp(void) const {
	std::cout
		<< "Usage:\n"
		<< "  city-client [options]\n"
		<< "\n"
		<< generic_options_parser.getDescription()
		<< "\n"
		<< connection_options_parser.getDescription()
		<< "\n"
		<< "Commands (REPL):\n"
		<< "  send arg               - send message;\n"
		<< "  exit                   - exit.\n"
		<< "\n";
}

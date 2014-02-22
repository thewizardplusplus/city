#include "OptionsProcessorPrivate.h"

using namespace thewizardplusplus::city_client;
using namespace boost::program_options;

OptionsProcessorPrivate::OptionsProcessorPrivate(void) :
	generic_options("Generic options"),
	connection_options("Connection options")
{
	defineGenericOptions();
	defineConnectionOptions();

	all_options.add(generic_options).add(connection_options);
}

ConnectionOptions OptionsProcessorPrivate::process(
	const CommandLineArguments& arguments
) {
	processGenericOptions(arguments);

	ConnectionOptions connection_options = processConnectionOptions(arguments);
	return connection_options;
}

void OptionsProcessorPrivate::defineGenericOptions(void) {
	generic_options.add_options()
		("version,v", " - show version;")
		("help,h", " - show help.");
}

void OptionsProcessorPrivate::defineConnectionOptions(void) {
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
}

void OptionsProcessorPrivate::processGenericOptions(
	const CommandLineArguments& arguments
) const {
	variables_map generic_parameters = parseGenericOptions(arguments);
	if (generic_parameters.count("version")) {
		showVersion();
		std::exit(EXIT_SUCCESS);
	}
	if (generic_parameters.count("help")) {
		showHelp();
		std::exit(EXIT_SUCCESS);
	}
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
		<< all_options
		<< "\n"
		<< "Commands (REPL):\n"
		<< "  send arg               - send message;\n"
		<< "  exit                   - exit.\n"
		<< "\n";
}

variables_map OptionsProcessorPrivate::parseGenericOptions(
	const CommandLineArguments& arguments
) const {
	variables_map generic_parameters;
	store(
		command_line_parser(arguments.getArguments())
			.options(generic_options)
			.allow_unregistered()
			.run(),
		generic_parameters
	);
	notify(generic_parameters);

	return generic_parameters;
}

ConnectionOptions OptionsProcessorPrivate::processConnectionOptions(
	const CommandLineArguments& arguments
) const {
	variables_map connection_parameters = parseConnectionOptions(arguments);
	std::string host = connection_parameters["host"].as<std::string>();
	unsigned short port = connection_parameters["port"].as<unsigned short>();

	return ConnectionOptions(host, port);
}

variables_map OptionsProcessorPrivate::parseConnectionOptions(
	const CommandLineArguments& arguments
) const {
	variables_map connection_parameters;
	store(
		command_line_parser(arguments.getArguments())
			.options(connection_options)
			.run(),
		connection_parameters
	);
	notify(connection_parameters);

	return connection_parameters;
}

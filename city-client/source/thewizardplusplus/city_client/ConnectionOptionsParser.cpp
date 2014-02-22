#include "ConnectionOptionsParser.h"

using namespace thewizardplusplus::city_client;
using namespace boost::program_options;

ConnectionOptionsParser::ConnectionOptionsParser(void) :
	OptionsParser("Connection options")
{
	options.add_options()
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

command_line_parser ConnectionOptionsParser::constructCommandLineParser(
	const CommandLineArguments& arguments
) const {
	return
		command_line_parser(arguments.getArguments())
		.options(options);
}

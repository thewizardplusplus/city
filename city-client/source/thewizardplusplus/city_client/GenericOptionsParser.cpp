#include "GenericOptionsParser.h"

using namespace thewizardplusplus::city_client;
using namespace boost::program_options;

GenericOptionsParser::GenericOptionsParser(void) :
	OptionsParser("Generic options")
{
	options.add_options()
		("version,v", " - show version;")
		("help,h", " - show help.");
}

command_line_parser GenericOptionsParser::constructCommandLineParser(
	const CommandLineArguments& arguments
) const {
	return
		command_line_parser(arguments.getArguments())
		.options(options)
		.allow_unregistered();
}

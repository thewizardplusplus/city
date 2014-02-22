#include "OptionsParser.h"

using namespace thewizardplusplus::city_client;
using namespace boost::program_options;

OptionsParser::OptionsParser(const std::string& options_name) :
	options(options_name)
{}

OptionsParser::~OptionsParser(void) {}

std::string OptionsParser::getDescription(void) const {
	std::ostringstream out;
	out << options;

	return out.str();
}

variables_map OptionsParser::parse(
	const CommandLineArguments& arguments
) const {
	variables_map parameters;
	store(constructCommandLineParser(arguments).run(), parameters);
	notify(parameters);

	return parameters;
}

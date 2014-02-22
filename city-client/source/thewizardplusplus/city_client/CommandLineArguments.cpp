#include "CommandLineArguments.h"

using namespace thewizardplusplus::city_client;

CommandLineArguments::CommandLineArguments(
	int arguments_number,
	char* arguments[]
) :
	arguments(arguments_number)
{
	std::copy(arguments, arguments + arguments_number, this->arguments.begin());
}

CommandLineArguments::ArgumentGroup CommandLineArguments::getArguments(
	void
) const {
	return arguments;
}

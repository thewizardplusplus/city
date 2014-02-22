#ifndef OPTIONSPROCESSORPRIVATE_H
#define OPTIONSPROCESSORPRIVATE_H

#include "CommandLineArguments.h"
#include "ConnectionOptions.h"
#include "GenericOptionsParser.h"
#include "ConnectionOptionsParser.h"

namespace thewizardplusplus {
namespace city_client {

class OptionsProcessorPrivate {
public:
	ConnectionOptions process(const CommandLineArguments& arguments);

private:
	GenericOptionsParser generic_options_parser;
	ConnectionOptionsParser connection_options_parser;

	void processGenericOptions(
		const boost::program_options::variables_map& parameters
	) const;
	ConnectionOptions processConnectionOptions(
		const boost::program_options::variables_map& parameters
	) const;
	void showVersion(void) const;
	void showHelp(void) const;
	void showShortHelp(void) const;
};

}
}
#endif

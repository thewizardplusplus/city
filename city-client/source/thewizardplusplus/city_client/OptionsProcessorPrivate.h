#ifndef OPTIONSPROCESSORPRIVATE_H
#define OPTIONSPROCESSORPRIVATE_H

#include "CommandLineArguments.h"
#include "ConnectionOptions.h"
#include <boost/program_options.hpp>

namespace thewizardplusplus {
namespace city_client {

class OptionsProcessorPrivate {
public:
	OptionsProcessorPrivate(void);
	ConnectionOptions process(const CommandLineArguments& arguments);

private:
	boost::program_options::options_description generic_options;
	boost::program_options::options_description connection_options;
	boost::program_options::options_description all_options;

	void defineGenericOptions(void);
	void defineConnectionOptions(void);
	void processGenericOptions(const CommandLineArguments& arguments) const;
	boost::program_options::variables_map parseGenericOptions(
		const CommandLineArguments& arguments
	) const;
	void showVersion(void) const;
	void showHelp(void) const;
	void showShortHelp(void) const;
	ConnectionOptions processConnectionOptions(
		const CommandLineArguments& arguments
	) const;
	boost::program_options::variables_map parseConnectionOptions(
		const CommandLineArguments& arguments
	) const;
};

}
}
#endif

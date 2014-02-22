#ifndef OPTIONSPARSER_H
#define OPTIONSPARSER_H

#include "CommandLineArguments.h"
#include <boost/program_options.hpp>

namespace thewizardplusplus {
namespace city_client {

class OptionsParser {
public:
	OptionsParser(const std::string& options_name);
	virtual ~OptionsParser(void);
	std::string getDescription(void) const;
	boost::program_options::variables_map parse(
		const CommandLineArguments& arguments
	) const;

protected:
	boost::program_options::options_description options;

	virtual boost::program_options::command_line_parser
		constructCommandLineParser(
			const CommandLineArguments& arguments
		) const = 0;
};

}
}
#endif

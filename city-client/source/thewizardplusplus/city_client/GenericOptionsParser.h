#ifndef GENERICOPTIONSPARSER_H
#define GENERICOPTIONSPARSER_H

#include "OptionsParser.h"

namespace thewizardplusplus {
namespace city_client {

class GenericOptionsParser : public OptionsParser {
public:
	GenericOptionsParser(void);

protected:
	virtual boost::program_options::command_line_parser
		constructCommandLineParser(
			const CommandLineArguments& arguments
		) const;
};

}
}
#endif

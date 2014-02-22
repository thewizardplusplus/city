#ifndef CONNECTIONOPTIONSPARSER_H
#define CONNECTIONOPTIONSPARSER_H

#include "OptionsParser.h"

namespace thewizardplusplus {
namespace city_client {

class ConnectionOptionsParser : public OptionsParser {
public:
	ConnectionOptionsParser(void);

protected:
	virtual boost::program_options::command_line_parser
		constructCommandLineParser(
			const CommandLineArguments& arguments
		) const;
};

}
}
#endif

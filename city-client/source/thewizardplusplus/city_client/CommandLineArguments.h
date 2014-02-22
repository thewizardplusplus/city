#ifndef COMMANDLINEARGUMENTS_H
#define COMMANDLINEARGUMENTS_H

#include <vector>
#include <string>

namespace thewizardplusplus {
namespace city_client {

class CommandLineArguments {
public:
	typedef std::vector<std::string> ArgumentGroup;

	CommandLineArguments(int arguments_number, char* arguments[]);
	ArgumentGroup getArguments(void) const;

private:
	ArgumentGroup arguments;
};

}
}
#endif

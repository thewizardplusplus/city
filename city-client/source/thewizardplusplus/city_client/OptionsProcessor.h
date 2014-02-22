#ifndef OPTIONSPROCESSOR_H
#define OPTIONSPROCESSOR_H

#include <memory>

#include "CommandLineArguments.h"
#include "ConnectionOptions.h"

namespace thewizardplusplus {
namespace city_client {

class OptionsProcessorPrivate;

class OptionsProcessor {
public:
	OptionsProcessor(void);
	ConnectionOptions process(const CommandLineArguments& arguments);

private:
	std::auto_ptr<OptionsProcessorPrivate> processor;
};

}
}
#endif

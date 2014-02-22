#ifndef OPTIONSPROCESSOR_H
#define OPTIONSPROCESSOR_H

#include <boost/shared_ptr.hpp>

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
	boost::shared_ptr<OptionsProcessorPrivate> processor;
};

}
}
#endif

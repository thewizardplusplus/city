#include "OptionsProcessor.h"
#include "OptionsProcessorPrivate.h"

using namespace thewizardplusplus::city_client;

OptionsProcessor::OptionsProcessor(void) {
	processor.reset(new OptionsProcessorPrivate());
}

ConnectionOptions OptionsProcessor::process(
	const CommandLineArguments& arguments
) {
	return processor->process(arguments);
}

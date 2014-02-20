#include "UnknownCommandException.h"
#include <boost/format.hpp>

using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;

UnknownCommandException::UnknownCommandException(const std::string& command) :
	CityClientException((format("unknown command \"%s\"") % command).str())
{}

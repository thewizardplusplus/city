#include "CityClientException.h"
#include <boost/format.hpp>

using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;

CityClientException::CityClientException(const std::string& message) :
	std::runtime_error((format("City client error: %s.") % message).str())
{}

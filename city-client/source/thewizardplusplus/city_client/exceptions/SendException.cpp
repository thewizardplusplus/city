#include "SendException.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;
using namespace boost::algorithm;

SendException::SendException(const std::string& message) :
	CityClientException(
		(format("unable to send the message - %s")
			% to_lower_copy(message)).str()
	)
{}

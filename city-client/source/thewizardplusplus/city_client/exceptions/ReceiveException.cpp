#include "ReceiveException.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;

ReceiveException::ReceiveException(const std::string& message) :
	CityClientException(
		(format("unable to receive a reply - %s")
			% to_lower_copy(message)).str()
	)
{}

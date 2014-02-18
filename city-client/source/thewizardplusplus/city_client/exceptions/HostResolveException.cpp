#include "HostResolveException.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

using namespace thewizardplusplus::city_client::exceptions;
using namespace boost;

HostResolveException::HostResolveException(
	const std::string& host,
	const unsigned short port,
	const std::string& message
) :
	CityClientException(
		(format("unable to resolve the host \"%s:%u\" - %s")
			% host
			% port
			% to_lower_copy(message)).str()
	)
{}

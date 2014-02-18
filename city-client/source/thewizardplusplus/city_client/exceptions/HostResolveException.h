#ifndef HOSTRESOLVEEXCEPTION_H
#define HOSTRESOLVEEXCEPTION_H

#include "CityClientException.h"

namespace thewizardplusplus {
namespace city_client {
namespace exceptions {

class HostResolveException : public CityClientException {
public:
	HostResolveException(
		const std::string& host,
		const unsigned short port,
		const std::string& message
	);
};

}
}
}
#endif

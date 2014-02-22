#ifndef CITYCLIENTEXCEPTION_H
#define CITYCLIENTEXCEPTION_H

#include <stdexcept>

namespace thewizardplusplus {
namespace city_client {
namespace exceptions {

class CityClientException : public std::runtime_error {
public:
	explicit CityClientException(const std::string& message);
};

}
}
}
#endif

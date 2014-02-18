#ifndef SENDEXCEPTION_H
#define SENDEXCEPTION_H

#include "CityClientException.h"

namespace thewizardplusplus {
namespace city_client {
namespace exceptions {

class SendException : public CityClientException {
public:
	SendException(const std::string& message);
};

}
}
}
#endif

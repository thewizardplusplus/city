#ifndef RECEIVEEXCEPTION_H
#define RECEIVEEXCEPTION_H

#include "CityClientException.h"

namespace thewizardplusplus {
namespace city_client {
namespace exceptions {

class ReceiveException : public CityClientException {
public:
	ReceiveException(const std::string& message);
};

}
}
}
#endif

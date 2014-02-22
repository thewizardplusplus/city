#ifndef RECEIVEEXCEPTION_H
#define RECEIVEEXCEPTION_H

#include "CityClientException.h"

namespace thewizardplusplus {
namespace city_client {
namespace exceptions {

class ReceiveException : public CityClientException {
public:
	explicit ReceiveException(const std::string& message);
};

}
}
}
#endif

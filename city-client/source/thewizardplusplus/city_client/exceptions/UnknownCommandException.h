#ifndef UNKNOWNCOMMANDEXCEPTION_H
#define UNKNOWNCOMMANDEXCEPTION_H

#include "CityClientException.h"

namespace thewizardplusplus {
namespace city_client {
namespace exceptions {

class UnknownCommandException : public CityClientException {
public:
	UnknownCommandException(const std::string& command);
};

}
}
}
#endif

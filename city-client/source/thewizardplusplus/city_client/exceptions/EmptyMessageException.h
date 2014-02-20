#ifndef EMPTYMESSAGEEXCEPTION_H
#define EMPTYMESSAGEEXCEPTION_H

#include "CityClientException.h"

namespace thewizardplusplus {
namespace city_client {
namespace exceptions {

class EmptyMessageException : public CityClientException {
public:
	EmptyMessageException(void);
};

}
}
}
#endif

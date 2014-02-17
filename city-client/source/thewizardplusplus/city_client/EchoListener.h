#ifndef ECHOLISTENER_H
#define ECHOLISTENER_H

#include "ReceiveMessageListener.h"

namespace thewizardplusplus {
namespace city_client {

class EchoListener : public ReceiveMessageListener {
public:
	virtual void onReceiveMessage(const std::string& message);
};

}
}
#endif

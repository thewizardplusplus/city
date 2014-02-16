#ifndef RECEIVEMESSAGELISTENER_H
#define RECEIVEMESSAGELISTENER_H

#include <boost/shared_ptr.hpp>

namespace thewizardplusplus {
namespace city_client {

class ReceiveMessageListener {
public:
	typedef boost::shared_ptr<ReceiveMessageListener> SmartPointer;

	virtual ~ReceiveMessageListener(void);
	virtual void onReceiveMessage(const std::string& message) = 0;
};

}
}
#endif

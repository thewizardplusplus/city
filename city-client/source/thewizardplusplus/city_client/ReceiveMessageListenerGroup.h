#ifndef RECEIVEMESSAGELISTENERGROUP_H
#define RECEIVEMESSAGELISTENERGROUP_H

#include "ReceiveMessageListener.h"
#include <list>

namespace thewizardplusplus {
namespace city_client {

class ReceiveMessageListenerGroup {
public:
	typedef ReceiveMessageListener::SmartPointer Listener;

	bool has(const Listener& listener) const;
	void add(const Listener& listener);
	void remove(const Listener& listener);
	void process(const std::string& message);

private:
	typedef std::list<Listener> ListenerInnerGroup;

	ListenerInnerGroup listeners;
};

}
}
#endif

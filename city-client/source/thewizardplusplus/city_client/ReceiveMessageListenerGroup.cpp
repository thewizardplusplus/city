#include "ReceiveMessageListenerGroup.h"

using namespace thewizardplusplus::city_client;

typedef ReceiveMessageListenerGroup::Listener Listener;

bool ReceiveMessageListenerGroup::has(const Listener& listener) const {
	ListenerInnerGroup::const_iterator group_end = listeners.end();

	return std::find(listeners.begin(), group_end, listener) == group_end;
}

void ReceiveMessageListenerGroup::add(const Listener& listener) {
	if (!has(listener)) {
		listeners.push_back(listener);
	}
}

void ReceiveMessageListenerGroup::remove(const Listener& listener) {
	listeners.remove(listener);
}

void ReceiveMessageListenerGroup::process(const std::string& message) {
	ListenerInnerGroup::const_iterator i = listeners.begin();
	for (; i != listeners.end(); ++i) {
		i->get()->onReceiveMessage(message);
	}
}

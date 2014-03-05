#include "EventListenerFactory.h"
#include "EventListener.h"

EventListenerFactory::EventListenerFactory(DemoContext& demo_context) :
	demo_context(demo_context)
{}

Rocket::Core::EventListener* EventListenerFactory::InstanceEventListener(
	const Rocket::Core::String& value,
	Rocket::Core::Element* element
) {
	(void)element;
	return new EventListener(demo_context, value, element);
}

void EventListenerFactory::Release(void) {
	EventListenerGroup::const_iterator i = event_listeners.begin();
	for (; i != event_listeners.end(); ++i) {
		delete *i;
	}
}

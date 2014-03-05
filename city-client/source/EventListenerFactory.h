#ifndef EVENTLISTENERFACTORY_H
#define EVENTLISTENERFACTORY_H

#include "DemoContext.h"
#include <Rocket/Core/EventListenerInstancer.h>
#include <vector>

class EventListenerFactory : public Rocket::Core::EventListenerInstancer {
public:
	EventListenerFactory(DemoContext& demo_context);
	virtual Rocket::Core::EventListener* InstanceEventListener(
		const Rocket::Core::String& value,
		Rocket::Core::Element* element
	);
	virtual void Release(void);

private:
	typedef std::vector<Rocket::Core::EventListener*> EventListenerGroup;

	DemoContext& demo_context;
	EventListenerGroup event_listeners;
};
#endif

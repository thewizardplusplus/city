#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "DemoContext.h"
#include <Rocket/Core/EventListener.h>

class EventListener : public Rocket::Core::EventListener {
public:
	EventListener(
		DemoContext& demo_context,
		const Rocket::Core::String& event_name,
		Rocket::Core::Element* element
	);
	virtual void ProcessEvent(Rocket::Core::Event& event);

private:
	DemoContext& demo_context;
	Rocket::Core::String event_name;
	Rocket::Core::Element* element;
};
#endif

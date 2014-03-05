#include "EventListener.h"
#include <Rocket/Core/Element.h>
#include <cstdlib>

EventListener::EventListener(
	DemoContext& demo_context,
	const Rocket::Core::String& event_name,
	Rocket::Core::Element* element
) :
	demo_context(demo_context),
	event_name(event_name),
	element(element)
{}

void EventListener::ProcessEvent(Rocket::Core::Event& event) {
	(void)event;

	if (event_name == "switch-animation") {
		demo_context.animation = !demo_context.animation;
		if (demo_context.animation) {
			element->SetInnerRML("Stop animation");
		} else {
			element->SetInnerRML("Start animation");
		}
	} else if (event_name == "exit") {
		std::exit(EXIT_SUCCESS);
	}
}

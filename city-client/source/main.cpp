#include "SystemInterfaceSFML.h"
#include "RenderInterfaceSFML.h"
#include "ShellFileInterface.h"
#include "EventListenerFactory.h"
#include <SFML/Graphics.hpp>
#include <Rocket/Core.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>
#include <iostream>
#include <cmath>

int main(void) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test libRocket");

	RocketSFMLRenderer renderer;
	renderer.SetWindow(&window);
	Rocket::Core::SetRenderInterface(&renderer);

	RocketSFMLSystemInterface system_interface;
	Rocket::Core::SetSystemInterface(&system_interface);

	ShellFileInterface file_interface("");
	Rocket::Core::SetFileInterface(&file_interface);

	Rocket::Core::Initialise();

	DemoContext demo_context;
	EventListenerFactory* event_listener_factory = new EventListenerFactory(
		demo_context
	);
	Rocket::Core::Factory::RegisterEventListenerInstancer(
		event_listener_factory
	);

	Rocket::Core::Context* context = Rocket::Core::CreateContext(
		"default",
		Rocket::Core::Vector2i(window.GetWidth(), window.GetHeight())
	);
	if (context == NULL) {
		std::cerr << "Unable to create Rocket context.\n";
		std::exit(EXIT_FAILURE);
	}

	Rocket::Debugger::Initialise(context);

	Rocket::Core::ElementDocument* document = context->LoadDocument(
		"gui/gui.rml"
	);
	if (document != NULL) {
		document->Show();
		document->RemoveReference();
	};

	sf::Image image;
	bool image_loaded = image.LoadFromFile("moon.png");
	if (!image_loaded) {
		std::exit(EXIT_FAILURE);
	}

	sf::Sprite sprite;
	sprite.SetImage(image);
	sf::Vector2f sprite_size = sprite.GetSize();
	sprite.SetCenter(sprite_size.x / 2, sprite_size.y / 2);
	sprite.SetPosition(window.GetWidth() / 2, window.GetHeight() / 2);

	float time = 0.0f;
	while (window.IsOpened()) {
		sf::Event event;
		while (true) {
			bool event_got = window.GetEvent(event);
			if (!event_got) {
				break;
			}

			switch(event.Type) {
				case sf::Event::Resized:
					renderer.Resize();
					break;
				case sf::Event::MouseMoved:
					context->ProcessMouseMove(
						event.MouseMove.X,
						event.MouseMove.Y,
						system_interface.GetKeyModifiers(&window)
					);
					break;
				case sf::Event::MouseButtonPressed:
					context->ProcessMouseButtonDown(
						event.MouseButton.Button,
						system_interface.GetKeyModifiers(&window)
					);
					break;
				case sf::Event::MouseButtonReleased:
					context->ProcessMouseButtonUp(
						event.MouseButton.Button,
						system_interface.GetKeyModifiers(&window)
					);
					break;
				case sf::Event::MouseWheelMoved:
					context->ProcessMouseWheel(
						event.MouseWheel.Delta,
						system_interface.GetKeyModifiers(&window)
					);
					break;
				case sf::Event::TextEntered:
					if (event.Text.Unicode > 32) {
						context->ProcessTextInput(event.Text.Unicode);
					}
					break;
				case sf::Event::KeyPressed:
					context->ProcessKeyDown(
						system_interface.TranslateKey(event.Key.Code),
						system_interface.GetKeyModifiers(&window)
					);
					break;
				case sf::Event::KeyReleased:
					if (event.Key.Code == sf::Key::F8) {
						Rocket::Debugger::SetVisible(
							!Rocket::Debugger::IsVisible()
						);
					};

					context->ProcessKeyUp(
						system_interface.TranslateKey(event.Key.Code),
						system_interface.GetKeyModifiers(&window)
					);
					break;
				case sf::Event::Closed:
					window.Close();
					break;
				default:
					break;
			};
		}

		window.Clear();

		if (demo_context.animation) {
			float scale_factor = 1.0f * std::sin(time) + 1.5f;
			time += window.GetFrameTime();
			sprite.SetScale(scale_factor, scale_factor);
		}
		window.Draw(sprite);

		context->Render();

		window.Display();
	}
}

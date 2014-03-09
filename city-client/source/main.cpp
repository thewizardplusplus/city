#include "Level.h"
#include <boost/format.hpp>
#include <iostream>

int main(void) try {
	sf::RenderWindow window(
		sf::VideoMode(Entity::SIZE * 12, Entity::SIZE * 8),
		"Simple 2D game"
	);

	Level level("");
	level.setPosition(sf::Vector2i(-2, -2));
	while (window.IsOpened()) {
		sf::Event event;
		while (window.GetEvent(event)) {
			switch (event.Type) {
				case sf::Event::Closed:
					window.Close();
					break;
				default:
					break;
			}
		}

		window.Clear();
		level.render(window);
		window.Display();
	}
} catch (const std::exception& exception) {
	std::cerr << (boost::format("Error! %s\n") % exception.what()).str();
}

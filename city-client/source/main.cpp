#include "Level.h"
#include <boost/format.hpp>
#include <iostream>

int main(void) try {
	sf::RenderWindow window(
		sf::VideoMode(Entity::SIZE * 12, Entity::SIZE * 8),
		"Simple 2D game"
	);
	Level level("level.lvl");
	while (window.IsOpened()) {
		sf::Event event;
		while (window.GetEvent(event)) {
			switch (event.Type) {
				case sf::Event::Closed:
					window.Close();
					break;
				case sf::Event::KeyPressed:
					switch (event.Key.Code) {
						case sf::Key::Left:
							level.setPosition(
								level.getPosition() - sf::Vector2i(1, 0)
							);
							break;
						case sf::Key::Right:
							level.setPosition(
								level.getPosition() + sf::Vector2i(1, 0)
							);
							break;
						case sf::Key::Down:
							level.setPosition(
								level.getPosition() + sf::Vector2i(0, 1)
							);
							break;
						case sf::Key::Up:
							level.setPosition(
								level.getPosition() - sf::Vector2i(0, 1)
							);
							break;
						case sf::Key::Escape:
							window.Close();
							break;
						default:
							break;
					}
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

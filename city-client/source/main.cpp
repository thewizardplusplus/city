#include "VariableEntity.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <iostream>

int main(void) try {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Simple 2D game");

	Entity entity1("red_castle.png");
	entity1.setPosition(100, 100);
	ParameterizedEntity entity2("red_castle.png");
	entity2.setPosition(100, 200);
	StringGroup filenames;
	filenames.push_back("red_castle.png");
	filenames.push_back("green_castle.png");
	filenames.push_back("grey_castle.png");
	VariableEntity entity3(filenames);
	entity3.setPosition(100, 300);

	size_t tick = 0;
	while (window.IsOpened()) {
		sf::Event event;
		while (true) {
			bool event_got = window.GetEvent(event);
			if (!event_got) {
				break;
			}

			if (event.Type == sf::Event::Closed) {
				window.Close();
			}
		}

		window.Clear(sf::Color(0x22, 0x8b, 0x22));

		entity1.render(window);
		entity2.setParameter(boost::lexical_cast<std::string>(tick));
		entity2.render(window);
		entity3.setParameter(boost::lexical_cast<std::string>(tick));
		entity3.setState(tick % 3);
		entity3.render(window);

		window.Display();

		tick++;
		tick %= 100;
	}
} catch (const std::exception& exception) {
	std::cerr << (boost::format("Error! %s\n") % exception.what()).str();
}

#include "Sprite.h"
#include "Label.h"
#include <iostream>
#include <cmath>

int main(void) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Simple 2D game");

	Sprite moon("moon.png");
	sf::Vector2f sprite_size = moon.getSize();
	moon.setPosition(
		(window.GetWidth() - sprite_size.x) / 2,
		(window.GetHeight() - sprite_size.y) / 2
	);

	Label label(
		LabelStyle(
			FontFactory::getInstance().loadFont("braxton_font.otf"),
			sf::Color::White,
			50
		)
	);
	label.setText("Moon");
	label.setPosition(15, 0);

	float time = 0.0f;
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

		window.Clear();

		label.render(window);

		float scale_factor = 1.0f * std::sin(time) + 1.5f;
		time += window.GetFrameTime();
		sf::Vector2f new_sprite_size = scale_factor * sprite_size;
		moon.setSize(new_sprite_size);
		moon.render(window);

		window.Display();
	}
}

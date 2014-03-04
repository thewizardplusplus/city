#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main(void) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test SFML");

	sf::Font font;
	bool font_loaded = font.LoadFromFile("braxton_font.otf");
	if (!font_loaded) {
		std::exit(EXIT_FAILURE);
	}

	sf::String text("Moon", font, 50);
	text.SetColor(sf::Color::White);
	text.SetPosition(15, 0);

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

			if (
				event.Type == sf::Event::Closed
				|| (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Key::Escape)
			) {
				window.Close();
			}
		}

		window.Clear();

		window.Draw(text);

		float scale_factor = 1.0f * std::sin(time) + 1.5f;
		time += window.GetFrameTime();
		sprite.SetScale(scale_factor, scale_factor);
		window.Draw(sprite);

		window.Display();
	}
}

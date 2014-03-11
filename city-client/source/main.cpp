#include "Level.h"
#include <boost/format.hpp>
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

std::list<size_t> castle_ids = boost::assign::list_of<size_t>
	(6)(19)(31)(35)(44)(46)(47)(61)(70)(74)(75);
size_t first_player_id = 77;
size_t players_number = 12;

int main(void) try {
	sf::RenderWindow window(
		sf::VideoMode(Entity::SIZE * 12, Entity::SIZE * 8),
		"Simple 2D game"
	);

	Level level("level.lvl");
	BOOST_FOREACH(size_t castle_id, castle_ids) {
		level.setEntityParameter(
			castle_id,
			boost::lexical_cast<std::string>(std::rand() % 100)
		);
		level.setEntityState(castle_id, std::rand() % 3);
	}
	std::vector<sf::Vector2i> players_positions;
	players_positions.push_back(sf::Vector2i(1, 1));
	players_positions.push_back(sf::Vector2i(1, 3));
	players_positions.push_back(sf::Vector2i(1, 4));
	players_positions.push_back(sf::Vector2i(1, 5));
	players_positions.push_back(sf::Vector2i(1, 6));
	players_positions.push_back(sf::Vector2i(1, 10));
	players_positions.push_back(sf::Vector2i(2, 1));
	players_positions.push_back(sf::Vector2i(2, 2));
	players_positions.push_back(sf::Vector2i(2, 3));
	players_positions.push_back(sf::Vector2i(2, 4));
	players_positions.push_back(sf::Vector2i(2, 5));
	players_positions.push_back(sf::Vector2i(2, 8));
	players_positions.push_back(sf::Vector2i(2, 9));
	players_positions.push_back(sf::Vector2i(2, 10));
	players_positions.push_back(sf::Vector2i(3, 1));
	players_positions.push_back(sf::Vector2i(3, 2));
	players_positions.push_back(sf::Vector2i(3, 3));
	players_positions.push_back(sf::Vector2i(3, 5));
	players_positions.push_back(sf::Vector2i(3, 7));
	players_positions.push_back(sf::Vector2i(3, 9));
	players_positions.push_back(sf::Vector2i(3, 10));
	players_positions.push_back(sf::Vector2i(4, 2));
	players_positions.push_back(sf::Vector2i(4, 3));
	players_positions.push_back(sf::Vector2i(4, 4));
	players_positions.push_back(sf::Vector2i(4, 5));
	players_positions.push_back(sf::Vector2i(4, 10));
	players_positions.push_back(sf::Vector2i(5, 1));
	players_positions.push_back(sf::Vector2i(5, 2));
	players_positions.push_back(sf::Vector2i(5, 5));
	players_positions.push_back(sf::Vector2i(5, 6));
	players_positions.push_back(sf::Vector2i(5, 7));
	players_positions.push_back(sf::Vector2i(5, 8));
	players_positions.push_back(sf::Vector2i(5, 9));
	players_positions.push_back(sf::Vector2i(5, 10));
	players_positions.push_back(sf::Vector2i(6, 1));
	players_positions.push_back(sf::Vector2i(6, 2));
	players_positions.push_back(sf::Vector2i(6, 3));
	players_positions.push_back(sf::Vector2i(6, 5));
	players_positions.push_back(sf::Vector2i(6, 7));
	players_positions.push_back(sf::Vector2i(6, 8));
	players_positions.push_back(sf::Vector2i(6, 9));
	players_positions.push_back(sf::Vector2i(6, 10));
	players_positions.push_back(sf::Vector2i(7, 1));
	players_positions.push_back(sf::Vector2i(7, 3));
	players_positions.push_back(sf::Vector2i(7, 5));
	players_positions.push_back(sf::Vector2i(7, 9));
	players_positions.push_back(sf::Vector2i(8, 1));
	players_positions.push_back(sf::Vector2i(8, 3));
	players_positions.push_back(sf::Vector2i(8, 5));
	players_positions.push_back(sf::Vector2i(8, 6));
	players_positions.push_back(sf::Vector2i(8, 7));
	players_positions.push_back(sf::Vector2i(8, 9));
	players_positions.push_back(sf::Vector2i(9, 2));
	players_positions.push_back(sf::Vector2i(9, 4));
	players_positions.push_back(sf::Vector2i(9, 6));
	players_positions.push_back(sf::Vector2i(9, 8));
	players_positions.push_back(sf::Vector2i(9, 9));
	players_positions.push_back(sf::Vector2i(9, 10));
	players_positions.push_back(sf::Vector2i(10, 1));
	players_positions.push_back(sf::Vector2i(10, 2));
	players_positions.push_back(sf::Vector2i(10, 3));
	players_positions.push_back(sf::Vector2i(10, 4));
	players_positions.push_back(sf::Vector2i(10, 5));
	players_positions.push_back(sf::Vector2i(10, 6));
	players_positions.push_back(sf::Vector2i(10, 7));
	players_positions.push_back(sf::Vector2i(10, 8));
	players_positions.push_back(sf::Vector2i(10, 9));
	std::random_shuffle(players_positions.begin(), players_positions.end());
	players_positions.resize(players_number);
	for (size_t i = 0; i < players_number; ++i) {
		size_t player_id = first_player_id + i;
		level.addPlayer(player_id);
		level.setEntityParameter(
			player_id,
			boost::lexical_cast<std::string>(std::rand() % 100)
		);
		level.setEntityState(player_id, std::rand() % 2);
		level.setPlayerPosition(player_id, players_positions[i]);
	}

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

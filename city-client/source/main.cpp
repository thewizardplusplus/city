#include "Connection.h"
#include "Level.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace boost;
using namespace boost::algorithm;
using namespace boost::posix_time;
using namespace boost::this_thread;

const int LEVEL_WIDTH = 12;
const int LEVEL_HEIGHT = 8;

void CleanerThreadFunction(
	const ConnectionSmartPointer& connection,
	const LevelSmartPointer& level
) {
	while (true) {
		std::string world_description = connection->request(
			(format("w:%u") % level->getPlayerId()).str()
		);
		std::cerr << world_description << '\n';

		level->removeAllPlayer();

		std::vector<std::string> players;
		split(players, world_description, is_any_of(";"));
		BOOST_FOREACH(std::string player_decription, players) {
			std::vector<std::string> player_data;
			split(player_data, player_decription, is_any_of(":"));

			size_t player_id = lexical_cast<size_t>(player_data[0]);
			//level->addPlayer(player_id);
			level->setEntityState(player_id, player_id != level->getPlayerId());
			sf::Vector2i position(
				lexical_cast<int>(player_data[1]),
				lexical_cast<int>(player_data[2])
			);
			if (player_id != level->getPlayerId()) {
				level->setPlayerPosition(player_id, position);
			} else {
				level->setPosition(
					position - sf::Vector2i(LEVEL_WIDTH, LEVEL_HEIGHT) / 2
				);
			}
		}
	}
}

void StartCleanerThread(
	const ConnectionSmartPointer& connection,
	const LevelSmartPointer& level
) {
	new thread(CleanerThreadFunction, connection, level);
}

int main(void) try {
	sf::RenderWindow window(
		sf::VideoMode(Entity::SIZE * LEVEL_WIDTH, Entity::SIZE * LEVEL_HEIGHT),
		"2D RTS"
	);

	ConnectionSmartPointer connection(new Connection());
	size_t player_id = lexical_cast<size_t>(connection->request("r"));

	LevelSmartPointer level(new Level(player_id, "level.lvl"));
	StartCleanerThread(connection, level);
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
							connection->request(
								(format("m:%u:%i") % player_id % 3).str()
							);
							break;
						case sf::Key::Right:
							connection->request(
								(format("m:%u:%i") % player_id % 1).str()
							);
							break;
						case sf::Key::Down:
							connection->request(
								(format("m:%u:%i") % player_id % 2).str()
							);
							break;
						case sf::Key::Up:
							connection->request(
								(format("m:%u:%i") % player_id % 0).str()
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
		level->render(window);
		window.Display();
	}
} catch (const std::exception& exception) {
	std::cerr << (boost::format("Error! %s\n") % exception.what()).str();
}

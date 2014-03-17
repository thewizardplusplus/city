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
		level->update(world_description);
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

	LevelSmartPointer level(
		new Level(
			player_id,
			sf::Vector2i(LEVEL_WIDTH, LEVEL_HEIGHT),
			"level.lvl"
		)
	);
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

#ifndef LEVEL_H
#define LEVEL_H

#include "Sprite.h"
#include "Entity.h"
#include "VariableEntity.h"
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <vector>

enum SpriteNames {
	SPRITE_TREE,
	SPRITE_MOUNTAIN,
	SPRITE_CASTLE,
	SPRITE_GREEN_PLAYER,
	SPRITE_RED_PLAYER
};

typedef std::map<SpriteNames, SpriteSmartPointer> SpriteGroup;
typedef std::vector<EntitySmartPointer> EntityGroup;
typedef std::map<size_t, VariableEntitySmartPointer> VariableEntityGroup;

class Level {
public:
	static const boost::regex LEVEL_FILE_LINE_PATTERN;
	static const sf::Color BACKGROUND_COLOR;
	static const float GRID_THICKNESS;
	static const sf::Color GRID_COLOR;

	Level(
		size_t player_id,
		const sf::Vector2i& visual_size,
		const std::string& filename
	);
	size_t getPlayerId(void);
	void update(const std::string& description);
	void render(sf::RenderWindow& render);

private:
	SpriteGroup sprites;
	sf::String label;
	size_t player_id;
	sf::Vector2i visual_size;
	sf::Vector2i position;
	EntityGroup trees;
	EntityGroup mountains;
	VariableEntityGroup castles;
	VariableEntityGroup players;
	boost::mutex mutex;

	void setEntityState(size_t id, size_t state);
	void setPlayerPosition(size_t id, const sf::Vector2i& position);
};

typedef boost::shared_ptr<Level> LevelSmartPointer;
#endif

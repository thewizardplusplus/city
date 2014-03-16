#ifndef LEVEL_H
#define LEVEL_H

#include "Entity.h"
#include "VariableEntity.h"
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

typedef std::vector<Entity::Pointer> EntityGroup;
typedef std::map<size_t, VariableEntity::Pointer> VariableEntityGroup;

class Level {
public:
	static const boost::regex LEVEL_FILE_LINE_PATTERN;
	static const sf::Color BACKGROUND_COLOR;
	static const float GRID_THICKNESS;
	static const sf::Color GRID_COLOR;

	Level(const std::string& filename);
	void setEntityState(size_t id, size_t state);
	void addPlayer(size_t id);
	void setPlayerPosition(size_t id, const sf::Vector2i& position);
	void removeAllPlayer(void);
	void render(sf::RenderWindow& render);

private:
	sf::Vector2i position;
	EntityGroup entities;
	VariableEntityGroup castles;
	VariableEntityGroup players;
	boost::mutex mutex;
};

typedef boost::shared_ptr<Level> LevelSmartPointer;
#endif

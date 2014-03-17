#ifndef VARIABLEENTITY_H
#define VARIABLEENTITY_H

#include "Entity.h"
#include "Sprite.h"
#include <list>
#include <vector>

typedef std::list<std::string> StringGroup;
typedef std::vector<SpriteSmartPointer> SpriteVector;

class VariableEntity : public Entity {
public:
	VariableEntity(size_t id, const StringGroup& sprites_filenames);
	size_t getState(void) const;
	void setState(size_t state);
	virtual void render(sf::RenderWindow& render);

private:
	SpriteVector sprites;
	size_t state;
};

typedef boost::shared_ptr<VariableEntity> VariableEntitySmartPointer;
#endif

#ifndef VARIABLEENTITY_H
#define VARIABLEENTITY_H

#include "ParameterizedEntity.h"
#include <vector>

typedef std::vector<std::string> StringGroup;
typedef std::vector<Sprite> SpriteGroup;

class VariableEntity : public ParameterizedEntity {
public:
	typedef boost::shared_ptr<VariableEntity> Pointer;

	using ParameterizedEntity::setPosition;

	VariableEntity(size_t id, const StringGroup& sprites_filenames);
	size_t getState(void) const;
	void setState(size_t state);
	virtual void setPosition(const sf::Vector2i& position);
	virtual void render(sf::RenderWindow& render);

private:
	SpriteGroup sprites;
	size_t state;

	void updateSpritesPosition(void);
};
#endif

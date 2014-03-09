#ifndef PARAMETERIZEDENTITY_H
#define PARAMETERIZEDENTITY_H

#include "Entity.h"
#include "Label.h"

class ParameterizedEntity : public Entity {
public:
	typedef boost::shared_ptr<ParameterizedEntity> Pointer;

	using Entity::setPosition;

	static const float PARAMETER_LABEL_SHIFT;
	static const LabelStyle PARAMETER_LABEL_STYLE;

	ParameterizedEntity(size_t id, const std::string& sprite_filename);
	std::string getParameter(void) const;
	void setParameter(const std::string& parameter);
	virtual void setPosition(const sf::Vector2i& position);
	virtual void render(sf::RenderWindow& render);

protected:
	Label label;

	void updateParameterPosition(void);
};
#endif

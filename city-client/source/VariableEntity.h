#ifndef VARIABLEENTITY_H
#define VARIABLEENTITY_H

#include "Entity.h"

class VariableEntity : public Entity {
public:
	VariableEntity(size_t id, size_t states_number);
	std::string getParameter(void) const;
	void setParameter(const std::string& value);
	size_t getState(void) const;
	void setState(size_t state);

private:
	size_t states_number;
	std::string parameter;
	size_t state;
};

typedef boost::shared_ptr<VariableEntity> VariableEntitySmartPointer;
#endif

#include "VariableEntity.h"
#include <stdexcept>

VariableEntity::VariableEntity(
	size_t id,
	size_t states_number
) :
	Entity(id),
	states_number(states_number),
	state(0)
{
	if (states_number == 0) {
		throw std::runtime_error(
			"Must not create VariableEntity with null states number."
		);
	}
}

size_t VariableEntity::getState(void) const {
	return state;
}

void VariableEntity::setState(size_t state) {
	if (state < states_number) {
		this->state = state;
	} else {
		throw std::runtime_error("Invalid state of VariableEntity.");
	}
}

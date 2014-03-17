#ifndef SPRITEFACTORY_H
#define SPRITEFACTORY_H

#include "Sprite.h"
#include <map>

typedef std::map<std::string, SpriteSmartPointer> SpriteMap;

class SpriteFactory {
public:
	static SpriteFactory& getInstance(void);

	SpriteSmartPointer loadSprite(const std::string& filename);

private:
	SpriteMap sprites;

	SpriteFactory(void);
	SpriteFactory(const SpriteFactory& sample);
	SpriteFactory& operator=(const SpriteFactory& sample);
};
#endif

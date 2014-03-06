#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

typedef boost::shared_ptr<sf::Image> Texture;
typedef std::map<std::string, Texture> TextureGroup;

class TextureFactory {
public:
	static TextureFactory& getInstance(void);

	Texture loadTexture(const std::string& filename);

private:
	TextureGroup textures;

	TextureFactory(void);
	TextureFactory(const TextureFactory& sample);
	TextureFactory& operator=(const TextureFactory& sample);
};
#endif

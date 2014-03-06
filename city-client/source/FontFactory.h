#ifndef FONTFACTORY_H
#define FONTFACTORY_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

typedef boost::shared_ptr<sf::Font> Font;
typedef std::map<std::string, Font> FontGroup;

class FontFactory {
public:
	static FontFactory& getInstance(void);

	Font loadFont(const std::string& filename);

private:
	FontGroup fonts;

	FontFactory(void);
	FontFactory(const FontFactory& sample);
	FontFactory& operator=(const FontFactory& sample);
};
#endif

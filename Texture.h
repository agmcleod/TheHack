#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#ifndef __TheHack_Texture__
#define __TheHack_Texture__

struct Region {
    std::string name;
    sf::Vector2f pos;
    float width;
    float height;
};

class Texture {
public:
	Texture(GLuint textureId, float width, float height) : textureId(textureId), width(width), height(height) {}
    void cleanup();
	GLuint getTextureId();
    Region * getRegion(const std::string &name);
	float getWidth();
	float getHeight();
    void readRegionsFromFile(const std::string &fileName);
private:
	GLuint textureId;
	float width;
	float height;
    std::vector<Region *> regions;
};

#endif
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#ifndef __TheHack_Texture__
#define __TheHack_Texture__
class Texture {
public:
	Texture(GLuint textureId, float originWidth, float originHeight, float width, float height, sf::Vector2f pos) : textureId(textureId), originWidth(originWidth), originHeight(originHeight), width(width), height(height), pos(pos) {}
	GLuint getTextureId();
	float getOriginWidth();
	float getOriginHeight();
	float getWidth();
	float getHeight();
	sf::Vector2f &getPos();
private:
	GLuint textureId;
	float originWidth;
	float originHeight;
	float width;
	float height;
	sf::Vector2f pos;
};

#endif
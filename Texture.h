#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#ifndef __TheHack_Texture__
#define __TheHack_Texture__
struct Texture
{
	GLuint textureId;
	float originWidth;
	float originHeight;
	float width;
	float height;
	sf::Vector2f pos;
};

#endif
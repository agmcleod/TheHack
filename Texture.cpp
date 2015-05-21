#include "Texture.h"

GLuint Texture::getTextureId() {
	return textureId;
}

float Texture::getOriginWidth() {
	return originWidth;
}
float Texture::getOriginHeight() {
	return originHeight;
}
float Texture::getWidth() {
	return width;
}
float Texture::getHeight() {
	return height;
}
sf::Vector2f & Texture::getPos() {
	return pos;
}
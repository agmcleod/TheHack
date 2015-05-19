#ifndef __TheHack_Renderer__
#define __TheHack_Renderer__

#define GLEW_STATIC
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"

class Renderer {
public:
	Renderer(float width, float height);
	void beginFrame();
	GLuint bindTexture(sf::Image &image);
	void cleanup();
	void compileProgram(const GLchar *vertex, const GLchar *fragment, GLuint &vertexShader, GLuint &fragmentShader, GLuint &shaderProgram);
	void renderTexture(sf::FloatRect &bounds, Texture &texture);
	void setupBuffers();
	void setupShader();
private:
	GLuint ebo;
	GLuint fragmentShader;
	glm::mat4 projection;
	GLuint shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLuint vertexShader;
};

#endif
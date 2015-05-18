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

class Renderer {
public:
	Renderer(float width, float height);
	void beginFrame();
	void cleanup();
	void compileProgram(const GLchar *vertex, const GLchar *fragment, GLuint &vertexShader, GLuint &fragmentShader, GLuint &shaderProgram);
	void setupBuffers();
	void setupShader();
private:
	GLuint ebo;
	GLuint fragmentShader;
	glm::mat4 modelMatrix;
	glm::mat4 projection;
	GLuint shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLuint vertexShader;
};

#endif
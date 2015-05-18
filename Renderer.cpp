#include "Renderer.h"
#include <iostream>

Renderer::Renderer(float width, float height) {
	glewExperimental = true;
	glewInit();
	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setupShader();
	glUseProgram(shaderProgram);
	projection = glm::ortho(0.0f, width, height, 0.0f);


}

void Renderer::beginFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::cleanup() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

void Renderer::compileProgram(const GLchar *vertex, const GLchar *fragment, GLuint &vertexShader, GLuint &fragmentShader, GLuint &shaderProgram) {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer << std::endl;
		assert(false);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer << std::endl;
		assert(false);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, buffer);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << buffer << std::endl;
	}
}

void Renderer::setupShader() {
	const GLchar *vertex =
	"#version 150 core\n\
	in vec2 position;\n\
	in vec3 color;\n\
	in vec2 texcoord;\n\
	out vec3 Color;\n\
	out vec2 Texcoord;\n\
	uniform mat4 projection;\n\
	uniform mat4 mMatrix;\n\
	void main() {\n\
		Color = color;\n\
		Texcoord = texcoord;\n\
		gl_Position = projection * mMatrix * vec4(position.xy, 0.0, 1.0);\n\
	}";

	const GLchar *fragment =
	"#version 150 core\n\
	in vec3 Color;\n\
	in vec2 Texcoord;\n\
	out vec4 outColor;\n\
	uniform sampler2D tex;\n\
	void main() {\n\
		outColor = texture(tex, Texcoord) * vec4(Color, 1.0);\n\
	}";

	compileProgram(vertex, fragment, vertexShader, fragmentShader, shaderProgram);
}
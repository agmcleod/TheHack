#include "Renderer.h"
#include <iostream>

#include "ResolvePath.h"

Renderer::Renderer(float width, float height) {
	glewExperimental = true;
	glewInit();
	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setupShader();
	setupBuffers();

	glUseProgram(shaderProgram);
	projection = glm::ortho(0.0f, width, height, 0.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

GLuint Renderer::bindTexture(sf::Image &image) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
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

void Renderer::renderTexture(sf::FloatRect &bounds, Texture &texture, const std::string &regionName) {
    
    Region *region = texture.getRegion(regionName);
    if (region != nullptr) {
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(bounds.left, bounds.top, 0.0f));
        model = glm::scale(model, glm::vec3(bounds.width, bounds.height, 0.0f));
        GLint modelMat = glGetUniformLocation(shaderProgram, "mMatrix");
        glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(model));
        
        float x = region->pos.x / texture.getWidth();
        float y = region->pos.y / texture.getHeight();
        float rx = (region->width + region->pos.x) / texture.getWidth();
        float ry = (region->height + region->pos.y) / texture.getHeight();
        GLfloat vertices[] = {
            //  Position(2) Color(3)     Texcoords(2)
            0.0f, 0.0f, 1.0f, 1.0f, 1.0f, x, y, // Top-left
            1.0f, 0.0f, 1.0f, 1.0f, 1.0f, rx, y, // Top-right
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f, rx, ry, // Bottom-right
            0.0f, 1.0f, 1.0f, 1.0f, 1.0f, x, ry  // Bottom-left
        };
        
        glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
        glBindVertexArray(vao);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    else {
        // std::cout << "Could not find region by: " << regionName << std::endl;
    }
	
}

void Renderer::setupBuffers() {
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat vertices[] = {
		//  Position(2) Color(3)     Texcoords(2)
		0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
		1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	glBindVertexArray(0);
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
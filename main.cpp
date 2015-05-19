#include <stdio.h>

#include "Renderer.h"
#include "Texture.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>

#ifdef __APPLE__
#include "ResourcePath.hpp"
#elif _WIN32
inline std::string resourcePath() { return ""; }
#include <Windows.h>
#elif _WIN64
inline std::string resourcePath() { return ""; }
#include <Windows.h>
#endif

int main() {
	sf::ContextSettings settings;
	settings.minorVersion = 2;
	settings.majorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;
	sf::Window window(sf::VideoMode(800, 600), "Hack", sf::Style::Default, settings);

	sf::Clock clock = sf::Clock();
	Renderer renderer(800, 600);

	sf::Image roomOneTexture;
	std::string imagePath = resourcePath() + "atlas.png";
	if (!roomOneTexture.loadFromFile(imagePath)) {
		return EXIT_FAILURE;
	}

	Texture roomOne;
	roomOne.textureId = renderer.bindTexture(roomOneTexture);
	roomOne.width = 800.0f;
	roomOne.height = 600.0f;
	roomOne.pos = sf::Vector2f(2, 2);
	roomOne.originWidth = roomOneTexture.getSize().x;
	roomOne.originHeight = roomOneTexture.getSize().y;

	InputManager input;
	sf::FloatRect bounds(0.0f, 0.0f, 800.0f, 600.0f);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					renderer.cleanup();
					window.close();
				}
				else {
					input.captureKey(event.key.code);
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				input.releaseKey(event.key.code);
			}
		}

		renderer.beginFrame();
		renderer.renderTexture(bounds, roomOne);

		const float time = clock.getElapsedTime().asSeconds();

		clock.restart();

		window.display();
	}

	return 0;
}
#include <stdio.h>

#include "Renderer.h"
#include "Texture.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>

#include "ResolvePath.h"
#if _WIN32
#include <Windows.h>
#elif _WIN64
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

	Texture atlas(renderer.bindTexture(roomOneTexture), roomOneTexture.getSize().x, roomOneTexture.getSize().y);
    atlas.readRegionsFromFile("atlas.json");

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
		renderer.renderTexture(bounds, atlas, "RoomOne.png");

		clock.restart();

		window.display();
	}
    
    atlas.cleanup();

	return 0;
}
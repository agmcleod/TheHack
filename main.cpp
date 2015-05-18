#include <stdio.h>

#include "Renderer.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>

#ifdef _WIN32
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

	InputManager input;

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

		const float time = clock.getElapsedTime().asSeconds();

		clock.restart();

		window.display();
	}

	return 0;
}
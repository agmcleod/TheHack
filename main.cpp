#include <stdio.h>

#include "Renderer.h"
#include "Box2DRenderer.h"
#include "Texture.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include "ResolvePath.h"
#if _WIN32
#include <Windows.h>
#elif _WIN64
#include <Windows.h>
#endif

#include "Player.h"

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
    input.bindAction(sf::Keyboard::Key::W, "up");
    input.bindAction(sf::Keyboard::Key::A, "left");
    input.bindAction(sf::Keyboard::Key::D, "right");
    input.bindAction(sf::Keyboard::Key::S, "down");
	sf::FloatRect bounds(0.0f, 0.0f, 800.0f, 600.0f);
    
    b2Vec2 gravity(0, 0);
    b2World world(gravity);
    
    Box2DRenderer box2dRenderer;
    box2dRenderer.setRenderer(&renderer);
    box2dRenderer.SetFlags(b2Draw::e_shapeBit);
    world.SetDebugDraw(&box2dRenderer);
    
    float32 timeStep = 1.0f / 60.0f;
    
    Player player(world, atlas);

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
        
        float time = clock.getElapsedTime().asSeconds();
        
        player.update(input, time);
        world.Step(timeStep, 6, 2);
        
        clock.restart();

		renderer.beginFrame();
		renderer.renderTexture(bounds, atlas, "RoomOne.png");
        player.render(renderer);
        world.DrawDebugData();
		window.display();
	}
    
    atlas.cleanup();

	return 0;
}
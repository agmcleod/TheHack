#ifndef __TheHack_InputManager__
#define __TheHack_InputManager__

#include <stdio.h>
#include <map>
#include <utility>
#include <SFML/Graphics.hpp>

class InputManager {
public:
	InputManager() {}
	void bindAction(sf::Keyboard::Key &key, std::string actionName);
	void captureKey(sf::Keyboard::Key &key);
	void releaseKey(sf::Keyboard::Key &key);

	bool isActionPressed(std::string action);
private:
	std::map<sf::Keyboard::Key, std::string> m_map;
	std::map<std::string, bool> m_actions;
};

#endif

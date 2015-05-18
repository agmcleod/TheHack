#include "InputManager.h"

void InputManager::bindAction(sf::Keyboard::Key &key, std::string action) {
	m_map.insert(std::make_pair(key, action));
	m_actions.insert(std::make_pair(action, false));
}

void InputManager::captureKey(sf::Keyboard::Key &key) {
	m_actions[m_map[key]] = true;
}

bool InputManager::isActionPressed(std::string action) {
	return m_actions[action];
}

void InputManager::releaseKey(sf::Keyboard::Key &key) {
	m_actions[m_map[key]] = false;
}
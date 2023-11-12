#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class HUDManager
{
public:
	HUDManager();
	static sf::View GetHud() { return hudView; }
	static void AddGameObjectHud(GameObject* _gameObject) { hudGameObjects.push_back(_gameObject); }
	static void Preload();
	static sf::Vector2f GetSquareCenter(std::string _key) { return centerSquare.at(_key); }
	static GameObject* GetHudGameObject(int _index) { return hudGameObjects[_index]; }
	static std::vector<GameObject* > GetHudGameObjects() { return hudGameObjects; }

private:
	static sf::View hudView;
	static std::vector<sf::Vector2f> column;
	static std::vector<sf::Vector2f> line;
	static std::map<std::string, sf::Vector2f> centerSquare;
	static std::vector<GameObject* > hudGameObjects;
};


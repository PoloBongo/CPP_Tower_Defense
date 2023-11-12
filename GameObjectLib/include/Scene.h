#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Components/Entities/Player.h"
#include "Components/Inputs/InputGame.h"


class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	Scene(sf::RenderWindow* _window);

	virtual void Create();
	virtual void Delete();
	virtual void Update(sf::Time _delta);
	virtual void Render(sf::RenderWindow* _window);

	virtual void Awake();

	void RemoveGameObject(GameObject* objectToRemove) {
		gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
			[objectToRemove](GameObject* obj) {
				return obj == objectToRemove;
			}), gameObjects.end());
	}

	GameObject* GetGameObject(std::string objectName) 
	{
		for (GameObject* gameObject : gameObjects) {
			if (gameObject->GetName() == objectName) {
				return gameObject;
			}
		}
		return nullptr;
	}

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool _state);


	GameObject* CreateGameObject(const std::string& _name);

	//GAME ELEMENT
	GameObject* CreateDecorObject(const std::string& name, float x, float y, float scaleX, float scaleY, const sf::Texture texture);

	GameObject* CreateButtonGameObject(const std::string& name, float x, float y, unsigned int fontSize);
	GameObject* CreatePlatformObject(const std::string& name, float x, float y, float scaleX, float scaleY, const sf::Texture texture, sf::IntRect* _rectSource);

	GameObject* CreateBackgroundGameObject(const std::string& name, float x, float y, sf::Texture texture);
	GameObject* CreateInputGameObject(std::string _name, float _x, float _y);

	GameObject* CreateSliderGameObject(const std::string& name, float x, float y, float _widthBar, float _heightBar, float _widthCursor, float _heightCursor, unsigned int _fontSize, float _data, float _maxData);
	GameObject* CreateSliderGameObject(const std::string& name, float x, float y, float _widthBar, float _heightBar, float _widthCursor, float _heightCursor, unsigned int _fontSize, float _data, float _minData, float _maxData);

protected:
	InputGame* inputGame = nullptr;
	std::vector<GameObject*> gameObjects;
	sf::RenderWindow* window;	 
	bool isActive = true;
};

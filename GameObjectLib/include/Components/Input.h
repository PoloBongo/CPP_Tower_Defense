#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Scene.h"



class Input : public Component
{

public:
	Input();

	void SetInput(unsigned int fontSize);
	void SetOrigin();
	void SetSize(float _width, float _height);
	void SetPosition(float _x, float _y);

	void Render(sf::RenderWindow* _window) override;
	bool IsClicked();
	void Update(sf::Time _delta) override;

	~Input();

private:
	float width, height;
	sf::Font font;
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::FloatRect textBounds;
	bool isEnteringText = false;
	sf::RenderWindow* window = nullptr;
};


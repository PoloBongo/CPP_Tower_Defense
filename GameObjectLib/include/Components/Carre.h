#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Scene.h"
class Carre : public Component
{

public:
	Carre();

	bool IsClicked();

	void Render(sf::RenderWindow* _window) override;
	void SetCarre();
	void SetOrigin();
	void SetSize(float _width, float _height);
	void SetPosition(float _x, float _y);

private:
	float width, height;
	bool clicked = false;
	sf::RectangleShape carre;
};


#include "Components/Carre.h"
#include "WindowManager.h"
#include "CameraManager.h"

Carre::Carre() {
	this->clicked = false;
	this->height = 0;
	this->width = 0;
}

void Carre::Render(sf::RenderWindow* _window) {
	Component::Render(_window);
	const auto position = GetOwner()->GetPosition();
	carre.setPosition(position.x, position.y);
	_window->setView(CameraManager::GetView());
	_window->draw(carre);
}


bool Carre::IsClicked() 
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*WindowManager::GetWindow());
	sf::Vector2f worldPos = WindowManager::GetWindow()->mapPixelToCoords(mousePos, CameraManager::GetView());
	return carre.getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !clicked;
}


void Carre::SetCarre()
{
	carre.setSize(sf::Vector2f(width, height));
	carre.setOutlineThickness(2);
	carre.setOutlineColor(sf::Color::Black);
	carre.setFillColor(sf::Color::Yellow);
}

void Carre::SetOrigin() 
{
	carre.setOrigin(sf::Vector2f(width / 2, height / 2));
}

void Carre::SetSize(float _width, float _height) 
{
	width = _width;
	height = _height;
}

void Carre::SetPosition(float _x, float _y) 
{
	carre.setPosition(_x, _y);
}
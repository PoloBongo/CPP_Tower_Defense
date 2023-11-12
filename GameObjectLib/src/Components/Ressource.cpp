#include "Components/Ressource.h"
#include "HUDManager.h"
#include "CameraManager.h"
#include <iostream>

void Ressource::Update(sf::Time _delta)
{
}

void Ressource::SetText()
{
	goldText.setFont(font);
	goldText.setString(std::to_string((int)GetGold()));
	goldText.setCharacterSize(24);
	goldText.setFillColor(sf::Color::Yellow);
	goldText.setStyle(sf::Text::Bold);

	manaText.setFont(font);
	manaText.setString(std::to_string((int)GetMana()));
	manaText.setCharacterSize(24);
	manaText.setFillColor(sf::Color::Blue);
	manaText.setStyle(sf::Text::Bold);
}

void Ressource::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	if (!font.loadFromFile("../Fonts/Roboto-Medium.ttf"))
	{
		std::cout << "fonts pas charge";
	}


	goldText.setString(std::to_string((int)GetGold()) + " Gold");
	manaText.setString(std::to_string((int)GetMana()) + " Mana");
	goldText.setPosition(150.0f, 50.0f);
	manaText.setPosition(300.0f, 50.0f);

	_window->setView(HUDManager::GetHud());
	_window->draw(goldText);
	_window->draw(manaText);
	_window->setView(CameraManager::GetView());
}


#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
class Ressource: public Component
{
public:
	void SetText();

	void Update(sf::Time _delta) override;
	void Render(sf::RenderWindow* _window) override;

	void AddGold(float _value) { gold += _value; }
	void SetGold(float _value){ gold = _value; }
	float GetGold() { return gold; }
	
	void AddMana(float _value) { mana += _value; }
	void SetMana(float _value) { mana = _value; }
	float GetMana() { return mana; }

	void SetMaxMana(float _value) { maxMana = _value; }
	float GetMaxMana() { return maxMana; }

private: 
	float gold;
	float mana;

	float maxMana = 200.f;

	sf::Text goldText;
	sf::Text manaText;
	sf::Font font;

};


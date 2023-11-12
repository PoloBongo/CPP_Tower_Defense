#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Command
{
public:
	Command();
	Command(GameObject* _entity);
	~Command();
	virtual void Execute(sf::Time delta) = 0;

protected:
	GameObject* entity;
};


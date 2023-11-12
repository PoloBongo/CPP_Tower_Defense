#pragma once

#include <SFML/Graphics.hpp>
class EventManager
{
public:

	static void Update(sf::Time _delta);
	static sf::Event GetEvent() { return event; }
	static void SetEvent(sf::Event& _event) { event = _event; }

private:
	static sf::Event event;
};


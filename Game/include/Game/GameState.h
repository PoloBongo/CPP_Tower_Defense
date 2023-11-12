#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
	GameState(sf::RenderWindow* _window, int _FPS);
	sf::Clock GetClock() const { return clock; }


	void Preload();
	void Update();
	void Create();

	void PreloadScenes();
	void PreloadAssets();
	void PreloadAudio();

	~GameState();

private:
	int FPS;
	sf::Clock clock;
	sf::Event event;
	sf::RenderWindow* window;
};


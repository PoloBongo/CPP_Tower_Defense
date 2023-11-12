#pragma once
#include <SFML/Graphics.hpp>

class WindowManager
{
public:

	static int GetFps() { return fps; }
	static int GetMaxFps() { return maxFps; }
	static int GetMinFps() { return minFps; }
	static void SetFps(int _fps) { fps = _fps; }
	static void SetMinFps(int& _minFps) { minFps = _minFps; }
	static void SetMaxFps(int& _maxFps) { maxFps = _maxFps; }

	static sf::RenderWindow* GetWindow() { return window; }
	static void SetWindow(sf::RenderWindow* _window) { window = _window; }
	static int GetWindowWidth() { return window->getSize().x; }
	static int GetWindowHeight() { return window->getSize().y; }

private:
	static sf::RenderWindow* window;
	static int fps;
	static int minFps;
	static int maxFps; 
};


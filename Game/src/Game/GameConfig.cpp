#include "Game/GameConfig.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "WindowManager.h"


GameConfig::GameConfig() {
	this->FPS = 240;
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "RAMBO", sf::Style::Fullscreen);
	WindowManager::SetWindow(this->window);
	WindowManager::SetFps(this->FPS);
}

GameConfig::~GameConfig() {
	delete this->window;
}

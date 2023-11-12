#include "WindowManager.h"


int WindowManager::fps = 60;
int WindowManager::minFps = 30;
int WindowManager::maxFps = 240;
sf::RenderWindow* WindowManager::window = nullptr;
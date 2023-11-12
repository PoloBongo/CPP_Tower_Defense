#include "HUDManager.h"
#include "WindowManager.h"

 sf::View HUDManager::hudView;
 std::vector<GameObject* > HUDManager::hudGameObjects;

std::vector<sf::Vector2f> HUDManager::line;
std::vector<sf::Vector2f> HUDManager::column;
std::map<std::string, sf::Vector2f> HUDManager::centerSquare;


HUDManager::HUDManager() {

}

void HUDManager::Preload() {
	int width = WindowManager::GetWindowWidth();
	int height = WindowManager::GetWindowHeight();
	HUDManager::hudView.setSize(width, height);
	HUDManager::hudView.setCenter(width / 2, height / 2);
	for (int i = 0; i < 16; i++) {
		HUDManager::column.push_back(sf::Vector2f(width / 16 * i, width / 16 * (i + 1)));
	}
	for (int i = 0; i < 9; i++) {
		HUDManager::line.push_back(sf::Vector2f(height / 9 * i, height / 9 * (i + 1)));
	}
	int j = 0;
	for (sf::Vector2f column_ : HUDManager::column) {
		for (sf::Vector2f line_ : HUDManager::line) {
			HUDManager::centerSquare.insert(std::make_pair(std::to_string(j), sf::Vector2f(column_.x + (column_.y - column_.x) / 2, line_.x + (line_.y - line_.x) / 2)));
			j++;
		}
	}

	WindowManager::GetWindow()->setView(HUDManager::hudView);
}
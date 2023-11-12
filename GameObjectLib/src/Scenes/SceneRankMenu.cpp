#include "Scenes/SceneRankMenu.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "Components/Button.h"
#include "AssetManager.h"

SceneRankMenu::SceneRankMenu(sf::RenderWindow* _window) : Scene(_window) {
	this->Awake();
	Scene::Create();
}

void SceneRankMenu::Create() {
	Scene::Create();
	sf::Texture backgroundTexture2;

	if (!backgroundTexture2.loadFromFile("../assets/Sprite_LOL/background/background2_lol.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background2 = CreateBackgroundGameObject("Background2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture2);
	this->CreateSceneButtonsMenu();
}

void SceneRankMenu::Render(sf::RenderWindow* _window) {
	Scene::Render(_window);
}

void SceneRankMenu::CreateSceneButtonsMenu() {
	float widthScreen = WindowManager::GetWindow()->getSize().x;
	float heightScreen = WindowManager::GetWindow()->getSize().y;
	rankButton = CreateButtonGameObject("Rank", widthScreen / 2, heightScreen / 13, 50);
	backButton = CreateButtonGameObject("Retour", widthScreen / 15, heightScreen / 13, 20);

	sf::Texture TextureTrophee;

	if (!TextureTrophee.loadFromFile("../assets/Sprite/trophee.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}

	for (int i = 1; i <= 10; i++)
	{
		listRank = CreateButtonGameObject("Rank " + std::to_string(i), widthScreen / 2, heightScreen / 11 + i * 95, 27);
		float posX = listRank->GetPosition().x;
		float posY = listRank->GetPosition().y;
		GameObject* imagesRank = CreateDecorObject("TextureTrophee1", posX * 0.94, posY * 1.01, 0.1, 0.1, TextureTrophee);
	}

}

void SceneRankMenu::SetOrigin() {
	float widthScreen = WindowManager::GetWindow()->getSize().x;
	float heightScreen = WindowManager::GetWindow()->getSize().y;

	text.setOrigin(sf::Vector2f(widthScreen / 2, heightScreen / 2));
}

void SceneRankMenu::Update(sf::Time _delta) {
	Scene::Update(_delta);
	if (backButton->GetComponent<Button>()->IsClicked()) {
		SceneManager::RunScene("SceneMainMenu");
	}
}
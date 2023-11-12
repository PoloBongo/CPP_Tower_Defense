#include "Scenes/SceneSuccessMenu.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "Components/Button.h"
#include "AssetManager.h"

SceneSuccessMenu::SceneSuccessMenu(sf::RenderWindow* _window) : Scene(_window) {
	this->Awake();
	Scene::Create();
}

SceneSuccessMenu::~SceneSuccessMenu() {
	this->Delete();
}


void SceneSuccessMenu::Create() {
	Scene::Create();
	sf::Texture backgroundTexture2;

	if (!backgroundTexture2.loadFromFile("../assets/Sprite_LOL/background/background2_lol.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background2 = CreateBackgroundGameObject("Background2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture2);
	this->CreateSceneButtonsMenu();
}

void SceneSuccessMenu::Delete() {
	Scene::Delete();
}

void SceneSuccessMenu::Render(sf::RenderWindow* _window) {
	Scene::Render(_window);
}

void SceneSuccessMenu::CreateSceneButtonsMenu() {
	float widthScreen = WindowManager::GetWindow()->getSize().x;
	float heightScreen = WindowManager::GetWindow()->getSize().y;
	successButton = CreateButtonGameObject("Success", widthScreen / 2, heightScreen / 10, 50);
	backButton = CreateButtonGameObject("Retour", widthScreen / 15, heightScreen / 13, 20);
	firstSuccessButton = CreateButtonGameObject("\tNombre de partie gagne", widthScreen / 2, heightScreen / 3.5, 70);

	float posX = firstSuccessButton->GetPosition().x;
	float posY = firstSuccessButton->GetPosition().y;

	sf::Texture textureMedaille;

	if (!textureMedaille.loadFromFile("../assets/Sprite/rank.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}

	GameObject* textureMedialle1 = CreateDecorObject("TextureMedialle1", posX * 0.55, posY * 1.04, 0.2, 0.2, textureMedaille);

}

void SceneSuccessMenu::SetOrigin() {
	float widthScreen = WindowManager::GetWindow()->getSize().x;
	float heightScreen = WindowManager::GetWindow()->getSize().y;

	text.setOrigin(sf::Vector2f(widthScreen / 2, heightScreen / 2));
}

void SceneSuccessMenu::Update(sf::Time _delta) {
	Scene::Update(_delta);
	if (firstSuccessButton->GetComponent<Button>()->IsClicked()) {
		std::cout << "texte" << std::endl;
	}
	if (backButton->GetComponent<Button>()->IsClicked()) {
		SceneManager::RunScene("SceneMainMenu");
	}
}
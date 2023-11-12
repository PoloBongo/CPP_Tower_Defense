#include "Scenes/SceneLoginSignup.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "Components/Button.h"

SceneLoginSignup::SceneLoginSignup(sf::RenderWindow* _window) : Scene(_window)
{
	this->Create();
}

void SceneLoginSignup::Create() {
	Scene::Create();
	sf::Texture backgroundTexture2;

	if (!backgroundTexture2.loadFromFile("../assets/Sprite_LOL/background/background2_lol.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background2 = CreateBackgroundGameObject("Background2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture2);
	loginName = CreateInputGameObject("loginName", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 8);
	loginPassWord = CreateInputGameObject("loginPassWord", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 7);
	buttonLogin = CreateButtonGameObject("buttonLogin", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 6, 30);
	signupName = CreateInputGameObject("signupName", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 5);
	signupPassWord = CreateInputGameObject("signupPassWord", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 4);
	buttonSignup = CreateButtonGameObject("buttonSignup", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 3, 30);
	buttonReturn = CreateButtonGameObject("Retour", WindowManager::GetWindowWidth() / 15, WindowManager::GetWindowHeight() / 13, 20);
}

void SceneLoginSignup::Update(sf::Time _delta)
{
	Scene::Update(_delta);
	if (buttonReturn->GetComponent<Button>()->IsClicked() && buttonReturn->GetActive()) {
		SceneManager::RunScene("SceneMainMenu");
	}
}

void SceneLoginSignup::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
}

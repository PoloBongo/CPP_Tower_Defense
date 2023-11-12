#include "Scenes/SceneMainMenu.h"
#include "WindowManager.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "AudioManager.h"
#include "WindowManager.h"

SceneMainMenu::SceneMainMenu(sf::RenderWindow* _window) : Scene(_window) {
	texture = nullptr;
	textureBullet = nullptr;
}

void SceneMainMenu::Create() {
	Scene::Create();
	sf::Texture backgroundTexture1;
	if (!backgroundTexture1.loadFromFile("../assets/Sprite_LOL/background/background_lol.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}

	GameObject* background1 = CreateBackgroundGameObject("Background1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture1);
	this->CreateSceneButtonsMenu();
	this->activeOption(false);
	this->activeMenu(true);

}
void SceneMainMenu::Delete() {
	delete texture;
	delete textureBullet;
	Scene::Delete();
}

void SceneMainMenu::Render(sf::RenderWindow* _window) {
	Scene::Render(_window);
}

void SceneMainMenu::CreateSceneButtonsMenu() {
	float widthScreen = WindowManager::GetWindow()->getSize().x;
	float heightScreen = WindowManager::GetWindow()->getSize().y;
	playButton = CreateButtonGameObject("Play", widthScreen / 2, heightScreen / 3, 50);
	optionsButton = CreateButtonGameObject("Options", widthScreen / 2, heightScreen / 2, 20);
	quitButton = CreateButtonGameObject("Quit", widthScreen / 2, heightScreen / 1.5, 50);
	successButton = CreateButtonGameObject("Success", widthScreen / 1.2, heightScreen / 10, 25);
	rankButton = CreateButtonGameObject("Rank", widthScreen / 1.3, heightScreen / 10, 25);
	creditsButton = CreateButtonGameObject("Credits", widthScreen / 1.1, heightScreen / 10, 25);
	backButton = CreateButtonGameObject("Back", widthScreen / 10, heightScreen / 10, 20);
	sliderFPS = CreateSliderGameObject("SliderFPS", widthScreen / 2, heightScreen / 2, 1200, 40, 50, 50, 20, WindowManager::GetFps(), WindowManager::GetMinFps(), WindowManager::GetMaxFps());
	sliderVolume = CreateSliderGameObject("SliderVolume", widthScreen / 2, heightScreen / 1.5, 1200, 40, 50, 50, 20, AudioManager::GetVolume(), AudioManager::GetMaxVolume());
	//signupLoginButton = CreateButtonGameObject("Signup Login", widthScreen / 1.2, heightScreen / 1.2, 30);
}

void SceneMainMenu::Update(sf::Time _delta) {
	Scene::Update(_delta);
	if (playButton->GetComponent<Button>()->IsClicked()) {
		std::cout << "Play";
		SceneManager::RunScene("SceneGameLVSR");
	}
	else if (optionsButton->GetComponent<Button>()->IsClicked() && optionsButton->GetActive()) {
		std::cout << "Option";
		this->activeMenu(false);
		this->activeOption(true);
	}
	else if (quitButton->GetComponent<Button>()->IsClicked() && quitButton->GetActive()) {
		std::cout << "Close";
		WindowManager::GetWindow()->close();
	}
	else if (backButton->GetComponent<Button>()->IsClicked() && backButton->GetActive()) {
		std::cout << "Back";
		this->activeOption(false);
		this->activeMenu(true);
	}
	else if (successButton->GetComponent<Button>()->IsClicked() && successButton->GetActive()) {
		std::cout << "Succes";
		SceneManager::RunScene("SceneSuccessMenu");
	}
	else if (rankButton->GetComponent<Button>()->IsClicked() && rankButton->GetActive()) {
		std::cout << "Rank";
		SceneManager::RunScene("SceneRankMenu");
	}
	else if (creditsButton->GetComponent<Button>()->IsClicked() && creditsButton->GetActive()) {
		std::cout << "Credits";
		SceneManager::RunScene("SceneCreditsMenu");
	}
	if (option) {
		if (sliderFPS && sliderFPS->GetActive())
		{
			std::cout << "slider";
			WindowManager::SetFps(sliderFPS->GetComponent<Slider>()->GetDataInt());
		}
		if (sliderVolume && sliderVolume->GetActive())
		{
			std::cout << "slider2";
			AudioManager::SetVolume(sliderVolume->GetComponent<Slider>()->GetDataInt());
		}
	}

	/*else if (signupLoginButton->GetComponent<Button>()->IsClicked() && signupLoginButton->GetActive()) {
		SceneManager::RunScene("SceneLoginSignup");
	}*/
}

void SceneMainMenu::activeMenu(bool _state) {
	this->playButton->SetActive(_state);
	this->optionsButton->SetActive(_state);
	this->quitButton->SetActive(_state);
	this->creditsButton->SetActive(_state);
	this->rankButton->SetActive(_state);
	this->successButton->SetActive(_state);
	//this->signupLoginButton->SetActive(_state);
}

void SceneMainMenu::activeOption(bool _state) {
	this->backButton->SetActive(_state);
	this->sliderFPS->SetActive(_state);
	this->sliderVolume->SetActive(_state);
	option = _state;
}

SceneMainMenu::~SceneMainMenu() {
	this->Delete();
}
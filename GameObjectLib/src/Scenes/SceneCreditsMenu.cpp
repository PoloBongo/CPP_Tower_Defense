#include "Scenes/SceneCreditsMenu.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "Components/Button.h"
#include "AssetManager.h"
#include "Scenes/SceneMainMenu.h"
#include "Components/SpriteRenderer.h"

SceneCreditsMenu::SceneCreditsMenu(sf::RenderWindow* _window) : Scene(_window) {
	this->Awake();
	Scene::Create();
}

void SceneCreditsMenu::Create() {
	Scene::Create();
	sf::Texture backgroundTexture2;

	if (!backgroundTexture2.loadFromFile("../assets/Sprite_LOL/background/fontaineLOL.jpg"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background2 = CreateBackgroundGameObject("Background2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture2);
	this->CreateSceneButtonsMenu();
	this->LoadCreditsTexture();
	imagesCredits.clear();
	texteCredits.clear();
}

void SceneCreditsMenu::Render(sf::RenderWindow* _window) {
	Scene::Render(_window);
}

void SceneCreditsMenu::CreateSceneButtonsMenu() {
	float widthScreen = static_cast<float>(WindowManager::GetWindow()->getSize().x);
	float heightScreen = static_cast<float>(WindowManager::GetWindow()->getSize().y);
	creditsButton = CreateButtonGameObject("Crédits", widthScreen / 2, heightScreen / 13, 50);
	backButton = CreateButtonGameObject("Retour", widthScreen / 15, heightScreen / 13, 20);
}

void SceneCreditsMenu::LoadCreditsTexture()
{
	float widthScreen = static_cast<float>(WindowManager::GetWindow()->getSize().x);
	float heightScreen = static_cast<float>(WindowManager::GetWindow()->getSize().y);

	for (size_t i = 0; i < 6; i++)
	{
		imagesCredits.push_back(CreateDecorObject("TextureCredits1", widthScreen / 1.7, -500.0f, 0.5, 0.5, *AssetManager::GetAsset("credits" + std::to_string(i))));
		texteCredits.push_back(CreateButtonGameObject(allTexteCredits[i], widthScreen / 1.7, -500.0f, 20));
	}
}

void SceneCreditsMenu::SetOrigin() {
	float widthScreen = WindowManager::GetWindow()->getSize().x;
	float heightScreen = WindowManager::GetWindow()->getSize().y;

	text.setOrigin(sf::Vector2f(widthScreen / 2, heightScreen / 2));
}

void SceneCreditsMenu::AnimCredits(float _deltaSeconds, float _iteration, int _totalLoop)
{	
	float widthScreen = static_cast<float>(WindowManager::GetWindow()->getSize().x);

	startPosFrancoisX = imagesCredits[0]->GetPosition().x;
	startPosFrancoisY = imagesCredits[0]->GetPosition().y;

	Maths::Vector2f pointA(startPosFrancoisX, startPosFrancoisY);
	Maths::Vector2f pointB(widthScreen / 1.7, 500.0f);

	Maths::Vector2f playerPosition = pointA;
	Maths::Vector2f displacement = pointB - pointA;


	if (_deltaSeconds < _totalLoop)
	{
		this->imagesCredits[0]->SetPosition(playerPosition += (displacement / 1.0f) * _deltaSeconds);
		this->texteCredits[0]->SetPosition(playerPosition += (displacement / 1.0f) * _deltaSeconds);
	}
	else if (_deltaSeconds > _totalLoop + 4)
	{
		if (startPosFrancoisX > -250.f)
		{
			this->imagesCredits[0]->SetPosition(playerPosition += ( Maths::Vector2f::DiagonaleLeft / 0.5f ) * _deltaSeconds);
			this->texteCredits[0]->SetPosition(playerPosition + Maths::Vector2f::DiagonaleLeft * _deltaSeconds);
		}
		else
		{
			imagesCredits.erase(imagesCredits.begin());
			texteCredits.erase(texteCredits.begin());
			goodPosCredits = true;
		}
	}
}

void SceneCreditsMenu::Update(sf::Time _delta) {
	Scene::Update(_delta);

	deltaSeconds += _delta.asSeconds();

	if (goodPosCredits)
	{
		deltaSeconds = 0;
		goodPosCredits = false;
	}
	
	if (!imagesCredits.empty())
	{
		this->AnimCredits(deltaSeconds, iteration, totalLoop);
	}
	else if (imagesCredits.empty())
	{
		this->LoadCreditsTexture();
		this->AnimCredits(deltaSeconds, iteration, totalLoop);
	}
	

	if (backButton->GetComponent<Button>()->IsClicked()) {
		SceneManager::RunScene("SceneMainMenu");
	}
}

GameObject* SceneCreditsMenu::CreateCreditsGameObject(const std::string& name, float _x, float _y, const sf::Texture texture, float scalex, float scaley)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));


	Player* player = gameObject->CreateComponent<Player>();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	return gameObject;
}

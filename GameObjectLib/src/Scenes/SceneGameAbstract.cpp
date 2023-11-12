#include "Scenes/SceneGameAbstract.h"

#include "SceneManager.h"
#include "AssetManager.h"
#include "WindowManager.h"

#include "Components/Button.h"
#include "Components/Carre.h"
#include "Components/Spawn.h"
#include "Components/SquareCollider.h"
#include "Components/SpriteRenderer.h"
#include "Components/Ressource.h"
#include "Components/FireBullet.h"
#include "Components/HealthPointBar.h"
#include "Components/Entities/Enemies/EnemyA.h"
#include "Components/Entities/Enemies/EnemyB.h"
#include "Components/Entities/Enemies/EnemyC.h"
#include "Components/Entities/Towers/Nexus.h"
#include "Components/Entities/Towers/Bat1.h"
#include "Components/Entities/Towers/Bat2.h"
#include "Components/Entities/Towers/Lulu.h"
#include "Components/Entities/Towers/Malphite.h"
#include "Components/Entities/Towers/Varus.h"
#include "Components/Entities/Towers/XinZhao.h"


SceneGameAbstract::SceneGameAbstract(sf::RenderWindow* _window) : Scene(_window) {
	this->Awake();
	srand(time(nullptr));
}


SceneGameAbstract::~SceneGameAbstract() {
	this->Delete();
}

void SceneGameAbstract::Create() {
	Scene::Create();

	this->victory = CreateImageGameObject("Victory", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 2.f, 2.f, *AssetManager::GetAsset("Victory"));
	this->defeat = CreateImageGameObject("Defeat", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 2.f, 2.f, *AssetManager::GetAsset("Defeat"));
	this->victory->SetActive(false);
	this->defeat->SetActive(false);
	endTime = 5.0f;
}

void SceneGameAbstract::Delete() {
	this->enemies.clear();
	delete texture;
	Scene::Delete();
}


void SceneGameAbstract::CreatePauseMenuButtons() {
	pausePlayButton = CreateButtonGameObject("Continue", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 4.0, 50);
	pauseMenuPrincipalButton = CreateButtonGameObject("Menu Principal", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2.5, 50);
	//pauseOptionsButton = CreateButtonGameObject("Options", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.8, 50);
	pauseQuitButton = CreateButtonGameObject("Quit", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.8, 50);
	this->ManageSceneGameButtonsPause(false);
}

void SceneGameAbstract::Awake() {
	Scene::Awake();
}

void SceneGameAbstract::CreatePlayer() {
}

void SceneGameAbstract::CreateTower()
{
	gameTowers.push_back(CreateBatimentGameObject("Varus", 0.f, 0.f, *AssetManager::GetAsset("Varus"), 0.5f, 0.5f, 300.f, 30.f));
	gameTowers.push_back(CreateBatimentGameObject("Lulu", 0.f, 0.f, *AssetManager::GetAsset("Lulu"), 0.5f, 0.5f, 300.f, 30.f));
	gameTowers.push_back(CreateBatimentGameObject("Malphite", 0.f, 0.f, *AssetManager::GetAsset("Malphite"), 2.5f, 2.5f, 300.f, 30.f));
	gameTowers.push_back(CreateBatimentGameObject("XinZhao", 0.f, 0.f, *AssetManager::GetAsset("XinZhao"), 2.5f, 2.5f, 300.f, 30.f));
	gameTowers.push_back(CreateBatimentGameObject("Bat1", 0.f, 0.f, *AssetManager::GetAsset("Bat1"), 2.5f, 2.5f,300.f, 0.f));
	gameTowers.push_back(CreateBatimentGameObject("Bat2", 0.f, 0.f, *AssetManager::GetAsset("Bat2"), 2.5f, 2.5f,300.f, 5.f));
	for (int i = 0; i < gameTowers.size(); i++) {
		gameTowers[i]->SetActive(false);
	}
};

void SceneGameAbstract::CreateRessource()
{
	ressource = this->CreatePlayerRessourceGameObject("Ressources", 50.f, 50.f, *AssetManager::GetAsset("Gold"), 2.5f, 2.5f, 300.f, 200.f);
};

void SceneGameAbstract::RemoveEnemy(GameObject* _enemyToRemove) {
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[_enemyToRemove](GameObject* obj) {
			return obj == _enemyToRemove;
		}), enemies.end());
}

void SceneGameAbstract::RemoveTower(GameObject* _towerToRemove) {
	towers.erase(std::remove_if(towers.begin(), towers.end(),
		[_towerToRemove](GameObject* obj) {
			return obj == _towerToRemove;
		}), enemies.end());
}



void SceneGameAbstract::ManageSceneGameButtonsPause(bool _state) {
	this->pauseMenuPrincipalButton->SetActive(_state);
	this->pausePlayButton->SetActive(_state);
	//this->pauseOptionsButton->SetActive(_state);
	this->pauseQuitButton->SetActive(_state);
}

void SceneGameAbstract::ManagePause()
{
	this->ManageSceneGameButtonsPause(!isActive);
	for (GameObject* enemy : this->enemies)
	{
		enemy->SetActive(isActive);
	}
	for (GameObject* tower : this->towers)
	{
		tower->SetActive(isActive);
	}
}

void SceneGameAbstract::Update(sf::Time _delta) {
	this->inputGame->Update(_delta);
	this->ManagePause();
	if (isActive)
	{
		Scene::Update(_delta);
	}
	else
	{
		if (pausePlayButton->GetComponent<Button>()->IsClicked()) {
			this->ManagePause();
			isActive = true;
		}
		else if (pauseMenuPrincipalButton->GetComponent<Button>()->IsClicked()) {
			this->ManagePause();
			SceneManager::RunScene("SceneMainMenu");
		}
		//else if (pauseOptionsButton->GetComponent<Button>()->IsClicked()) {
		//	std::cout << "Options" << std::endl;
		//}
		else if (pauseQuitButton->GetComponent<Button>()->IsClicked()) {
			WindowManager::GetWindow()->close();
		}
	}
}

void SceneGameAbstract::GameEnd(bool _win, sf::Time _delta)
{
	float deltaSecond = _delta.asSeconds();
	endTime -= deltaSecond;
	if (_win)
	{
		this->victory->SetActive(true);
	}
	else
	{
		this->defeat->SetActive(true);
	}
	if (endTime <= deltaSecond) {
		SceneManager::StopScene();
		SceneManager::RunScene("SceneMainMenu");
	}
}

void SceneGameAbstract::CreateBackground()
{
	sf::Texture backgroundTexture1;

	if (!backgroundTexture1.loadFromFile("../assets/Sprite/background/background_color.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background1 = CreateBackgroundGameObject("Background1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture1);
};

void SceneGameAbstract::Render(sf::RenderWindow* _window) {
	Scene::Render(_window);
}

GameObject* SceneGameAbstract::CreateTowerGameObject(const std::string& name, float positionx, float positiony, const sf::Texture texture, float scalex, float scaley)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	

	return gameObject;
}
GameObject* SceneGameAbstract::CreateBatimentGameObject(const std::string& name, float _x, float _y, const sf::Texture texture, float scalex, float scaley, float prixGold, float prixMana)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Entity* entity;
	if (name == "Bat1") {
		entity = gameObject->CreateComponent<Bat1>();
	}
	else if (name == "Bat2") {
		entity = gameObject->CreateComponent<Bat2>();
	}
	else if (name == "Lulu") {
		entity = gameObject->CreateComponent<Lulu>();
	}
	else if (name == "Malphite") {
		entity = gameObject->CreateComponent<Malphite>();
	}
	else if (name == "Varus") {
		entity = gameObject->CreateComponent<Varus>();
	}
	else if (name == "XinZhao") {
		entity = gameObject->CreateComponent<XinZhao>();
	}

	Ressource* ressource = gameObject->CreateComponent<Ressource>();
	ressource->SetGold(prixGold);
	ressource->SetMana(prixMana);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	return gameObject;
}
GameObject* SceneGameAbstract::CreatePlayerRessourceGameObject(const std::string& name, float _x, float _y, const sf::Texture texture, float scalex, float scaley, float ressourceGold, float ressourceMana)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Ressource* ressource = gameObject->CreateComponent<Ressource>();
	ressource->SetGold(ressourceGold);
	ressource->SetMana(ressourceMana);
	ressource->SetText();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();
	sprite->SetHud(true);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	return gameObject;
}

GameObject* SceneGameAbstract::CreateTurretGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateCarreGameObject(const std::string& name, float x, float y)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));
	gameObject->SetActive(false);

	Spawn* spawn = gameObject->CreateComponent<Spawn>();

	Carre* carre = gameObject->CreateComponent<Carre>();
	carre->SetPosition(x, y);
	carre->SetSize(100, 100);
	carre->SetOrigin();
	carre->SetCarre();

	return gameObject;
};

GameObject* SceneGameAbstract::CreateBulletGameObject(const std::string& name, const sf::Texture textureBullet, float scalex, float scaley, GameObject* _player)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(textureBullet);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(0.5, 0.5);

	FireBullet* fireBullet = gameObject->CreateComponent<FireBullet>();
	fireBullet->setDirection(_player);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateEnemyAGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, int lane, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	EnemyA* enemy = gameObject->CreateComponent<EnemyA>();
	enemy->SetLane(lane);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(25);
	healthPointBar->SetSize(25, 2);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();
	enemies.push_back(gameObject);

	return gameObject;
}

GameObject* SceneGameAbstract::CreateEnemyBGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, int lane, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	EnemyB* enemy = gameObject->CreateComponent<EnemyB>();
	enemy->SetLane(lane);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);


	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(25);
	healthPointBar->SetSize(25, 2);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();

	enemies.push_back(gameObject);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateEnemyCGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, int lane, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	EnemyC* enemy = gameObject->CreateComponent<EnemyC>();
	enemy->SetLane(lane);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(25);
	healthPointBar->SetSize(25, 2);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();

	enemies.push_back(gameObject);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateBossGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, int lane, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	EnemyB* enemy = gameObject->CreateComponent<EnemyB>();
	enemy->SetLane(lane);
	enemy->SetMaxHealthPoint(1000);
	enemy->SetHealthPoint(1000);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(50);
	healthPointBar->SetSize(50, 2);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();

	enemies.push_back(gameObject);

	return gameObject;

}


GameObject* SceneGameAbstract::CreateNexusGameObject()
{
	GameObject* gameObject = CreateGameObject("nexus");
	gameObject->SetPosition(Maths::Vector2f(WindowManager::GetWindowWidth() / 3.98, WindowManager::GetWindowHeight() / 1.30));

	Nexus* nexus = gameObject->CreateComponent<Nexus>();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(*AssetManager::GetAsset("Nexus"));
	sprite->SetScale(1.f, 1.f);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(1.f, 1.f);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(nexus->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(nexus->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();

	this->nexus = gameObject;

	return gameObject;

}


GameObject* SceneGameAbstract::CreateImageGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, sf::Texture _texture) 
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	return gameObject;
}
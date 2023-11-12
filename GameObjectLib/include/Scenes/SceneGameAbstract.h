#pragma once
#include "Scene.h"


class SceneGameAbstract : public Scene
{
public:
	SceneGameAbstract(sf::RenderWindow* window);
	~SceneGameAbstract();

	void Awake() override;

	void CreatePlayer();
	void CreateTower();
	void CreateRessource();

	void RemoveEnemy(GameObject* _enemyToRemove);
	void RemoveTower(GameObject* _towerToRemove);


	void ManagePause();
	void ManageSceneGameButtonsPause(bool _states);
	void CreatePauseMenuButtons();

	//PLAYER 
	GameObject* CreateTowerGameObject(const std::string& name, float positionx, float positiony, const sf::Texture texture, float scalex, float scaley);
	GameObject* CreateBatimentGameObject(const std::string& name, float _x, float _y, const sf::Texture texture, float scalex, float scaley, float prixGold, float prixMana);
	GameObject* CreateBulletGameObject(const std::string& name, const sf::Texture textureBullet, float scalex, float scaley, GameObject* _player);
	GameObject* CreatePlayerRessourceGameObject(const std::string& name, float _x, float _y, const sf::Texture texture, float scalex, float scaley, float ressourceGold, float ressourceMana);

	GameObject* CreateEnemyAGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, int lane, sf::Texture _texture);
	GameObject* CreateEnemyBGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, int lane, sf::Texture _texture);
	GameObject* CreateEnemyCGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, int lane, sf::Texture _texture);
	GameObject* CreateBossGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, int lane, sf::Texture _texture);

	GameObject* CreateTurretGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, sf::Texture _texture);
	GameObject* CreateNexusGameObject();
	GameObject* CreateImageGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, sf::Texture _texture);


	GameObject* CreateCarreGameObject(const std::string& name, float x, float y);

	void CreateBackground();
	void Create() override;
	void Delete() override;
	void Update(sf::Time _delta) override;
	void Render(sf::RenderWindow* _window) override;
	void GameEnd(bool _win, sf::Time _delta);
	std::vector<GameObject*> GetEnemies() { return enemies; }
	GameObject* GetEnemie(int _index) { return enemies[_index]; }
	std::vector<GameObject*> GetTowers() { return towers; }
	GameObject* GetTowers(int _index) { return towers[_index]; }

protected:
	std::vector<GameObject*> towers;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> gameTowers;
	GameObject* player = nullptr;
	//GameObject* varus = nullptr;
	//GameObject* lulu = nullptr;
	//GameObject* malphite = nullptr;
	//GameObject* xinZhao = nullptr;
	//GameObject* bat1 = nullptr;
	//GameObject* bat2 = nullptr;
	GameObject* nexus = nullptr;
	GameObject* ressource = nullptr;
	GameObject* ressourceText = nullptr;
	GameObject* pausePlayButton = nullptr;
	GameObject* pauseOptionsButton = nullptr;
	GameObject* pauseMenuPrincipalButton = nullptr;
	GameObject* pauseQuitButton = nullptr;
	GameObject* pauseBongoButton = nullptr;
	GameObject* victory = nullptr;
	GameObject* defeat = nullptr;
	float endTime = 5.f;
	sf::Texture* texture;
	sf::Text text;
};


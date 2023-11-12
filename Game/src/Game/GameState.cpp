#include "Game/GameState.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "AssetManager.h"
#include "WindowManager.h"
#include "CameraManager.h"
#include "HUDManager.h"
#include "EventManager.h"
#include "SceneMainMenu.h"
#include "SceneSuccessMenu.h"
#include "SceneCreditsMenu.h"
#include "SceneRankMenu.h"
#include "SceneGameLVSR.h"
#include "SceneLoginSignup.h"

GameState::GameState(sf::RenderWindow* _window, int _FPS) {
	this->window = _window;
	this->FPS = _FPS;
	WindowManager::SetFps(this->FPS);
	CameraManager::SetWindow(this->window);
	EventManager::SetEvent(this->event);
}


void GameState::Preload() {
	HUDManager::Preload();
	this->PreloadScenes();
	this->PreloadAudio();
	this->PreloadAssets();
}

void GameState::Create() {
	SceneManager::RunScene("SceneMainMenu");

}

void GameState::PreloadScenes() {
	SceneManager::AddScene("SceneMainMenu", new SceneMainMenu(this->window));
	SceneManager::AddScene("SceneSuccessMenu", new SceneSuccessMenu(this->window));
	SceneManager::AddScene("SceneRankMenu", new SceneRankMenu(this->window));
	SceneManager::AddScene("SceneCreditsMenu", new SceneCreditsMenu(this->window));
	SceneManager::AddScene("SceneGameLVSR", new SceneGameLVSR(this->window));
	//SceneManager::AddScene("SceneLoginSignup", new SceneLoginSignup(this->window));
}

void GameState::PreloadAssets() {
	//Map
	AssetManager::AddAsset("mapLol", "../assets/Sprite_LOL/Map/map.jpg");

	AssetManager::AddAsset("Gold", "../assets/Sprite_LOL/Ressources/gold.png");

	//BackGrund
	AssetManager::AddAsset("backgroundMenu", "../assets/Sprite_LOL/Background/background_lol.png");
	AssetManager::AddAsset("backgroundOtherMenu", "../assets/Sprite_LOL/Background/background2_lol.png");
	//Boss
	AssetManager::AddAsset("bossErald", "../assets/Sprite_LOL/Boss/erald.png");
	AssetManager::AddAsset("bossVeigar", "../assets/Sprite_LOL/Boss/veigar.png");
	//Champions
	AssetManager::AddAsset("Varus", "../assets/Sprite_LOL/Champions/varus.png");
	AssetManager::AddAsset("Lulu", "../assets/Sprite_LOL/Champions/lulu.png");
	AssetManager::AddAsset("Malphite", "../assets/Sprite_LOL/Champions/malphite.png");
	AssetManager::AddAsset("XinZhao", "../assets/Sprite_LOL/Champions/xinZhao.png");
	//Minions
	AssetManager::AddAsset("minionMage", "../assets/Sprite_LOL/Minions/minion_mage.png");
	AssetManager::AddAsset("minionMelee", "../assets/Sprite_LOL/Minions/minion_melee.png");
	AssetManager::AddAsset("minionSiege", "../assets/Sprite_LOL/Minions/minion_siege.png");
	//Batiments
	AssetManager::AddAsset("Nexus", "../assets/Sprite_LOL/Batiments/nexus.png");
	AssetManager::AddAsset("Bat1", "../assets/Sprite_LOL/Batiments/batiment_1.png");
	AssetManager::AddAsset("Bat2", "../assets/Sprite_LOL/Batiments/batiment_2.png");
	AssetManager::AddAsset("Victory", "../assets/Sprite_LOL/VictoryDefeat/Victory.png");
	AssetManager::AddAsset("Defeat", "../assets/Sprite_LOL/VictoryDefeat/Victory.png");
	//Bullet
	for (size_t i = 0; i < 6; i++)
	{
		AssetManager::AddAsset("bullet" + std::to_string(i), "../assets/Sprite_LOL/Bullet/bullet_" + std::to_string(i) + ".png");
	}
	//Credits
	for (size_t i = 0; i < 6; i++)
	{
		AssetManager::AddAsset("credits" + std::to_string(i), "../assets/Sprite_LOL/Credits/credits_" + std::to_string(i) + ".png");
	}
}

void GameState::PreloadAudio() {
	AudioManager::AddMusic(std::string("soundtrack"), std::string("../assets/Sounds/soundtrack.ogg"));
	AudioManager::AddMusic(std::string("round_start"), std::string("../assets/Sounds/round_start.ogg"));
	AudioManager::AddMusic(std::string("nexus_under_attack"), std::string("../assets/Sounds/nexus_under_attack.ogg"));
	AudioManager::AddMusic(std::string("tower_placed"), std::string("../assets/Sounds/tower_placed.ogg"));
	AudioManager::AddMusic(std::string("tower_already_placed"), std::string("../assets/Sounds/tower_already_placed.ogg"));
	AudioManager::AddMusic(std::string("Lulu_attack"), std::string("../assets/Sounds/Lulu/Lulu_Select_SFX.ogg"));
	AudioManager::AddMusic(std::string("Malphite_attack"), std::string("../assets/Sounds/Malphite/Malphite_Select_SFX.ogg"));
	AudioManager::AddMusic(std::string("Varus_attack"), std::string("../assets/Sounds/Varus/Varus_Select_SFX.ogg"));
	AudioManager::AddMusic(std::string("XinZhao_attack"), std::string("../assets/Sounds/Xin_Zhao/Xin_Zhao_Select_SFX.ogg"));
	AudioManager::AddMusic(std::string("Bat1_attack"), std::string("../assets/Sounds/Bat_SFX.ogg"));
	AudioManager::AddMusic(std::string("Bat2_attack"), std::string("../assets/Sounds/Bat_SFX.ogg"));
	AudioManager::Play(std::string("soundtrack"));
}


void GameState::Update() {
	
	sf::Time delta = this->clock.restart();

	// limiter à un nombre fixe de FPS
	sf::Time frameTime = sf::seconds(1.0f / FPS);
	//Delta time for the update
	if (delta < frameTime)
	{
		sf::sleep(frameTime - delta);
		delta = frameTime;
	}

	EventManager::Update(delta);
	SceneManager::GetActiveScene()->Update(delta);

	this->window->clear(sf::Color::Black);

	SceneManager::GetActiveScene()->Render(this->window);
	this->window->display();
}

GameState::~GameState() {
}


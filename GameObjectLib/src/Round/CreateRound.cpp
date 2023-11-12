#include "Round/CreateRound.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "AudioManager.h"
#include "Components/Ressource.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

CreateRound::CreateRound()
{
	round = 1;
};

void CreateRound::setRound(int _round) {
	round = _round;
}

int CreateRound::getRound() {
	return round;
}

void CreateRound::SetRoundInfos(int _roundInt) {
	std::ifstream fichier("../assets/Save/Round.txt");
	if (fichier.is_open()) {
		std::string ligne;
		while (getline(fichier, ligne)) {
			char comma;
			int Round, Waves, Ennemies, TimeBetweenWaves;
			std::istringstream lineValue(ligne);
			if (lineValue >> Round >> comma >> Waves >> comma >> Ennemies >> comma >> TimeBetweenWaves) {
				if (Round == _roundInt) {
					this->Info.Round = Round;
					this->Info.Waves = Waves;
					this->Info.Ennemies = Ennemies;
					this->Info.TimeBetweenWaves = TimeBetweenWaves;
				}
			}
		}
	}
	fichier.close();
};

void CreateRound::CreateRound1(sf::Time _delta)
{
	/*AudioManager::Play("round_start");*/
	/*CreateRound::SetRoundInfos(1);*/
	TimeInRound += _delta.asSeconds();
	CreateRound::SetRoundInfos(1);
	CreateRound::SpawnEnemy();
}

void CreateRound::CreateRound2(sf::Time _delta)
{
	TimeInRound += _delta.asSeconds();
	CreateRound::SetRoundInfos(2);
	CreateRound::SpawnEnemy();
};
void CreateRound::CreateRound3(sf::Time _delta)
{
	TimeInRound += _delta.asSeconds();
	CreateRound::SetRoundInfos(3);
	CreateRound::SpawnEnemy();
};
void CreateRound::CreateRound4(sf::Time _delta)
{
	TimeInRound += _delta.asSeconds();
	CreateRound::SetRoundInfos(4);
	CreateRound::SpawnEnemy();
};

void CreateRound::SpawnEnemy() {
	srand(static_cast<unsigned int>(time(0)));
	if (TimeInRound > TimeToWait) {
		if (WavesSpawned < Info.Waves) {
			TimeToWait = 1.f;
			if (round != 4) {
				int EnnemyType = rand() % 3 + 1;
				int Lane = rand() % 3;
				if (EnnemyType == 1) {
					GameObject* EnemyA = SceneManager::GetActiveGameScene()->CreateEnemyAGameObject("EnemyA", 1411, 150, 0.1f, 0.1f, Lane, *AssetManager::GetAsset("minionMelee"));
				}
				else if (EnnemyType == 2) {
					GameObject* EnemyB = SceneManager::GetActiveGameScene()->CreateEnemyBGameObject("EnemyB", 1411, 150, 0.1f, 0.1f, Lane, *AssetManager::GetAsset("minionSiege"));
				}
				else {
					GameObject* EnemyC = SceneManager::GetActiveGameScene()->CreateEnemyCGameObject("EnemyC", 1411, 150, 0.1f, 0.1f, Lane, *AssetManager::GetAsset("minionMage"));
				}
			}
			else {
				GameObject* Boss = SceneManager::GetActiveGameScene()->CreateBossGameObject("Boss", 1411, 150, 0.2f, 0.2f, 1, *AssetManager::GetAsset("bossErald"));
			}
			TimeInRound = 0.f;
			EnemiesSpawnedInWave++;
			std::cout << "Ennemies spawned =" << EnemiesSpawnedInWave << std::endl;
			if (EnemiesSpawnedInWave == Info.Ennemies) {
				std::cout << "end wave" << std::endl;
				TimeToWait = static_cast<float>(Info.TimeBetweenWaves);
				WavesSpawned++;
				EnemiesSpawnedInWave = 0;
			}
		} else {
			//std::cout << "waiting for next round" << std::endl;
			if (SceneManager::GetActiveGameScene()->GetEnemies().size() == 0) {
				SceneManager::GetActiveGameScene()->GetGameObject("Ressources")->GetComponent<Ressource>()->AddGold(100 * round);
				WavesSpawned = 0;
				round++;
				EnemiesSpawnedInWave = 0;
			}
		}

	}
}
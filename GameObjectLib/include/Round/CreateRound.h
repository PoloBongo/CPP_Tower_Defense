#pragma once
#include <vector>
#include "GameObject.h"
class CreateRound
{
public:
	CreateRound();
	void setRound(int _round);
	int getRound();
	void SetRoundInfos(int _roundInt);
	void CreateRound1(sf::Time _delta);
	void CreateRound2(sf::Time _delta);
	void CreateRound3(sf::Time _delta);
	void CreateRound4(sf::Time _delta);
	void SpawnEnemy();

	int getRoundInfos() { return Info.Waves; }
private:
	int round = 1;
	std::vector<GameObject*> enemy;
	struct RoundInfo
	{
		int Round;
		int Waves;
		int Ennemies;
		int TimeBetweenWaves;
	};
	RoundInfo Info;
	int EnemiesSpawnedInWave = 0;
	int WavesSpawned = 0;
	float TimeInRound = 0.f;
	float TimeToWait = 1.f;
};
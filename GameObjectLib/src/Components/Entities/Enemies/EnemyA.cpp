#include "Components/Entities/Enemies/EnemyA.h"
#include "Components/Entities/EnemyAbstract.h"

EnemyA::EnemyA() : EnemyAbstract(25, 25, 0, 1.0f, 1.0f, 10.f) {};

void EnemyA::Check()
{
	EnemyAbstract::fichierStatsEnemey();
	for (const EnemyAbstract::EnemyStats enemy : listStatsEnemy)
	{
		if (enemy.WHichEnemey == "EnemyA")
		{
			std::cout << enemy.pv << "\n";
		}
	}
}
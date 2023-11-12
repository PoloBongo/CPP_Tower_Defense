#include "Components/Entities/EnemyAbstract.h"
#include "Components/Entities/TowerAbstract.h"
#include "WindowManager.h"
#include "SceneManager.h"

EnemyAbstract::EnemyAbstract() : Entity() {}

EnemyAbstract::EnemyAbstract(int _hp, int _damage, int _lane, float _speed,float _attackSpeed, float _range ) : Entity(_hp, _damage, _lane, _speed, _attackSpeed, _range) {}

void EnemyAbstract::Update(sf::Time _delta)
{
	Entity::Update(_delta);

	if (GetOwner()->GetPosition().GetX() > WindowManager::GetWindowWidth()
		|| GetOwner()->GetPosition().GetY() > WindowManager::GetWindowHeight()
		|| GetOwner()->GetPosition().GetY() < 0
		|| GetOwner()->GetPosition().GetX() < 0
		)
	{
		this->Die();
	}
}

void EnemyAbstract::Die()
{
	SceneManager::GetActiveGameScene()->RemoveEnemy(GetOwner());
	Entity::Die();
}


void EnemyAbstract::Attack(GameObject* _nexus) {
	_nexus->GetComponent<TowerAbstract>()->SetHealthPoint(-this->GetDamage());
}

void EnemyAbstract::setLane(int _lane) {
	this->lane = _lane;
}

int EnemyAbstract::getLane() {
	return this->lane;
}

void EnemyAbstract::fichierStatsEnemey()
{

	std::ifstream fichierStats("../GameObjectLib/src/Components/Entities/Enemies/Enemy.txt");

	if (!fichierStats.is_open())
	{
		std::cout << "Le fichier ne s'est pas ouvert!" << std::endl;
	}
	else
	{
		std::string nombreLigne;

		while (std::getline(fichierStats, nombreLigne))
		{
			EnemyStats attack;
			char virgule = '-';

			std::istringstream linestream(nombreLigne);
			if (std::getline(linestream, attack.WHichEnemey, virgule) &&
				linestream >> attack.pv >> virgule &&
				linestream >> attack.damage >> virgule &&
				linestream >> attack.lane >> virgule &&
				linestream >> attack.speed >> virgule &&
				linestream >> attack.attackSpeed >> virgule &&
				linestream >> attack.range) {
				listStatsEnemy.push_back(attack);
			}

		};

		fichierStats.close();
	}
}
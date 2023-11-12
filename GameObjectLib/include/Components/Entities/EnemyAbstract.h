#pragma once
#include "Components/Entity.h"
#include "Scene.h"
#include <fstream>
#include <sstream>

class EnemyAbstract : public Entity {
protected:
	struct EnemyStats {
		std::string WHichEnemey;
		int pv;
		int damage;
		int lane;
		float speed;
		float attackSpeed;
		float range;
		int count;
	};
public:
    EnemyAbstract();
    EnemyAbstract(int _hp, int _damage, int _lane, float _speed, float _attackSpeed, float _range);

    void Update(sf::Time _delta) override;

    void Die() override;

    void Attack(GameObject* _nexus);
    void setLane(int _lane);
    int getLane();
    int lane;

    void fichierStatsEnemey();
	std::vector<EnemyStats> listStatsEnemy = {};
};
#pragma once
#include "Components/Entity.h"
#include "Scene.h"

class TowerAbstract : public Entity {
public:
    TowerAbstract();
    TowerAbstract(int _hp, int _damage, int _lane, float _speed, float _attackspeed, float _range);

    void Update(sf::Time _delta) override;

    void Die() override;
};
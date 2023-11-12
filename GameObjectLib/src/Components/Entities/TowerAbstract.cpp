#include "Components/Entities/TowerAbstract.h"
#include "WindowManager.h"
#include "SceneManager.h"

TowerAbstract::TowerAbstract() : Entity() {}
TowerAbstract::TowerAbstract(int _hp, int _damage, int _lane, float _speed, float _attackspeed, float _range) : Entity(_hp, _damage, _lane, _speed, _attackspeed, _range) {}

void TowerAbstract::Update(sf::Time _delta)
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

void TowerAbstract::Die()
{
	SceneManager::GetActiveGameScene()->RemoveTower(GetOwner());
	Entity::Die();
}
#include "Components/Entity.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "WindowManager.h"
#include "AudioManager.h"


Entity::Entity() : healthPoint(100), maxHealthPoint(100), damage(10), lane(0), attackSpeed(1.0f), range(1), speed(20.f) {}
Entity::Entity(int _hp, int _damage, int _lane,float _speed, float _attackSpeed, float _range) : healthPoint(_hp), maxHealthPoint(_hp), damage(_damage), lane(_lane), speed(_speed), attackSpeed(_attackSpeed), range(_range) {}

void Entity::TakeDamage(int _damage) {
	if (healthPoint > damage)
	{
		healthPoint -= _damage;
	}
	else {
		healthPoint = 0;
	}

	if(healthPoint <= 0)
	{
		this->Die();
	}
}

void Entity::Die() {
	healthPoint = 0;
	AudioManager::PlaySound("dead");
	SceneManager::GetActiveGameScene()->RemoveGameObject(GetOwner());
}

void Entity::SetCurrPathPoint(int newPathPoint) {
	currPathPoint = newPathPoint;
}

void Entity::MoveToPoint(Maths::Vector2i point, float speed) {
	owner->SetPosition(owner->GetPosition() + (Maths::Vector2f(point.x, point.y) - owner->GetPosition()).Normalize() * speed);
}

void Entity::Update(sf::Time _delta) {
	Component::Update(_delta);

	if (count < attackSpeed * 500) {
		count++;
	}

	if (GetOwner()->GetPosition().GetX() > WindowManager::GetWindowWidth()
		|| GetOwner()->GetPosition().GetY() > WindowManager::GetWindowHeight()
		|| GetOwner()->GetPosition().GetY() < 0
		|| GetOwner()->GetPosition().GetX() < 0
		)
	{
		this->Die();
	}
}
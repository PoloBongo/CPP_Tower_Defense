
#include "Components/Entities/Player.h"
#include "SceneManager.h"
#include "WindowManager.h"

Player::Player() : Entity(200, 30, 20.f,1.f,10.f, 10.f)
{
    directionPlayer = false;
	direction = Direction::Right;
}

Player::Player(int _hp, int _damage, int _lane, float _speed, float _attackspeed, float _range) : Entity(_hp, _damage, _lane, _speed, _attackspeed, _range)
{
    directionPlayer = false;
    direction = Direction::Right;
}

void Player::setDirection(Direction newDirection) {
	direction = newDirection;
}

void Player::Update(sf::Time _delta)
{
    Entity::Update(_delta);
    if (direction == Direction::Left)
    {
        directionPlayer = true;
    }
    else if (direction == Direction::Right)
    {
        directionPlayer = false;
    }
    if (GetOwner()->GetPosition().GetX() > WindowManager::GetWindowWidth()
        || GetOwner()->GetPosition().GetY() > WindowManager::GetWindowHeight()
        || GetOwner()->GetPosition().GetY() < 0
        || GetOwner()->GetPosition().GetX() < 0
        )
    { 
        this->Die();
        SceneManager::GetActiveScene()->RemoveGameObject(GetOwner());
        SceneManager::RunScene("SceneMainMenu");
    }
}
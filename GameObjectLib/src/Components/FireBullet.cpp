#include "Components/FireBullet.h"
#include "SceneManager.h"
#include "Components/SquareCollider.h"

FireBullet::FireBullet() {
	this->player = nullptr;
}
//TODO : demander au PROF comment réparer la multiplication car elle ne marche pas
void FireBullet::Update(sf::Time _delta)
{
	Component::Update(_delta);

	if (dirBullet == DirectionBullet::Left)
	{
		GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Left * 500.0f * _delta.asSeconds());
	}
	else
	{
		GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Right * 500.0f * _delta.asSeconds());
	}
	Collided();
}

void FireBullet::setDirection(GameObject* _player) {
	this->player = _player;
	if (this->player->GetComponent<Player>()->getDirection() == Player::Direction::Right) {
		this->dirBullet = FireBullet::DirectionBullet::Right;
	}
	else {
		this->dirBullet = FireBullet::DirectionBullet::Left;
	}
	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Right * 6.0f);
}

void FireBullet::Collided()
{


}
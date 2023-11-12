#include "Components/Inputs/InputPlayer.h"
#include "Commands/CommandsPlayer.h"
#include "Components/SpriteRenderer.h"
#include "SceneManager.h"

InputPlayer::InputPlayer() {
	this->player = nullptr;
	this->ActionKeyD_ = new MoveToRightCommand(this->GetOwner());
	this->ActionKeyQ_ = new MoveToLeftCommand(this->GetOwner());
	this->ActionKeySpace_ = new MoveToRightBulletCommand(this->GetOwner());
	this->ActionKeyZ_ = new JumpCommand(this->GetOwner());
}

void InputPlayer::Update(sf::Time _delta) 
{
	Component::Update(_delta);

	Command* commandMoves = this->HandleInput();
	if (commandMoves) 
	{
		commandMoves->Execute(_delta);
	}
	Command* commandJump = this->JumpInput();

	if (commandJump) 
	{
		commandJump->Execute(_delta);
	}
	Command* fireBullet = this->FireInput();

	if (fireBullet) 
	{
		fireBullet->Execute(_delta);
	}

}

Command* InputPlayer::HandleInput() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return ActionKeyQ_;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return ActionKeyD_;

	return nullptr;

}

Command* InputPlayer::JumpInput() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return ActionKeyZ_;
	return nullptr;
}

Command* InputPlayer::FireInput() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return ActionKeySpace_;
	return nullptr;
}


void InputPlayer::Jump(sf::Time _delta)
{
	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Down + Maths::Vector2f(0, -130) * _delta.asSeconds());
}

InputPlayer::~InputPlayer() {
	delete 	this->ActionKeyD_;
	delete 	this->ActionKeyQ_;
	delete 	this->ActionKeySpace_;
	delete 	this->ActionKeyZ_;
}
#pragma once

#include "Command.h"
#include "Components/Component.h"


class InputPlayer : public Component
{
public:
	InputPlayer();

	void Update(sf::Time _delta) override;
	Command* HandleInput();
	Command* JumpInput();
	Command* FireInput();
	void Jump(sf::Time _delta);
	~InputPlayer();

private:
	float JumpVelocity = 0.f;


	Command* ActionKeyZ_;
	Command* ActionKeyD_;
	Command* ActionKeyQ_;
	Command* ActionKeySpace_;
	GameObject* player;
};
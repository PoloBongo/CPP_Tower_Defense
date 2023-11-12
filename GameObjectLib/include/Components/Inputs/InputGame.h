#pragma once

#include "Commands/CommandsGame.h"
#include "Components/Component.h"


class InputGame : public Component
{
public:
	InputGame();
	void Update(sf::Time _delta) override;
	Command* PauseInput();
	Command* ArrowHorizontalInput();
	Command* ArrowVerticalInput();

private:
	Command* ActionKeyEscape_;
	bool isKeyEscapeAlreadyPressed = true;
	Command* ActionArrowRight_;
	Command* ActionArrowLeft_;
	Command* ActionArrowUp_;
	Command* ActionArrowDown_;
	sf::Vector2i lastMousePosition;
};


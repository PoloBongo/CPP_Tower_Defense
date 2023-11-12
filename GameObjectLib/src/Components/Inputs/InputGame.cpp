#include "Components/Inputs/InputGame.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "EventManager.h"

InputGame::InputGame() 
{
	sf::Vector2i lastMousePosition = sf::Mouse::getPosition();
	this->ActionKeyEscape_ = new PauseCommand();
	this->ActionArrowRight_ = new RightCommand();
	this->ActionArrowLeft_ = new LeftCommand();
	this->ActionArrowUp_ = new UpCommand();
	this->ActionArrowDown_ = new DownCommand();
}
void InputGame::Update(sf::Time _delta)
{
	Component::Update(_delta);
	Command* pauseInput = this->PauseInput();
	if (pauseInput)
	{
		pauseInput->Execute(_delta);
	} 
	Command* horizontalInput = this->ArrowHorizontalInput();
	if (horizontalInput)
	{
		horizontalInput->Execute(_delta);
	}
	Command* verticalInput = this->ArrowVerticalInput();
	if (verticalInput)
	{
		verticalInput->Execute(_delta);
	}
}

Command* InputGame::PauseInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !isKeyEscapeAlreadyPressed) {
		isKeyEscapeAlreadyPressed = true;
		return ActionKeyEscape_;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		isKeyEscapeAlreadyPressed = false;
	}
	return nullptr;

}


Command* InputGame::ArrowHorizontalInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		return ActionArrowRight_;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		return ActionArrowLeft_;
	}
	return nullptr;

}


Command* InputGame::ArrowVerticalInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		return ActionArrowUp_;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		return ActionArrowDown_;
	}
	return nullptr;

}



#include "Components/SpriteRenderer.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "AssetManager.h"
#include "HUDManager.h"
#include "CameraManager.h"

Sprite::Sprite()
{

	texture.create(100, 100);
	scalex = 1.0f;
	scaley = 1.0f;
	rectTexture = nullptr;

	currentFrame = 0;
	frameDuration = 0.2f;
	animationClock.restart();
	LoadPlayAnimation();
	LoadPlayAnimationGrunt();

}
sf::Vector2f Sprite::GetBounds()
{
	return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

void Sprite::LoadPlayAnimation()
{

}

void Sprite::PlayerPlayAnimation()
{
	if (animationClock.getElapsedTime().asSeconds() > frameDuration)
	{
		currentFrame = (currentFrame + 1) % animPlayer.size();
		texture = animPlayer[currentFrame];
		animationClock.restart();
	}
}

void Sprite::PlayerPlayAnimationRun()
{
	if (animationClock.getElapsedTime().asSeconds() > frameDuration)
	{
		currentFrame = (currentFrame + 1) % animPlayerRun.size();
		texture = animPlayerRun[currentFrame];
		animationClock.restart();
	}
}

void Sprite::LoadPlayAnimationGrunt()
{

}

void Sprite::GruntPlayAnimation()
{
	if (animationClock.getElapsedTime().asSeconds() > frameDuration)
	{
		currentFrame = (currentFrame + 1) % animGrunt.size();
		texture = animGrunt[currentFrame];
		animationClock.restart();
	}
}

void Sprite::GruntPlayAnimationRun()
{
	if (animationClock.getElapsedTime().asSeconds() > frameDuration)
	{
		currentFrame = (currentFrame + 1) % animGruntRun.size();
		texture = animGruntRun[currentFrame];
		animationClock.restart();
	}
}
void Sprite::Update(sf::Time _delta)
{
}

void Sprite::SetSprite()
{
	const auto position = GetOwner()->GetPosition();
	sprite.setTexture(texture);

	if (this->rectTexture) {
		sprite.setTextureRect(*rectTexture);
	}

	sprite.setScale(scalex, scaley);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setPosition(position.x, position.y);
}

void Sprite::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);
	this->SetSprite();

	if (inHud) {
		_window->setView(HUDManager::GetHud());
		_window->draw(sprite);
		_window->setView(CameraManager::GetView());
	}
	else {
		_window->draw(sprite);
	}

}

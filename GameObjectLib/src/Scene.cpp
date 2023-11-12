#include "Scene.h"
#include "WindowManager.h"
#include "WindowManager.h"

#include "Components/Button.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/Slider.h"
#include "Components/Input.h"


Scene::Scene(sf::RenderWindow* _window) {
	window = _window;
	this->inputGame = new InputGame();
}

void Scene::Create() {
}

void Scene::Delete() {
	for (GameObject* gameObject : this->gameObjects) {
		delete gameObject;
	}
	gameObjects.clear();
}

void Scene::Awake() {
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(sf::Time _delta)
{
	if (isActive)
	{
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update(_delta);
		}
	}

}

void Scene::Render(sf::RenderWindow* _window)
{


	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}

}

void Scene::SetIsActive(bool _state)
{
	isActive = _state;
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObject->SetActive(true);
	gameObjects.push_back(gameObject);
	return gameObject;
}


//GAME ELEMENT

GameObject* Scene::CreateButtonGameObject(const std::string& name, float x, float y, unsigned int fontSize)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));
	gameObject->SetActive(true);

	Button* button = gameObject->CreateComponent<Button>();
	button->SetPosition(x, y);
	button->SetButton(fontSize);
	button->SetOrigin();

	return gameObject;
}

GameObject* Scene::CreatePlatformObject(const std::string& name, float x, float y, float scaleX, float scaleY, const sf::Texture texture, sf::IntRect* _rectSource) {

	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetRect(_rectSource);
	sprite->SetScale(scaleX, scaleY);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scaleX, scaleY);



	return gameObject;
}

GameObject* Scene::CreateDecorObject(const std::string& name, float x, float y, float scaleX, float scaleY, const sf::Texture texture) {

	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scaleX, scaleY);

	return gameObject;
}


GameObject* Scene::CreateBackgroundGameObject(const std::string& name, float x, float y, const sf::Texture texture) {
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);

	float scalerX = (float)WindowManager::GetWindow()->getSize().x / texture.getSize().x;
	float scalerY = (float)WindowManager::GetWindow()->getSize().y / texture.getSize().y;
	sprite->SetScale(scalerX, scalerY);
	sprite->SetSprite();

	return gameObject;
}


GameObject* Scene::CreateSliderGameObject(const std::string& name, float _x, float _y, float _widthBar, float _heightBar, float _widthCursor, float _heightCursor, unsigned int _fontSize, float _data, float _maxData) {
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Slider* slider = gameObject->CreateComponent<Slider>();
	slider->SetMaxData(_maxData);
	slider->SetData(_data);
	slider->SetSizeBar(_widthBar, _heightBar);
	slider->SetSizeCursor(_widthCursor, _heightCursor);
	slider->SetCursorText(_fontSize);
	slider->SetTitleText();
	slider->SetPosition(_x, _y);

	return gameObject;
}

GameObject* Scene::CreateSliderGameObject(const std::string& name, float _x, float _y, float _widthBar, float _heightBar, float _widthCursor, float _heightCursor, unsigned int _fontSize, float _data, float _minData, float _maxData) {
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Slider* slider = gameObject->CreateComponent<Slider>();
	slider->SetMaxData(_maxData);
	slider->SetMinData(_minData);
	slider->SetData(_data);
	slider->SetSizeBar(_widthBar, _heightBar);
	slider->SetSizeCursor(_widthCursor, _heightCursor);
	slider->SetCursorText(_fontSize);
	slider->SetTitleText();
	slider->SetPosition(_x, _y);

	return gameObject;
}

GameObject* Scene::CreateInputGameObject(std::string _name, float _x, float _y)
{
	GameObject* gameObject = CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Input* input = gameObject->CreateComponent<Input>();
	input->SetInput(50);
	input->SetPosition(_x, _y);
	input->SetOrigin();
	input->SetSize(WindowManager::GetWindowWidth() / 1.5, WindowManager::GetWindowWidth() / 8);

	return gameObject;
}
#pragma once
#include "Scene.h"
class SceneLoginSignup : public Scene
{
public:
	SceneLoginSignup(sf::RenderWindow* _window);
	void Create() override;
	void Update(sf::Time _delta) override;
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* loginName;
	GameObject* loginPassWord;
	GameObject* buttonLogin;

	GameObject* signupName;
	GameObject* signupPassWord;
	GameObject* buttonSignup;

	GameObject* buttonReturn;
};


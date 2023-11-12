#pragma once
#include "Scene.h"
#include "SceneGameAbstract.h"

class SceneCreditsMenu : public Scene
{
public:
	SceneCreditsMenu(sf::RenderWindow* window);

	void CreateSceneButtonsMenu();
	void LoadCreditsTexture();

	GameObject* CreateCreditsGameObject(const std::string& name, float positionx, float positiony, const sf::Texture texture, float scalex, float scaley);

	void AnimCredits(float _deltaSeconds, float _iteration, int _totalLoop);

	void SetOrigin();

	void Create() override;
	void Render(sf::RenderWindow* _window) override;
	void Update(sf::Time _delta) override;
private:
	GameObject* creditsButton = nullptr;
	GameObject* backButton = nullptr;
	GameObject* credits = nullptr;
	std::vector<GameObject*> imagesCredits;
	std::vector<GameObject*> texteCredits;
	std::vector<std::string> allTexteCredits = {
		"Game Master : LAHALLE Fran�ois\nD�veloppeur : LAHALLE Fran�ois\n",
		"D�veloppeur : LEFORESTIER Quentin\nDiagramme Production : LEFORESTIER Quentin",
		"D�veloppeur : Maurad",
		"D�veloppeur : DIFALLAH Ka�s\nDiagramme Production : DIFALLAH Ka�s",
		"D�veloppeur : ROY Hugo",
		"D�veloppeur : BRU Arthur\nSound Production : BRU Arthur\nAssets Production : BRU Arthur"
	};
	sf::Text text;

	float deltaSeconds = 0.f;
	float iteration = 2.f;
	int totalLoop = 1;
	bool goodPosCredits;
	float startPosFrancoisX;
	float startPosFrancoisY;
};



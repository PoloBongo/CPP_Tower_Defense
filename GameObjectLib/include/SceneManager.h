#pragma once

#include <iostream>
#include <map>

#include "Scene.h"
#include "Scenes/SceneMainMenu.h"
#include "Scenes/SceneGameAbstract.h"
#include "Scenes/SceneSuccessMenu.h"

class SceneManager
{
public:

	//Add a new scene to the scene list
	template <typename T> 
	static void AddScene(std::string _key, T* _scene) {
		SceneManager::scenes.insert(std::make_pair(_key, _scene));
	}

	//Run a scene
	static void RunScene(std::string _key);

	//Stop a scene (don't forget to run a scene after calling this function)	
	static void StopScene();

	//Get the current scene
	static Scene* GetActiveScene() { return activeScene; }
	static SceneGameAbstract* GetActiveGameScene() { return static_cast<SceneGameAbstract*>(activeScene); }
	static Scene* GetSceneByKey(std::string _key) { return scenes.at(_key); }

	~SceneManager();

private:
	static std::map<std::string, Scene*> scenes;
	static Scene* activeScene;
};


#include "SceneManager.h"

Scene* SceneManager::activeScene = nullptr;
std::map<std::string, Scene*> SceneManager::scenes;


void SceneManager::StopScene() {
	SceneManager::activeScene = nullptr; 
}

void SceneManager::RunScene(std::string _key) {
	if (SceneManager::scenes.find(_key) != SceneManager::scenes.end()) {
		if (SceneManager::activeScene) {
			SceneManager::activeScene->Delete();
			SceneManager::StopScene();
		}
		SceneManager::activeScene = scenes.at(_key);
		SceneManager::activeScene->Create();
	}
}

SceneManager::~SceneManager() {
	delete SceneManager::activeScene;
	for (const auto scene : SceneManager::scenes)
	{
		delete scene.second;
	}
	SceneManager::scenes.clear();
}
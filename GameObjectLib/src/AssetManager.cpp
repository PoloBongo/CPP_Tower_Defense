#include "AssetManager.h"

std::map<std::string, sf::Texture*> AssetManager::assets;

 void AssetManager::AddAsset(std::string _key, std::string _fileName)
{
	 sf::Texture* texture = new sf::Texture();
	if (AssetManager::assets.find(_key) == AssetManager::assets.end()) {
		AssetManager::assets.insert(std::make_pair(_key, texture));
		if (AssetManager::assets.find(_key) != AssetManager::assets.end()) {
			AssetManager::assets.at(_key)->loadFromFile(_fileName);
		}
	}
}

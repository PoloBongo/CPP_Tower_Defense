#pragma once
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
class AssetManager
{
public:
	//Add a new asset to the assets list
	static void AddAsset(std::string _key, std::string _fileName);

	//Get an asset by its key
	static sf::Texture* GetAsset(std::string _key) { return assets.at(_key); }

private:
	static std::map<std::string, sf::Texture*> assets;
};


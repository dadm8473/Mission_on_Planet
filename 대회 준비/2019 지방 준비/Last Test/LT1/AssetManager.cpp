#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture("key", L"filename", L"png", maxScene);

	// Player
	LoadTexture("Player", L"images/Player/player00", L"png", 1);

	// Tile
	LoadTexture("Tile", L"images/Tile/tile00", L"png", 3);

	// Map
	LoadTexture("Mid", L"images/Map/mid00", L"png", 1);
	LoadTexture("Sky", L"images/Map/sky00", L"png", 1);

	// Score
	LoadTexture("Apb", L"images/APB/apb00", L"png", 26);
	LoadTexture("Num", L"images/Num/Num", L"png", 10);

	// Main
	LoadTexture("Title", L"images/Title/title00", L"png", 4);

	LoadTexture("HowTo", L"images/Title/HowTo00", L"png", 1);
	LoadTexture("Rank", L"images/Title/Rank00", L"png", 1);

	LoadTexture("Win", L"images/Ending/Win00", L"png", 1);
	LoadTexture("Lose", L"images/Ending/Lose00", L"png", 1);
}

void AssetManager::ReleaseAssets()
{
	for (auto it = textures.begin(); it != textures.end(); ++it)
		if (it->second)
			delete it->second;
	textures.clear();
}

void AssetManager::LoadTexture(string key, LPCWSTR filename, LPCWSTR extname, int maxScene)
{
	if (textures.find(key) != textures.end())
		return;

	textures[key] = new CTexture(filename, extname, maxScene);
}

CTexture * AssetManager::GetTexture(string key)
{
	if (textures.find(key) == textures.end())
		return NULL;
	return textures[key];
}

#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture("key", L"filename", L"png", maxScene);

	LoadTexture("Player", L"images/Player/Player", L"png", 1);

	LoadTexture("Object", L"images/Object/object", L"png", 1);

	LoadTexture("Effect", L"images/Effect/effect", L"png", 3);

	LoadTexture("Num", L"images/Num/Num", L"png", 10);
	LoadTexture("Apb", L"images/Apb/apb00", L"png", 26);

	LoadTexture("Tile", L"images/Tile/tile00", L"png", 3);

	LoadTexture("Mid", L"images/Map/Mid", L"png", 1);
	LoadTexture("Sky", L"images/Map/Sky", L"png", 1);

	LoadTexture("Title", L"images/Main/Title/title", L"png", 4);
	LoadTexture("HowTo", L"images/Main/Title/HowTo", L"png", 1);
	LoadTexture("Rank", L"images/Main/Title/Rank", L"png", 1);

	LoadTexture("Win", L"images/Main/Ending/Win", L"png", 1);
	LoadTexture("Lose", L"images/Main/Ending/Lose", L"png", 1);
}

void AssetManager::ReleaseAssets()
{
	for (map<string, CTexture*>::iterator it = textures.begin(); it != textures.end(); ++it)
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

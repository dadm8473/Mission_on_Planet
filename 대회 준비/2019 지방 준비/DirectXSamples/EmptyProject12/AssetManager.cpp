#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture("key", L"filename", L"png", maxScene);
	LoadTexture("Title", L"images/Main/TitleScene/Title00", L"png", 4);
	LoadTexture("HowTo", L"images/Main/TitleScene/HowTo00", L"png", 1);
	LoadTexture("Rank", L"images/Main/TitleScene/Ranking00", L"png", 1);
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

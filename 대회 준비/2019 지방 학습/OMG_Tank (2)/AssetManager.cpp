#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture("키값", L"경로", L"png", 프레임);

	LoadTexture("Player1", L"images/Player/Player1/player001", L"png", 20);
	LoadTexture("Player2", L"images/Player/Player2/player002", L"png", 20);
	LoadTexture("Player3", L"images/Player/Player3/player000", L"png", 20);

	LoadTexture("Rock", L"images/Object/Rock", L"png", 1);
	LoadTexture("Trap", L"images/Object/Trap", L"png", 1);

	LoadTexture("Bullet", L"images/Bullet/Bullet", L"png", 1);

	LoadTexture("Item", L"images/Item/item", L"png", 6);
	LoadTexture("Container", L"images/Item/Container", L"png", 1);

	LoadTexture("Tile", L"images/Tile/tile00", L"png", 3);

	LoadTexture("Sky", L"images/Map/Sky", L"png", 2);
	LoadTexture("Mid", L"images/Map/map00", L"png", 2);

	LoadTexture("Num", L"images/Num/Num", L"png", 10);

	LoadTexture("Title", L"images/Main/TitleScene/Title00", L"png", 4);
	LoadTexture("HowTo", L"images/Main/TitleScene/HowTo00", L"png", 1);
	LoadTexture("Rank", L"images/Main/TitleScene/Ranking00", L"png", 1);

	LoadTexture("Win", L"images/Main/EndingScene/VicTory00", L"png", 1);
	LoadTexture("Lose", L"images/Main/EndingScene/Lose00", L"png", 1);
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

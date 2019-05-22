#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture("키값", L"경로", L"png", 프레임);

	LoadTexture("Tile", L"images/Tile/tile00", L"png", 3);

	LoadTexture("Sky", L"images/Map/Sky", L"png", 2);
	LoadTexture("Mid", L"images/Map/Mid", L"png", 2);

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
	{
		MessageBox(DXUTGetHWND(), L"텍스쳐 키 중복!", L"", MB_OK);
		return;
	}

	textures[key] = new CTexture(filename, extname, maxScene);
}

CTexture * AssetManager::GetTexture(string key)
{
	if (textures.find(key) == textures.end())
		return NULL;

	return textures[key];
}

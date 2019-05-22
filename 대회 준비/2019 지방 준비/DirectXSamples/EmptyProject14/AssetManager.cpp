#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture("key", L"filename", L"png", maxScene);

	LoadTexture("Title", L"images/Main/TitleScene/Title00", L"png", 4);
	LoadTexture("HowTo", L"images/Main/TitleScene/HowTo00", L"png", 1);
	LoadTexture("Rank", L"images/Main/TitleScene/Rank00", L"png", 1);

	LoadTexture("Win", L"images/Main/EndingScene/Victory00", L"png", 1);
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
	{
		MessageBox(DXUTGetHWND(), L"텍스쳐 키 오류!", L"", MB_OK);
		return NULL;
	}

	return textures[key];
}

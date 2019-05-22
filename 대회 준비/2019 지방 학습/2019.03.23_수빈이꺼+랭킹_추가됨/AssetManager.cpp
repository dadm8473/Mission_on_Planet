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
	LoadTexture("Player1_Die", L"images/Player/PlayerDie/dead01", L"png", 30);
	LoadTexture("Player2_Die", L"images/Player/PlayerDie/dead02", L"png", 30);
	LoadTexture("Player3_Die", L"images/Player/PlayerDie/dead00", L"png", 30);

	LoadTexture("Enemy1", L"images/Enemy/Enemy1/enemy00", L"png", 30);
	LoadTexture("Enemy2", L"images/Enemy/Enemy2/enemy01", L"png", 20);

	LoadTexture("Rock", L"images/Object/Rock", L"png", 1);
	LoadTexture("Trap", L"images/Object/Trap00", L"png", 1);

	LoadTexture("Bullet", L"images/Bullet/Bullet", L"png", 1);
	LoadTexture("ClearAttack", L"images/Effect/ClearAttack//effect00", L"png", 40);
	LoadTexture("ClearAttackUI", L"images/ClearAttack/bum002", L"png", 1);

	LoadTexture("effect", L"images/Effect/폭파/ㅇㅍ/effect01", L"png", 20);

	LoadTexture("Item", L"images/Item/item", L"png", 6);
	LoadTexture("ItemMessage", L"images/UI/ItemMessage/item", L"png", 8);
	LoadTexture("Container", L"images/Item/Container00", L"png", 1);

	LoadTexture("Tile", L"images/Tile/tile00", L"png", 3);

	LoadTexture("Sky", L"images/Map/map03", L"png", 1);
	LoadTexture("Mid", L"images/Map/map00", L"png", 2);

	LoadTexture("UI", L"images/UI/ui00", L"png", 1);
	LoadTexture("PlayerLife", L"images/UI/life00", L"png", 1);

	LoadTexture("Num", L"images/UI/Number/num00", L"png", 10);

	LoadTexture("PlayerIcon", L"images/UI/hollo01", L"png", 1);
	LoadTexture("MiniMap", L"images/UI/minimap00", L"png", 1);

	LoadTexture("Title", L"images/Main/main/main01", L"png", 5);
	LoadTexture("TitleBG", L"images/Main/main/main02", L"png", 1);
	LoadTexture("Tank", L"images/Main/main/main00", L"png", 20);

	LoadTexture("HowTo", L"images/Main/TitleScene/HowTo00", L"png", 1);
	LoadTexture("Rank", L"images/Main/TitleScene/Ranking00", L"png", 1);
	LoadTexture("Kredit", L"images/Main/TitleScene/Kredit", L"png", 1);

	LoadTexture("Intro", L"images/Main/Intro/intero00", L"png", 40);

	LoadTexture("Win", L"images/Main/EndingScene/VicTory00", L"png", 1);
	LoadTexture("Lose", L"images/Main/EndingScene/Lose00", L"png", 1);

	LoadTexture("Alphabet", L"images/UI/alphabet/apb_", L"png", 26);
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

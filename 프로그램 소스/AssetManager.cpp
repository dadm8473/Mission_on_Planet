#include "DXUT.h"
#include "Header.h"


AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssts_Sound(string key, LPWSTR filename, float maxBuffer)
{
	soundManager->Create(&sounds[key], filename, 0, GUID_NULL, maxBuffer);
}

void AssetManager::LoadAssets()
{
	// LoadTexture("key", L"filename", L"png", maxScene);

	// Player
	LoadTexture("Player", L"images/Player/Player1/player00", L"png", 20);
	LoadTexture("Player1", L"images/Player/Player2/player00", L"png", 20);
	LoadTexture("Player2", L"images/Player/Player3/player00", L"png", 20);
	
	// Enemy
	LoadTexture("Enemy1", L"images/Enamy/1스테이지 우주선/enamy00", L"png", 20);
	LoadTexture("Enemy2", L"images/Enamy/1스테이지 전투기/enamy00", L"png", 20);
	LoadTexture("Enemy3", L"images/Enamy/2스테이지 우주선/enamy00", L"png", 20);
	LoadTexture("Enemy4", L"images/Enamy/2스테이지 전투기/enamy00", L"png", 20);

	// Bullet
	LoadTexture("Bullet", L"images/Bullet/Bullet00", L"png", 1);
	LoadTexture("PlayerBullet_1", L"images/Bullet/플레이어/주포/bullet01", L"png", 1);
	LoadTexture("PlayerBullet_2", L"images/Bullet/플레이어/대공포/bullet00", L"png", 1);
	LoadTexture("EnemyBullet_1", L"images/Bullet/적/수직/bullet1", L"png", 1);
	LoadTexture("EnemyBullet_2", L"images/Bullet/적/대각/bullet", L"png", 1);

	LoadTexture("clearAttackCount", L"images/Bullet/적/수직/bullet", L"png", 1);

	// Object
	LoadTexture("Rock", L"images/Object/rock00", L"png", 2);// 돌
	LoadTexture("Hole", L"images/Object/Hole00", L"png", 1);// 구멍
	LoadTexture("StageClear", L"images/Object/StageClear00", L"png", 1);//StageClear

	// Item
	LoadTexture("Item", L"images/Item//아이콘/item", L"png", 6);
	LoadTexture("Item1", L"images/Item/2단점프/item00", L"png", 10);
	LoadTexture("Item2", L"images/Item/Speedup//item00", L"png", 10);
	LoadTexture("Item3", L"images/Item/사거리/item00", L"png", 10);
	LoadTexture("Item4", L"images/Item/3방향공격/item00", L"png", 10);
	LoadTexture("Item5", L"images/Item/유도미사일/item00", L"png", 10);
	LoadTexture("Item6", L"images/Item/핵탄두/item00", L"png", 10);

	// 컨테이너
	LoadTexture("Upgrade", L"images/Item/upgrade00", L"png", 1);

	// Item Message
	LoadTexture("ItemMessage", L"images/itemMessage/mes00", L"png", 7);

	//UI
	LoadTexture("Num", L"images/Num/num", L"png", 10);
	LoadTexture("Num_B", L"images/Num/num1", L"png", 10);
	LoadTexture("Apb", L"images/APB/apb00", L"png", 26);
	LoadTexture("Black", L"images/Black00", L"png", 1);

	// PlayerLife
	LoadTexture("PlayerLife", L"images/UI/Life/life", L"png", 3);

	// Player Image
	LoadTexture("PlayerImage", L"images/UI/image/ui", L"png", 3);

	// Main UI
	LoadTexture("MainUI", L"images/UI/ui", L"png", 2);

	// Item CoolTime
	LoadTexture("ItemCool", L"images/UI/itemCool00", L"png", 1);

	// Clear Cool
	LoadTexture("ClaerCool", L"images/UI/clearCool00", L"png", 1);

	// Stage
	LoadTexture("StageStart_Mes", L"images/Stage/Stage", L"png", 2);
	LoadTexture("StageClear_Mes", L"images/Stage/StageClear", L"png", 2);
	LoadTexture("Continue", L"images/Stage/Conti/Con00", L"png", 10);
	LoadTexture("Over", L"images/Stage/Conti/Over00", L"png", 1);

	// Mini Map
	LoadTexture("MiniMap", L"images/Minimap/minimap00", L"png", 1);
	LoadTexture("SavePoint", L"images/Minimap/Save/seve00", L"png", 1);
	LoadTexture("PlayerPoint", L"images/Minimap/Player/mini00", L"png", 1);

	// Effect
	LoadTexture("Effect", L"images/Effect/bulleteffect/effect00", L"png", 15);
	LoadTexture("Effect_Player", L"images/Effect/플레이어폭팔/effect00", L"png", 20);
	LoadTexture("Effect_Enemy", L"images/Effect/적폭팔/effect00", L"png", 20);
	LoadTexture("Effect_Clear", L"images/Effect/핵폭팔/effect00", L"png", 20);

	// Tile
	LoadTexture("Tile", L"images/Tile/tile00", L"png", 4);
	LoadTexture("Tile2", L"images/Tile/2스테이지/tile", L"png", 4);
	// End Tile
	LoadTexture("EndTile", L"images/Tile/EndTile", L"png", 2);
	LoadTexture("conEffect", L"images/Coneffect/conefect00", L"png", 20);
	

	// Map
	LoadTexture("Mid", L"images/Map/1스테이지/map02", L"png", 2);
	LoadTexture("Mid3", L"images/Map/2스테이지/map02", L"png", 2);

	LoadTexture("Mid2", L"images/Map/1스테이지/map01", L"png", 2);
	LoadTexture("Sky", L"images/Map/1스테이지/map00", L"png", 1);

	// Title
	LoadTexture("Title", L"images/Main/Title/main00", L"png", 6);
	LoadTexture("Intro", L"images/Main/Title/Intro/intro00", L"png", 60);
	LoadTexture("HowTo", L"images/Main/Title/howto", L"png", 3);
	LoadTexture("Rank", L"images/Main/Title/ranking", L"png", 1);
	LoadTexture("iu", L"images/Main/Title/iu00", L"png", 1);
	LoadTexture("Kredit", L"images/Main/Title/Kredit00", L"png", 1);

	LoadTexture("mainAni", L"images/Main/Title/메인 애니메이션/main00", L"png", 20);

	// Ending
	LoadTexture("Win", L"images/Main/Ending/승리/win00", L"png", 20);
	LoadTexture("Lose", L"images/Main/Ending/패배/lose00", L"png", 20);
	LoadTexture("Rank_end", L"images/Main/Ending/랭킹/ranking", L"png", 2);
	LoadTexture("Black_E", L"images/Black01", L"png", 1);

	// Sound
	soundManager = new CSoundManager;
	soundManager->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
	soundManager->SetPrimaryBufferFormat(2, 22050, 16);

	LoadAssts_Sound("Main", L"Sound/Main.wav", 1);
	LoadAssts_Sound("Die", L"Sound/Die.wav", 10);
	LoadAssts_Sound("Effect", L"Sound/Effect.wav", 20);
	LoadAssts_Sound("Clear", L"Sound/ClearAttack.wav", 1);
	LoadAssts_Sound("Lose", L"Sound/Lose.wav", 1);
	LoadAssts_Sound("Stage1", L"Sound/Stage1.wav", 1);
	LoadAssts_Sound("Stage2", L"Sound/Stage2.wav", 1);
	LoadAssts_Sound("Upgrade", L"Sound/Upgrade.wav", 1);
	LoadAssts_Sound("Win", L"Sound/Win.wav", 1);
}

void AssetManager::ReleaseAssets()
{
	for (auto it = textures.begin(); it != textures.end(); ++it)
		if (it->second)
			delete it->second;
	textures.clear();

	for (auto it = sounds.begin(); it != sounds.end(); ++it)
		if (it->second)
			delete it->second;
	delete soundManager;
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

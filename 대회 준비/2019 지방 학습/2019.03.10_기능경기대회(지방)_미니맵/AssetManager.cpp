#include "DXUT.h"
#include "Header.h"

CAssetManager*gAssetManager;

void CAssetManager::InitAssets()
{
	map_Sky_Texture = new CTexture(L"Images/Map/Sky_", L"png", 2);
	map_Mid_Texture = new CTexture(L"Images/Map/Mid_", L"png", 2);

	tile_Texture = new CTexture(L"Images/Tile/Tile_", L"png", 3);
	item_Texture = new CTexture(L"Images/Item/Item_", L"png", 6);
	container_Texture = new CTexture(L"Images/Item/Container_", L"png", 1);

	player_1_Texture = new CTexture(L"Images/Player/Tank_1_", L"png", 1);
	player_2_Texture = new CTexture(L"Images/Player/Tank_2_", L"png", 1);
	player_3_Texture = new CTexture(L"Images/Player/Tank_3_", L"png", 1);

	enemy_Type1_Stage1_Texture = new CTexture(L"Images/Enemy/Enemy_Type1_1_", L"png", 1);
	enemy_Type1_Stage2_Texture = new CTexture(L"Images/Enemy/Enemy_Type1_2_", L"png", 1);
	enemy_Type2_Stage1_Texture = new CTexture(L"Images/Enemy/Enemy_Type2_1_", L"png", 1);
	enemy_Type2_Stage2_Texture = new CTexture(L"Images/Enemy/Enemy_Type2_2_", L"png", 1);

	playerBulletTexture = new CTexture(L"Images/Bullet/P_N_Bullet_", L"png", 1);
	playerHomingBulletTexture = new CTexture(L"Images/Bullet/P_H_Bullet_", L"png", 1);
	enemyBulletTexture = new CTexture(L"Images/Bullet/E_D_Bullet_", L"png", 1);

	object_TrapTexture = new CTexture(L"Images/Object/Object_Trap_", L"png", 1);
	object_RockTexture = new CTexture(L"Images/Object/Object_Rock_", L"png", 1);

	titleTexture = new CTexture(L"Images/Main/시작화면00", L"png", 4);
	howtoTexture = new CTexture(L"Images/Main/게임방법00", L"png", 1);

	victoryTexture = new CTexture(L"Images/Main/미션성공00", L"png", 1);
	gameoverTexture = new CTexture(L"Images/Main/게임오버00", L"png", 1);

	numberTexture = new CTexture(L"Images/UI/num/num", L"png", 10);

	checkPointMessage = new CTexture(L"Images/UI/CheckPoint_", L"png", 1);
	stageClearMessage = new CTexture(L"Images/UI/StageClear_", L"png", 1);
	upgradeMessage = new CTexture(L"Images/UI/Upgrade_", L"png", 1);

	miniMapBar = new CTexture(L"Images/UI/minimap", L"png", 1);
	playerIcon = new CTexture(L"Images/UI/playericon", L"png", 1);
}

void CAssetManager::TermAssets()
{
	delete map_Sky_Texture;
	delete map_Mid_Texture;

	delete tile_Texture;
	delete item_Texture;
	delete container_Texture;

	delete player_1_Texture;
	delete player_2_Texture;
	delete player_3_Texture;

	delete enemy_Type1_Stage1_Texture;
	delete enemy_Type1_Stage2_Texture;
	delete enemy_Type2_Stage1_Texture;
	delete enemy_Type2_Stage2_Texture;

	delete playerBulletTexture;
	delete playerHomingBulletTexture;
	delete enemyBulletTexture;

	delete object_TrapTexture;
	delete object_RockTexture;

	delete titleTexture;
	delete howtoTexture;

	delete victoryTexture;
	delete gameoverTexture;

	delete numberTexture;

	delete checkPointMessage;
	delete stageClearMessage;
	delete upgradeMessage;

	delete miniMapBar;
	delete playerIcon;
}
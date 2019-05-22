#pragma once

class CAssetManager
{
public:
	CTexture* map_Sky_Texture;
	CTexture* map_Mid_Texture;

	CTexture* tile_Texture;
	CTexture* item_Texture;
	CTexture* container_Texture;

	CTexture* player_1_Texture;
	CTexture* player_2_Texture;
	CTexture* player_3_Texture;

	CTexture* enemy_Type1_Stage1_Texture;
	CTexture* enemy_Type1_Stage2_Texture;
	CTexture* enemy_Type2_Stage1_Texture;
	CTexture* enemy_Type2_Stage2_Texture;

	CTexture* playerBulletTexture;
	CTexture* playerHomingBulletTexture;
	CTexture* enemyBulletTexture;

	CTexture* object_TrapTexture;
	CTexture* object_RockTexture;

	CTexture* titleTexture;
	CTexture* howtoTexture;

	CTexture* victoryTexture;
	CTexture* gameoverTexture;

	CTexture* numberTexture;

	CTexture* checkPointMessage;
	CTexture* stageClearMessage;
	CTexture* upgradeMessage;

	// minimap
	CTexture* miniMapBar;
	CTexture* playerIcon;
	
	// ·©Å·
	CTexture* alphabetTexture;
	CTexture* rankingBackgroundTexture;

	void InitAssets();
	void TermAssets();
};

extern CAssetManager*gAssetManager;
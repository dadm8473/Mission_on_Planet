#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), type(type), isDie(false), isDestroyed(false)
{
	position = pos;

	center.x = 100;
	center.y = 50;

	hp = 50;
}

void CEnemy::Update(float deltaTime)
{
	position.x -= 100 * deltaTime;

	// ī�޶� ������ ������ �� ������Ʈ�� ����� ���� ���ǹ�
	// ���� �˳��ϰ� �������ش�.
	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroyed = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	if (type == 0)
		Draw(sprite, gAssetManager->enemy_Type1_Stage1_Texture);
	else if (type == 1)
		Draw(sprite, gAssetManager->enemy_Type2_Stage1_Texture);
}
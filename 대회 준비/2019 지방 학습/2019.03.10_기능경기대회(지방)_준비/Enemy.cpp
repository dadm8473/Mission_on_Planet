#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), type(type), isDestroyed(false), parentScene(NULL), hp(0), isDie(false),
	attackTime(0.3f), attackTimer(0), exitTime(2), exitTimer(0), exit(false), speed(0)
{
	position = pos;

	if (type == 0)
	{
		hp = 60;

		center.x = 128;
		center.y = 75;
	}
	else if (type == 1)
	{
		hp = 35;

		center.x = 100;
		center.y = 50;

		speed = 400;

		attackTime = 1;
	}
	else if (type == 2)
	{
		hp = 50;

		center.x = 100;
		center.y = 50;

		speed = 256;

		attackTime = 0.66f;
	}
}

void CEnemy::Update(float deltaTime)
{
	if (type == 0) // 돌 or 장애물
	{
		// 중력 적용
		velocity_Y -= 32 * deltaTime;
		// velocity_Y의 값이 +면 상승하고 -면 하강하기위해 부호를 반전시킵니다.
		position.y -= velocity_Y;

		// 씬에 생성되있는 타일을 검사하여 현재 서있는 땅의 위치를 알아낸다.
		if (parentScene)
		{
			// 타일의 가로 길이를 이용하여 현재 서있는 위치를 알 수 있다.
			int tileIndex = position.x / gAssetManager->tile_Texture->width;
			if (parentScene->tileList.size() > tileIndex
				&& tileIndex >= 0)  // 타일리스트 사이즈를 넘을 경우를 예외처리
			{
				ground_Y_Pos = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			}
		}

		// 땅에 닿았다.
		if (position.y > ground_Y_Pos)
		{
			position.y = ground_Y_Pos;
			velocity_Y = 0.0f;
		}

		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);
	}
	else if (type == 1) // 아래에 폭탄을 쏘는 적
	{
		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			//아래를 향해
			CBullet* b = new CBullet(camera, position, 2, 280, 180.0f, 10, 999.0f);
			b->parentScene = parentScene;

			parentScene->enemyBulletList.push_back(b);

			attackTimer = 0;
		}

		position.x -= speed * deltaTime;

		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);
	}
	else if (type == 2) // 플레이어를 향해 총알을 발사
	{
		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			float angle = 180;
			if (parentScene->player)
			{
				angle = GetAngle(
					parentScene->player->position.x - position.x,
					parentScene->player->position.y - position.y
				);
			}

			CBullet* b = new CBullet(camera, position, 2, 280, angle, 10, 999.0f);
			b->parentScene = parentScene;

			parentScene->enemyBulletList.push_back(b);

			attackTimer = 0;
		}

		if (!exit)
		{
			exitTimer += deltaTime;
			if (exitTimer >= exitTime)
			{
				exit = true;
			}

			speed -= 256 * deltaTime;

			if (speed <= 0)
				speed = 0;
		}
		else
		{
			speed -= 256 * deltaTime;
		}
		position.x += speed * deltaTime;

		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);
	}

	if ((position.x < camera->position.x - 256 || position.x > camera->position.x + 1280) && type != 0) // 돌 or 장애물은 화면 밖으로 나가도 사라지지 않음
		isDestroyed = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	if (type == 0)
		Draw(sprite, gAssetManager->object_RockTexture);
	else if (type == 1)
		Draw(sprite, gAssetManager->enemy_Type1_Stage1_Texture);
	else if (type == 2)
		Draw(sprite, gAssetManager->enemy_Type2_Stage1_Texture);
}
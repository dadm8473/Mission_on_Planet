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
	if (type == 0) // �� or ��ֹ�
	{
		// �߷� ����
		velocity_Y -= 32 * deltaTime;
		// velocity_Y�� ���� +�� ����ϰ� -�� �ϰ��ϱ����� ��ȣ�� ������ŵ�ϴ�.
		position.y -= velocity_Y;

		// ���� �������ִ� Ÿ���� �˻��Ͽ� ���� ���ִ� ���� ��ġ�� �˾Ƴ���.
		if (parentScene)
		{
			// Ÿ���� ���� ���̸� �̿��Ͽ� ���� ���ִ� ��ġ�� �� �� �ִ�.
			int tileIndex = position.x / gAssetManager->tile_Texture->width;
			if (parentScene->tileList.size() > tileIndex
				&& tileIndex >= 0)  // Ÿ�ϸ���Ʈ ����� ���� ��츦 ����ó��
			{
				ground_Y_Pos = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			}
		}

		// ���� ��Ҵ�.
		if (position.y > ground_Y_Pos)
		{
			position.y = ground_Y_Pos;
			velocity_Y = 0.0f;
		}

		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);
	}
	else if (type == 1) // �Ʒ��� ��ź�� ��� ��
	{
		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			//�Ʒ��� ����
			CBullet* b = new CBullet(camera, position, 2, 280, 180.0f, 10, 999.0f);
			b->parentScene = parentScene;

			parentScene->enemyBulletList.push_back(b);

			attackTimer = 0;
		}

		position.x -= speed * deltaTime;

		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);
	}
	else if (type == 2) // �÷��̾ ���� �Ѿ��� �߻�
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

	if ((position.x < camera->position.x - 256 || position.x > camera->position.x + 1280) && type != 0) // �� or ��ֹ��� ȭ�� ������ ������ ������� ����
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
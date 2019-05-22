#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)
	:CMatrix(), attackTimer(0), attackTime(0.05f), attackIntervalTimer(0), attackIntervalTime(0.5f),
	isAttacking(false), isAttackInterval(false), isDie(false), isInvincible(true), invincibleTimaer(0), invincibleTimae(2), upgrade(0), camera(camera), velocity_Y(0), jumpCount(1),
	mainAttackCounter(0), mainAttackCount(1), skyAttackCounter(0), skyAttackCount(5), homingAttackCounter(0), homingAttackCount(2),
	homingMissile(10.0f),
	longShot(10.0f),
	powerUp(10.0f),
	doubleJump(10.0f),
	speedUp(false)
{
	position = pos;
	ground_Y_Pos = pos.y;
	center = D3DXVECTOR2(100, 50);

	// SetAnimation(40, 0.001f, true);
}

void CPlayer::Update(float deltaTime)
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
			float y = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (y != 0) ground_Y_Pos = y;
		}
	}
	
	// ���� ��Ҵ�.
	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0.0f;
		
		if(!doubleJump.on || upgrade == 2) // ���� ���� ������ ȿ���� 3�ܰ� �߰����� ���� ���� �Ұ�
			jumpCount = 1;
		else
			jumpCount = 2;
	}

	CMatrix::Update(deltaTime, camera->position);

	SetRect(&rect, position.x - 10, position.y - 10, position.x + 10, position.y + 10);

	attackTimer += deltaTime;
	if (isAttacking)
	{
		if (attackTimer >= attackTime)
		{
			attackTimer = 0;

			if (parentScene) // ������ ���� ���� �����������
			{
				// ������ ��
				if (mainAttackCounter++ < mainAttackCount)
				{
					float speed = 100.0f;
					if (longShot.on) // �ռ� ������ȿ�� ��Ÿ� �ִ�
						speed = 2048;
					else
					{
						switch (upgrade) // ���׷��̵忡 ���� ��Ÿ� ��ȭ
						{
						case 0:
							speed = 1024;
							break;
						case 1:
							speed = 1536;
							break;
						case 2:
							speed = 2048;
							break;
						}
					}
				
					CBullet* b = new CBullet(camera, position - D3DXVECTOR2(0, 50), 0, speed, 80.0f, 100, 999.0f);
					b->parentScene = parentScene;
					parentScene->playerBulletList.push_back(b);
				}


				// ���� ��
				if (skyAttackCounter++ < skyAttackCount)
				{
					CBullet* b = new CBullet(camera, position, 1, 1536, 45, 6, 0.5f);
					b->parentScene = parentScene;
					parentScene->playerBulletList.push_back(b);
					if (powerUp.on) // ��� 3�ٱ� ������ ȿ��
					{
						b = new CBullet(camera, position, 1, 1536, 45-10.0f, 6, 0.5f);
						b->parentScene = parentScene;
						parentScene->playerBulletList.push_back(b);

						b = new CBullet(camera, position, 1, 1536, 45+10.0f, 6, 0.5f);
						b->parentScene = parentScene;
						parentScene->playerBulletList.push_back(b);
					}
				}

				// ȣ�� �̻���
				if (homingMissile.on)
				{
					if (homingAttackCounter++ < homingAttackCount)
					{
						parentScene->playerBulletList.push_back(new CBullet(camera, position, 1, 1024, 90, 6, 0.3f));
					}
				}

				// ��� źȯ�� ����ϸ� ���� ���� ������ ����
				if (mainAttackCounter >= mainAttackCount &&
					skyAttackCounter >= skyAttackCount &&
					(!homingMissile.on || homingAttackCounter >= homingAttackCount))
				{
					isAttacking = false;

					isAttackInterval = true;
					attackIntervalTimer = 0.0f;
				}
			}
		}
	}

	attackIntervalTimer += deltaTime;
	if (isAttackInterval)
	{
		if (attackIntervalTimer >= attackIntervalTime)
		{
			attackIntervalTimer = 0;
			isAttackInterval = false;
		}
	}

	if (isInvincible)
	{
		a = 150;

		invincibleTimaer += deltaTime;

		if (invincibleTimaer >= invincibleTimae)
		{
			invincibleTimaer = 0;
			isInvincible = false;
		}
	}
	else
	{
		a = 255;
	}

	// ������ ȿ�� ������Ʈ
	homingMissile.Update(deltaTime);
	longShot.Update(deltaTime);
	powerUp.Update(deltaTime);
	doubleJump.Update(deltaTime);
}


void CPlayer::Render(LPD3DXSPRITE sprite)
{
	CMatrix::Render(sprite);

	switch (upgrade)
	{
	case 0:
		Draw(sprite, gAssetManager->player_1_Texture);
		break;
	case 1:
		Draw(sprite, gAssetManager->player_2_Texture);
		break;
	case 2:
		Draw(sprite, gAssetManager->player_3_Texture);
		break;
	}
}

void CPlayer::Move(int dir, float deltaTime)
{
	float speed = 400.0f;
	if (speedUp)
		speed *= 2.0f;

	position.x += dir * speed * deltaTime;
}

void CPlayer::Attack()
{
	if (isAttackInterval || isAttacking) return;

	isAttacking = true;

	mainAttackCounter = 0;
	skyAttackCounter = 0;
	homingAttackCounter = 0;
}

void CPlayer::Jump()
{
	if (jumpCount > 0)
	{
		jumpCount--;
		velocity_Y = 10.0f;
	}
}
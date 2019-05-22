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
			float y = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (y != 0) ground_Y_Pos = y;
		}
	}
	
	// 땅에 닿았다.
	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0.0f;
		
		if(!doubleJump.on || upgrade == 2) // 더블 점프 아이템 효과와 3단계 중갑전차 더블 점프 불가
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

			if (parentScene) // 공격은 게임 씬과 연결되있을때
			{
				// 앞으로 쏴
				if (mainAttackCounter++ < mainAttackCount)
				{
					float speed = 100.0f;
					if (longShot.on) // 롱샷 아이템효과 사거리 최대
						speed = 2048;
					else
					{
						switch (upgrade) // 업그레이드에 따른 사거리 변화
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


				// 위로 쏴
				if (skyAttackCounter++ < skyAttackCount)
				{
					CBullet* b = new CBullet(camera, position, 1, 1536, 45, 6, 0.5f);
					b->parentScene = parentScene;
					parentScene->playerBulletList.push_back(b);
					if (powerUp.on) // 대공 3줄기 아이템 효과
					{
						b = new CBullet(camera, position, 1, 1536, 45-10.0f, 6, 0.5f);
						b->parentScene = parentScene;
						parentScene->playerBulletList.push_back(b);

						b = new CBullet(camera, position, 1, 1536, 45+10.0f, 6, 0.5f);
						b->parentScene = parentScene;
						parentScene->playerBulletList.push_back(b);
					}
				}

				// 호밍 미사일
				if (homingMissile.on)
				{
					if (homingAttackCounter++ < homingAttackCount)
					{
						parentScene->playerBulletList.push_back(new CBullet(camera, position, 1, 1024, 90, 6, 0.3f));
					}
				}

				// 모든 탄환을 사용하면 공격 끄고 딜레이 시작
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

	// 아이템 효과 업데이트
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
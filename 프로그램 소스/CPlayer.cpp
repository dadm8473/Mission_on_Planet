#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * inputCamera)
	: camera(inputCamera), velocity_Y(0), ground_Y_Pos(0), jumpCount(1), speed(250), isDie(false),
	isAttack(false), attackTimer(0.2f), attackTime(0.2f), rich(0.3f), velocity_X(0),
	isAttack_Sky(false), attackTimer_Sky(0.2f), attackTime_Sky(0.2f),
	isMulti(false), isHoming(false), upgrade(0), isDoubleJump(false),
	target1(NULL), target2(NULL), target3(NULL)
{
	position = pos;
	center = D3DXVECTOR2(128, 96);

	ground_Y_Pos = pos.y + 60;

	SetAnimation(0.03f, 20, true);
}

void CPlayer::Update(float deltaTime)
{
	// 중력
	velocity_Y += 32 * deltaTime;
	position.y += velocity_Y;
	position.x += velocity_X;

	//// 업그레이드 테스트
	//switch (upgrade)
	//{
	//case 0:
	//	scale = D3DXVECTOR2(1, 1);
	//	break;
	//case 1:
	//	scale = D3DXVECTOR2(1.2f, 1.2f);
	//	break;
	//case 2:
	//	scale = D3DXVECTOR2(1.4f, 1.4f);
	//	break;
	//default:
	//	scale = D3DXVECTOR2(2, 2); // 오류체크
	//	break;
	//}

	// 플레이어 땅 한계값 받아오기
	if (parentScene)
	{
		int tileIndex = position.x / tileWidth;
		if (tileIndex >= 0 && tileIndex < parentScene->tileList.size())
		{
			float outY = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (outY != 0)
				ground_Y_Pos = outY + 60;

			// 구덩이일 경우
			if (parentScene->tileList[tileIndex]->currentScene == 3)
				ground_Y_Pos = 9999;
		}
	}
	
	// 플레이어 중력
	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0;
		velocity_X = 0;

		if (isDoubleJump)
			jumpCount = 2;
		else
			jumpCount = 1;
	}

	// Attack
	if (isAttack)
	{
		attackTimer += deltaTime;
		if (attackTimer > attackTime)
		{
			parentScene->playerBulletList.push_back(new CBullet(position + D3DXVECTOR2(128, -15), camera, 1, 90, 1000, rich));
			attackTimer = 0;
			isAttack = false;
		}
	}
	
	// Attack Sky
	if (isAttack_Sky)
	{
		attackTimer_Sky += deltaTime;
		if (attackTimer_Sky > attackTime_Sky)
		{
			// Homing Attack
			if (isHoming && (target1 || target2 || target3))
			{
				/*float angle = GetAngle(target->position.x - position.x, target->position.y - position.y);

				if(angle > 0)
					parentScene->playerBulletList.push_back(new CBullet(position, camera, 100, angle, 1000));

				target = NULL;*/

				parentScene->playerBulletList.push_back(new CBullet(position - D3DXVECTOR2(30, 0), camera, 100, 10, 700, 1.5f, target1, target2, target3));
				//parentScene->playerBulletList.push_back(new CBullet(position, camera, 2, 70, 1000, rich + 0.3f));

				target1 = NULL;
				target2 = NULL;
				target3 = NULL;
			}
			else
				parentScene->playerBulletList.push_back(new CBullet(position, camera, 2, 60, 1000, rich + 0.3f));

			// Multi Attack
			if (isMulti)
			{
				parentScene->playerBulletList.push_back(new CBullet(position, camera, 2, 80, 1000, rich + 0.3f));
				parentScene->playerBulletList.push_back(new CBullet(position, camera, 2, 70, 1000, rich + 0.3f));
			}

			attackTimer_Sky = 0;
			isAttack_Sky = false;
		}
	}

	// 충돌
	SetRect(&rect, position.x - 85, position.y - 32, position.x + 85, position.y + 64);
	CMatrix::Update(deltaTime, camera->position);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	switch (upgrade)
	{
	case 0:
		Draw(sprite, gAssetManager->GetTexture("Player"));
		break;
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Player1"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Player2"));
		break;
	}
}

void CPlayer::Move(int dir, float deltaTime)
{
	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	if (--jumpCount >= 0)
	{
		velocity_Y = -13;
		velocity_X = 3;
	}
}

void CPlayer::Attack()
{
	isAttack = true;
}

void CPlayer::Attack_Sky()
{
	isAttack_Sky = true;
}

void CPlayer::DoubleJump()
{
	Reset();
	if (upgrade != 2)
		isDoubleJump = true;
}

void CPlayer::SpeedUp()
{
	Reset();
	speed += 75;

	if (speed > 650)
		speed = 650;
}

void CPlayer::LongAttack()
{
	Reset();
	rich = 1;
}

void CPlayer::MultiAttack()
{
	Reset();
	isMulti = true;
}

void CPlayer::HomingAttack()
{
	Reset();
	isHoming = true;
}

void CPlayer::Reset()
{
	jumpCount = 0;
	isDoubleJump = false;
	rich = 0.4 + upgrade * 0.1f;
	isMulti = false;
	isHoming = false;
}
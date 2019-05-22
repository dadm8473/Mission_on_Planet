#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float destoryTime)
	:CMatrix(), parentScene(NULL), camera(camera), type(type), speed(speed), moveAngle(moveAngle), damage(damage), isDestroyed(false), destroyTime(destoryTime), destroyTimer(0), targetPos(NULL), homingTimer(0), homingTime(0), homingSpeed(0), velocity_Y(0)
{
	position = pos;

	// 플레이어 총알
	if (type == 0)
	{
		center.x = 16;
		center.y = 16;
	}
	// 플레이어 호밍 미사일
	else if (type == 1)
	{
		center.x = 16;
		center.y = 16;
	}
	//적 총알
	else if (type == 2)
	{
		center.x = 16;
		center.y = 16;
	}
}

void CBullet::Update(float deltaTime)
{
	// 씬에 생성되있는 타일을 검사하여 현재 서있는 땅의 위치를 알아낸다.
	if (parentScene)
	{
		// 타일의 가로 길이를 이용하여 현재 서있는 위치를 알 수 있다.
		int tileIndex = position.x / gAssetManager->tile_Texture->width;
		if (parentScene->tileList.size() > tileIndex && 
			tileIndex >= 0)  // 타일리스트 사이즈를 넘을 경우를 예외처리
		{
			ground_Y_Pos = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
		}
	}

	position.x += sin(moveAngle*(D3DX_PI / 180))*speed*deltaTime;
	position.y -= cos(moveAngle*(D3DX_PI / 180))*speed*deltaTime;

	rotation = moveAngle;

	if (type == 0) // 주포 탄환
	{
		// 중력 적용
		velocity_Y -= 10 * deltaTime;
		// velocity_Y의 값이 +면 상승하고 -면 하강하기위해 부호를 반전시킵니다.
		position.y -= velocity_Y;

		SetRect(&rect, position.x - 16, position.y - 16, position.x + 16, position.y + 16);
	}
	else if (type == 1)
	{
		SetRect(&rect, position.x - 16, position.y - 16, position.x + 16, position.y + 16);
	}
	else if (type == 2)
	{
		SetRect(&rect, position.x - 16, position.y - 16, position.x + 16, position.y + 16);
	}

	// 호밍 미사일 움직임
	if (targetPos != NULL)
	{
		homingTimer += deltaTime;
		if (homingTimer > homingTime)
			homingTimer = homingTime;

		float targetAngle = (GetAngle(targetPos->x - position.x, targetPos->y - position.y));
		if (targetAngle >= 180.0f)
			targetAngle -= 360.0f;

		moveAngle += (targetAngle - moveAngle) *  0.5f * (homingTimer / homingTime);
	}

	// 삭제 검사
	// 바닥 검사
	if (position.y > ground_Y_Pos && type != 1 ) // 호밍미사일을 바닥 충돌하지 않음
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0.0f;
		isDestroyed = true;
	}

	// 시간 검사
	destroyTimer += deltaTime;
	if (destroyTimer >= destroyTime)
		isDestroyed = true;

	// 화면 검사
	if (position.x < camera->position.x - 128 || position.x > camera->position.x + 1152 || position.y < camera->position.y - 128 || position.y > camera->position.y + 896)
		isDestroyed = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	//플레이어 총알 그리기
	if (type == 0)
	{
		Draw(sprite, gAssetManager->playerBulletTexture);
	}
	// 플레이어 호밍 미사일
	else if (type == 1)
	{
		Draw(sprite, gAssetManager->playerHomingBulletTexture);
	}
	//적 총알 그리기
	else if (type == 2)
	{
		Draw(sprite, gAssetManager->enemyBulletTexture);
	}
}

void CBullet::SetHoming(D3DXVECTOR2 * target, float time, float speed)
{
	targetPos = target;
	homingTimer = 0.0f;
	homingTime = time;
	homingSpeed = speed;
}
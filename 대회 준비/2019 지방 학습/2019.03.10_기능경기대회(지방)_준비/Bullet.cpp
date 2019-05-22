#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float destoryTime)
	:CMatrix(), parentScene(NULL), camera(camera), type(type), speed(speed), moveAngle(moveAngle), damage(damage), isDestroyed(false), destroyTime(destoryTime), destroyTimer(0), targetPos(NULL), homingTimer(0), homingTime(0), homingSpeed(0), velocity_Y(0)
{
	position = pos;

	// �÷��̾� �Ѿ�
	if (type == 0)
	{
		center.x = 16;
		center.y = 16;
	}
	// �÷��̾� ȣ�� �̻���
	else if (type == 1)
	{
		center.x = 16;
		center.y = 16;
	}
	//�� �Ѿ�
	else if (type == 2)
	{
		center.x = 16;
		center.y = 16;
	}
}

void CBullet::Update(float deltaTime)
{
	// ���� �������ִ� Ÿ���� �˻��Ͽ� ���� ���ִ� ���� ��ġ�� �˾Ƴ���.
	if (parentScene)
	{
		// Ÿ���� ���� ���̸� �̿��Ͽ� ���� ���ִ� ��ġ�� �� �� �ִ�.
		int tileIndex = position.x / gAssetManager->tile_Texture->width;
		if (parentScene->tileList.size() > tileIndex && 
			tileIndex >= 0)  // Ÿ�ϸ���Ʈ ����� ���� ��츦 ����ó��
		{
			ground_Y_Pos = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
		}
	}

	position.x += sin(moveAngle*(D3DX_PI / 180))*speed*deltaTime;
	position.y -= cos(moveAngle*(D3DX_PI / 180))*speed*deltaTime;

	rotation = moveAngle;

	if (type == 0) // ���� źȯ
	{
		// �߷� ����
		velocity_Y -= 10 * deltaTime;
		// velocity_Y�� ���� +�� ����ϰ� -�� �ϰ��ϱ����� ��ȣ�� ������ŵ�ϴ�.
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

	// ȣ�� �̻��� ������
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

	// ���� �˻�
	// �ٴ� �˻�
	if (position.y > ground_Y_Pos && type != 1 ) // ȣ�ֹ̻����� �ٴ� �浹���� ����
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0.0f;
		isDestroyed = true;
	}

	// �ð� �˻�
	destroyTimer += deltaTime;
	if (destroyTimer >= destroyTime)
		isDestroyed = true;

	// ȭ�� �˻�
	if (position.x < camera->position.x - 128 || position.x > camera->position.x + 1152 || position.y < camera->position.y - 128 || position.y > camera->position.y + 896)
		isDestroyed = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	//�÷��̾� �Ѿ� �׸���
	if (type == 0)
	{
		Draw(sprite, gAssetManager->playerBulletTexture);
	}
	// �÷��̾� ȣ�� �̻���
	else if (type == 1)
	{
		Draw(sprite, gAssetManager->playerHomingBulletTexture);
	}
	//�� �Ѿ� �׸���
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
#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)	: CMatrix(), camera(camera), 
velocity_Y(0), jumpCount(1), upgrade(0), isDie(false)
// �����ڿ��� ���� �ʱ�ȭ�� �� �������
{
	position = pos;
	center = D3DXVECTOR2(100, 50);

	// ó�� ���� ��ġ�� ������ �� ������ pos.y�� ������
	ground_Y_Pos = pos.y;
}

void CPlayer::Update(float deltaTime)
{
	// �߷� ��� =========================================================================
	// ���� : �߷��� �׳� �߷��� �޴� ������Ʈ���� Y��ǥ�� �׻� �Ʒ��� �����ִ� ���̰�
	//		  �ٴ��浹�� �׳� �� �Ʒ��� ���������� �ϴ� �� ��
	
	// �߷� ����
	// velocity_Y ���� ���� : �߷��� �޴� ��� ������Ʈ���� ������ �ִ� �����̰�
	//						  �ϴ� ������ position.y += velocity_Y �̷������� �׻� Y�࿡ �������� �����̴�.
	//						  �׷��� velocity_Y�� ���� -�� �ö󰡰� +�� ��������.

	velocity_Y += 32 * deltaTime; 
	// �߷� �� (�� : 32 * deltaTime) �� �����ش�.
	// = ������ �ƴ� += ������ �ϴ� ������ �߷��� ������ �޾� ���� ���ӵ��� �޾� ���� �������� �������� ���ؼ��̴�.
	
	position.y += velocity_Y;	  // �̷������� velocity_Y�� ����� ���� �����ֱ� ������ Y�� ��ġ�� �׻� �ٲ��.

	// �ٴ� ��ǥ ������Ʈ �ϱ� ===========================================================
	// ������ CTile���� ������� �Լ�(GetGround_Y_Pos)�� �̿��� �ٴ��� ��ġ�� �˾Ƴ��� ��

	// ���� �������ִ� Ÿ���� �˻��Ͽ� ���� ���ִ� ���� ��ġ�� �˾Ƴ���.
	if (parentScene)
	{
		// Ÿ���� ���� ���̸� �̿��Ͽ� ���� ���ִ� ��ġ�� �� �� �ִ�.

		// ���� ��ġ ������ Ÿ���� ���� ���̸� �ϸ� ���� ����ִ� Ÿ���� ��ȣ(tileIndex)�� �� �� �ִ�.
		int tileIndex = position.x / gAssetManager->tile_Texture->width;

		// �迭 �ε��� ������ �������� GameScene�� ������ TileList.size()�� ũ��� ���Ѵ�.
		// Ÿ�� ����Ʈ ����� ���� ��� ����
		if (parentScene->tileList.size() > tileIndex
			&& tileIndex >= 0) 
			// �׸��� �÷��̾ -��ǥ�� ������ tileIndex�� - ���� ���� �� �ִ�.
			// �̰͵� ����ó�� �ؾ���
		{
			float outY = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (outY != 0) // �� �Լ����� 0�� ���Դٸ� ������ 0�� �ƴҶ� ó�����ش�. 
				ground_Y_Pos = outY;
			// GetGround_Y_Pos �Լ��� �÷��̾��� ���� Position.X�� �־� �ٴ� ��ġ�� ������Ʈ�Ѵ�.
		}
	}

	// position.y�� �ٴ���ǥ�� �Ѿ� �������� ��츦 ���� ��Ҵٰ� �Ǵ��Ѵ�.
	if (position.y > ground_Y_Pos)
	{
		// ���� ����� �� �ʱ�ȭ ����� �ϴ� �κ��� ���⼭ �ʱ�ȭ�Ѵ�.
		position.y = ground_Y_Pos;

		// ���� ������ �߷� ���ӵ��� 0���� �ٲ��ش�.
		velocity_Y = 0.0f;
		// �߷±�� �� ===================================================================

		// �ٴڿ� ��ұ� ������ ���� Ƚ���� �ʱ�ȭ ���ش�.

		// ��ȹ���� �������� ������ 2�� ������ �����ϴٰ� ���ִµ� ���⼭ ó���� �� �� �ִ�.

		// ���� ������ ȿ�� ���� + ���׷��̵� 3�ܰ�� 2�� ������ ���Ѵٰ���
		/*
		if(doubleJump && upgrade != 2) 
			jumpCount = 2;
		else
			jumpCount = 1;
		*/

		jumpCount = 1;
	}

	CMatrix::Update(deltaTime, camera->position);
	SetRect(&rect, position.x - 10, position.y - 10, position.x + 10, position.y + 10);
}


void CPlayer::Render(LPD3DXSPRITE sprite)
{
	CMatrix::Render(sprite);

	// upgrade ������ �����ϴ� ������ �̹��� �����ϸ� ��ũ ���׷��̵� �κ� �ϼ�
	switch (upgrade)
	{
	case 0: // 1�ܰ�
		Draw(sprite, gAssetManager->player_1_Texture);
		break;
	case 1: // 2�ܰ�
		Draw(sprite, gAssetManager->player_2_Texture);
		break;
	case 2: // 3�ܰ�
		Draw(sprite, gAssetManager->player_3_Texture);
		break;
	}
}

void CPlayer::Move(int dir, float deltaTime)
// �̵� ���� int dir (�� : -1, �� : +1)
{
	float speed = 600.0f;

	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	// ������ jumpCount ��ŭ�� �����ϵ��� �ؾ� ��
	if (jumpCount > 0)
	{
		jumpCount--;
		velocity_Y = -10.0f;
		// ���⿡ ������ ��(�� : -10)�� ����
		// ������ ������ ���� �ö󰡾� �ϱ� ����

		// ����� ������ �ƴ϶� �������� ����� ������ ������ ������ �������� ����
	}
}

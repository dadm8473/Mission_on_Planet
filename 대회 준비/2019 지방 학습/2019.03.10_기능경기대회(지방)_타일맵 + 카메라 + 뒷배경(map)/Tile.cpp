#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera) :CMatrix(), camera(inputCamera)
{
	position = pos;
	currentScene = type = inputType;
}

void CTile::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);
}

void CTile::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->tile_Texture);
}

// �� �Լ��� posX�� ���� ��ǥ�� ���� �� Ÿ���� ��� �ִ��� �˻� �� �ٴ��� ���̸� �������ִ� �Լ���
float CTile::GetGround_Y_Pos(float posX)
{
	float yPos = 0.0f;

	// �÷��̾ �ش� Ÿ���� ���� ����

	// ���� �÷��̾ ��� ��������� �Ѿ˵� ���� ���� �� �� ����

	// posX�� �� Ÿ���� position.x ���� ũ�ų� ���� �ű⿡ �ؽ�ó�� ���α��̸� ���� �� ���� ������ ����ִٰ� �Ǵ�
	// �̰Ϳ� ������ �׸��� ÷����
	if (posX >= position.x  &&
		posX < position.x + gAssetManager->tile_Texture->width)
	{
		// �÷��̾��� ��ġ�� Ÿ���� �Ÿ��� ���� Ÿ���� ������ ������ ����� ���� ��� �� ����
		float length = posX - position.x;

		// ���� ���� ��ȭ���� �������ش�
		float value = 0.0f; // �⺻���� ������ (�� ���� �����̴�)
		float delta_Y = 0.0f; // �������� Y �������� ���� ����ŭ ���⿡ ������ ���ش�. 
		// ���� �������� �׸��� �����صξ���
		switch (type)
		{
		case 1: // ������
			delta_Y = 100.0f;
			value = -100.0f;
			break;
		case 2: // ������ 
			value = 100.0f;
			break;
		}
		// �÷��̾��� �� �������� ����
		yPos = position.y + delta_Y + value * (length / gAssetManager->tile_Texture->width);
		// ���� ������ ���� Ÿ���� Position.Y�� �������� ������ + ���� ��갪�� ���� �������� ��ȯ�Ѵ�.
		// ���� ��갪�� ���ؼ��� �׸��� ������
	}

	return yPos;
}

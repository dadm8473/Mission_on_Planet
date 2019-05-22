#include "DXUT.h"
#include "Header.h"


CCamera::CCamera()
	:position(0,0), center(256, 384), 
	limitPos_Max(9999, 9999), limitPos_Min(0, - 9999),
	target(NULL), speed(0.05f)
{
}

CCamera::~CCamera()
{
	delete target;
}

void CCamera::Update(float deltaTime)
{
	if (target != NULL)
		// �Ʒ�ó�� �����ϸ� �� ������ ���� ī�޶��� �����ǰ��� Ÿ���� �����ǿ� ���ǵ常ŭ �ٰ����� �ȴ�.
		D3DXVec2Lerp(&position, &position, &(target->position - center), speed);


	// ī�޶� ������ ���� �˻�
	if (position.x <= limitPos_Min.x)
		position.x = limitPos_Min.x;
	if (position.x >= limitPos_Max.x)
		position.x = limitPos_Max.x;

	if (position.y <= limitPos_Min.y)
		position.y = limitPos_Min.y;
	if (position.y >= limitPos_Max.y)
		position.y = limitPos_Max.y;
		
}

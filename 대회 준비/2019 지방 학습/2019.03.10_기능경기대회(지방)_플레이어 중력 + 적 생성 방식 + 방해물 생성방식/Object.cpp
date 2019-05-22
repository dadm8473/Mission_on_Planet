#include "DXUT.h"
#include "Header.h"

CObject::CObject(CCamera* camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), type(type), isDestroyed(false)
{
	position = pos;

	if (type == 0) // 구덩이
		SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
	else if (type == 1) // 바위
		SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
}

void CObject::Update(float deltaTime)
{
	// 오브젝트는 카메라 영역 밖에 나가도 삭제하지 않음
	// 이유는 체크포인트 기능 때문에 뒤로 이동이 가능하기 때문임

	CMatrix::Update(deltaTime, camera->position);
}

void CObject::Render(LPD3DXSPRITE sprite)
{
	if (type == 0) // 구덩이
		Draw(sprite, gAssetManager->object_TrapTexture);
	else if (type == 1) // 바위
		Draw(sprite, gAssetManager->object_RockTexture);
}
#pragma once

// 내가 줬던 완성본은 바위 오브젝트가 파괴가능한 것 때문에 Enemy의 Type으로 놨는데
// 생각해보니 그냥 구덩이랑 바위는 Object로 합치는게 맞는 것 같음
// CObject의 기능은 그냥 충돌 체크랑 바위용 체력만 있으면됨
class CObject : public CMatrix
{
public:
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	int type;

	//충돌
	RECT rect;

	//체력
	int hp;
	bool isDestroyed;

	CObject(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
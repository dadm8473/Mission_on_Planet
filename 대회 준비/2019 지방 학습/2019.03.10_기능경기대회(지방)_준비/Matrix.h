#pragma once

class CMatrix
{
public:
	D3DXMATRIX matrix;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 center;
	float rotation;

	int a, r, g, b ; // 색깔값

	//애니메이션
	int currentScene;							//현재 씬
	int maxScene;								//최대 씬
	bool isAnimate;								//애니메이션 적용?
	float animationTime, animationTimer;;		//에니메이션 속도
	bool isAniEnd;								//애니메이션이 끝났는가
	bool isRepeatAni;							//에니메이션이 반복되는가

	void SetAnimation(int maxScene, float time, bool repeat);

	CMatrix();
	// 카메라의 위치 값이 새로 추가됨
	virtual void Update(float deltaTime, D3DXVECTOR2 camera = D3DXVECTOR2(0, 0));
	virtual void Render(LPD3DXSPRITE sprite);

	void Draw(LPD3DXSPRITE sprite, CTexture* texture);
};
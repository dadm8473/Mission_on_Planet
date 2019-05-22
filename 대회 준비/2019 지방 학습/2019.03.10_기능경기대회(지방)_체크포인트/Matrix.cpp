#include "DXUT.h"
#include "Header.h"


CMatrix::CMatrix()
	// 월드 정보
	: position(0, 0), scale(1, 1), center(0, 0), rotation(0),
	// 색깔
	a(255), r(255), g(255), b(255),
	// 애니메이션
	currentScene(0), isAnimate(false), animationTime(0), animationTimer(0),
	isAniEnd(false), isRepeatAni(false), maxScene(0)
{
	D3DXMatrixIdentity(&matrix);
}

// 카메라의 위치 값이 새로 추가됨
void CMatrix::Update(float deltaTime, D3DXVECTOR2 camera)
{
	D3DXVECTOR2 finalPos = position - center - camera;
	D3DXMatrixTransformation2D(
		&matrix,
		&center,
		0,
		&scale,
		&center,
		D3DXToRadian(rotation),
		&finalPos
	);

	//애니시작
	if (isAnimate && !isAniEnd)
	{
		animationTimer += deltaTime;

		if (animationTimer >= animationTime)
		{
			animationTimer = 0;
			if (++currentScene >= maxScene)
			{
				if (isRepeatAni)
				{
					currentScene = 0;
				}
				else
				{
					currentScene--;
					isAniEnd = true;
				}
			}
		}
	}
}

void CMatrix::Render(LPD3DXSPRITE sprite)
{

}
void CMatrix::Draw(LPD3DXSPRITE sprite, CTexture* texture)
{
	sprite->SetTransform(&matrix);
	sprite->Draw(texture->GetTexture(currentScene),
		NULL, NULL, NULL,
		D3DCOLOR_ARGB(a, r, g, b));
}

void CMatrix::SetAnimation(int maxScene, float time, bool repeat)
{
	this->isAnimate			= true;
	this->maxScene			= maxScene;
	this->animationTime		= time;
	this->animationTimer	= 0;
	this->isAniEnd			= false;
	this->isRepeatAni		= repeat;
}


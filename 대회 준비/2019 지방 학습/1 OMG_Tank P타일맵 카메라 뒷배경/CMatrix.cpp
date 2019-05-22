#include "DXUT.h"
#include "Header.h"

CMatrix::CMatrix()
	: position(0,0), scale(1,1), center(0,0), rotate(0), animation(false), aniTime(0), aniTimer(0), currentScene(0), maxScene(0), repeateAni(false), isAniEnd(false)
{
	D3DXMatrixIdentity(&matrix);

	a = r = g = b = 255;
}

void CMatrix::Update(float deltaTime, D3DXVECTOR2 camera)
{
	D3DXVECTOR2 pos = position - center - camera;

	D3DXMatrixTransformation2D(&matrix, &center, 0, &scale, &center, D3DXToRadian(rotate), &pos);

	if (animation && !isAniEnd)
	{
		aniTimer += deltaTime;
		if (aniTimer > aniTime)
		{
			currentScene++;
			if (currentScene >= maxScene)
			{
				if (repeateAni)
					currentScene = 0;
				else
				{
					currentScene--;
					isAniEnd = true;
				}
			}
			aniTimer = 0;
		}
	}
}

void CMatrix::Draw(LPD3DXSPRITE sprite, CTexture * texture, RECT* drawRect)
{
	sprite->SetTransform(&matrix);
	sprite->Draw(texture->GetTexture(currentScene), drawRect,
		NULL, NULL, D3DCOLOR_ARGB(a, r, g, b, ));
}

void CMatrix::SetAnimation(float rate, int maxScene, bool repeat)
{
	animation = true;

	aniTimer = 0;
	aniTime = rate;
	this->maxScene = maxScene;
	currentScene = 0;
	repeateAni = repeat;
	isAniEnd = false;
}

#include "DXUT.h"
#include "Header.h"

CMatrix::CMatrix()
	:position(0, 0), scale(1,1), center(0,0), rotate(0), animation(false), aniTime(0), aniTimer(0), currentScene(0), maxScene(0), repeatAni(false), isAniEnd(false)
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
			aniTimer = 0;
			if (++currentScene >= maxScene)
			{
				if (repeatAni)
					currentScene = 0;
				else
				{
					currentScene--;
					isAniEnd = true;
				}
			}
		}
	}
}

void CMatrix::Draw(LPD3DXSPRITE sprite, CTexture * texture)
{
	sprite->SetTransform(&matrix);
	sprite->Draw(texture->GetTexture(currentScene), NULL, NULL, NULL, D3DCOLOR_ARGB(a, r, g, b));
}

void CMatrix::SetAnimation(float rate, int maxScene, bool repeat)
{
	animation = true;

	aniTimer = 0;
	aniTime = rate;
	currentScene = 0;
	this->maxScene = maxScene;
	repeatAni = repeat;
	isAniEnd = false;
}

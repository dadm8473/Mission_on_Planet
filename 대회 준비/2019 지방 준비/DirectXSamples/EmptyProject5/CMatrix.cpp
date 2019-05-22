#include "DXUT.h"
#include "Header.h"

CMatrix::CMatrix()
{
	camera = NULL;
	zValue = 1;

	position = D3DXVECTOR2(0, 0);
	center = D3DXVECTOR2(0, 0);
	scale = D3DXVECTOR2(1, 1);
	rotate = 0;

	a = r = g = b = 255;

	animation = false;

	aniTime = 0;
	aniTimer = 0;
	currentScene = 0;
	maxScene = 0;
	repeatAni = false;
	isAniEnd = false;
}

void CMatrix::Update(float deltaTime)
{
	D3DXVECTOR2 pos = position;
	pos -= center;

	D3DXMatrixIdentity(&matrix);

	if (camera)
	{
		pos.x -= (camera->position.x - camera->center.x) / zValue;
		pos.y -= (camera->position.y - camera->center.y) / zValue;
	}

	D3DXMatrixTransformation2D(&matrix, &center, 0, &scale, &center, D3DXToRadian(rotate), &pos);

	if (animation && !isAniEnd)
	{
		aniTimer += deltaTime;
		if (aniTimer > aniTime)
		{
			currentScene++;
			if (currentScene >= maxScene)
			{
				if (repeatAni)
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

void CMatrix::Draw(LPD3DXSPRITE sprite, CTextrue * texture, RECT * drawRect)
{
	sprite->GetTransform(&matrix);
	sprite->Draw(texture->GetTexture(currentScene), drawRect,
		NULL, NULL, D3DCOLOR_ARGB(a, r, g, b));
}

void CMatrix::SetAnimation(float rate, int maxScene, bool repeat)
{
	animation = true;

	aniTime = rate;
	aniTimer = 0;
	currentScene = 0;
	this->maxScene = maxScene;
	repeatAni = repeat;
	isAniEnd = false;
}

#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, int inputType, CCamera * camera)
	: camera(camera), type(inputType), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);
	SetAnimation(0.03f, 15, false);
	gAssetManager->GetSound("Effect")->Play();

	switch (type)
	{
	case 1: // effect
		SetAnimation(0.03f, 15, false);
		center = D3DXVECTOR2(64, 64);
		break;
	case 2: // player
		SetAnimation(0.03f, 20, false);
		break;
	case 3: // enemy
		SetAnimation(0.03f, 20, false);
		break;
	case 10: // Clear Attack Effect
		center = D3DXVECTOR2(0, 0);
		SetAnimation(0.03f, 20, false);
		break;
	case 100: // Clear ~~~~
		scale = D3DXVECTOR2(3, 3);
		center = D3DXVECTOR2(64, 64);
		SetAnimation(0.03f, 15, false);
		break;
	default:
		break;
	}
}

void CEffect::Update(float deltaTime)
{
	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	case 10: // Clear Attack Effect
		break;
	default:
		break;
	}
	
	// 애니메이션이 끝나면 삭제
	if (isAniEnd)
		isDestroyed = true;

	// 타입 100은 카메라 안넣어줌
	if(type != 100 && type != 10)
		CMatrix::Update(deltaTime, camera->position);
	else
		CMatrix::Update(deltaTime);
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1: //effect
		Draw(sprite, gAssetManager->GetTexture("Effect"));
		break;
	case 2: //player
		Draw(sprite, gAssetManager->GetTexture("Effect_Player"));
		break;
	case 3: //enemy
		Draw(sprite, gAssetManager->GetTexture("Effect_Enemy"));
		break;
	case 10: // Clear Attack Effect
		Draw(sprite, gAssetManager->GetTexture("Effect_Clear"));
		break;
	case 100:// Clear ~~~~
		Draw(sprite, gAssetManager->GetTexture("Effect"));
		break;
	default:
		Draw(sprite, gAssetManager->GetTexture("Effect"));
		break;
	}
}

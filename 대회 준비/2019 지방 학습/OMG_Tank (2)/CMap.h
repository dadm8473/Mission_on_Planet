#pragma once
class CMap
{
public:
	CCamera* camera;

	CMatrix skyLayer[2];
	CMatrix midLayer[2];

	CMap(int stage, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprtie);
};


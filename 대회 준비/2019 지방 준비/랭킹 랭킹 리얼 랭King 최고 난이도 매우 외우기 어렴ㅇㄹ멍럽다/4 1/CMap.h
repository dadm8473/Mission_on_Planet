#pragma once
class CMap
{
public:
	CCamera* camera;

	CMatrix skyLayer[2];
	CMatrix midLayer[2];

public:
	CMap(int stage, CCamera* camear);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


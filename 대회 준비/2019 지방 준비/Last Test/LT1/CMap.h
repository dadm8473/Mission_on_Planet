#pragma once
class CMap
{
public:
	CCameara* camera;

	CMatrix skyLayer[2];
	CMatrix midLayer[2];

public:
	CMap(int stage, CCameara* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


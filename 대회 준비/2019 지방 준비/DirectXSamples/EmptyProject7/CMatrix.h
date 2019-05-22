#pragma once
class CMatrix
{
public:
	CMatrix* camera;
	float zValue;

	D3DXMATRIX matrix;
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;
	D3DXVECTOR2 scale;
	float rotate;

	int a, r, g, b;

	bool animation;

	float aniTimer, aniTime;
	int currentScene, maxScene;
	bool repeatAni, isAniEnd;

public:
	CMatrix();
	virtual void Update(float deltaTime);
	void Draw(LPD3DXSPRITE sprite, CTexture* texture, RECT* drawRect = NULL);
	virtual void SetAnimation(float rate, int maxScene, bool repeat);

	CMatrix* GetCamearaObject() { return this->camera; }
	void SetCameraObject(CMatrix* cameara) { this->camera = camera; }
};
extern CMatrix gCamera;


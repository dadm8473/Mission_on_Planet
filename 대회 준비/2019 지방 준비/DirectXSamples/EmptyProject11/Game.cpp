#include "DXUT.h"
#include "Header.h"

LPD3DXSPRITE* gSprite = NULL;
CScene* gScene = NULL;

void ChangeScene(string sceneName)
{
	if (gScene)
		delete gScene;

	if (sceneName == "Title")
		gScene = new CTitleScene();
}

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);


}

void Term()
{
}

void Reset()
{
}

void Lost()
{
}

void Update(float deltaTime)
{
}

void Reder()
{
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}

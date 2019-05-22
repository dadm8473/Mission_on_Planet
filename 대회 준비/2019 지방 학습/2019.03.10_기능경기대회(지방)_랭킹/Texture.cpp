#include "DXUT.h"
#include "Header.h"

CTexture::CTexture(LPCWSTR filename, 
					LPCWSTR extname, 
					int maxScene)
{
	textures = new LPDIRECT3DTEXTURE9[maxScene];
	this->maxScene = maxScene;

	D3DXIMAGE_INFO imageInfo;

	for (int i = 0; i < maxScene; i++)
	{
		wchar_t temp[256];
		wsprintf(temp, L"%s%02d.%s", filename, i, extname);

		D3DXGetImageInfoFromFile(temp, &imageInfo);

		if (FAILED(D3DXCreateTextureFromFileEx(
			/*디바이스*/ DXUTGetD3D9Device(),
			/*파일경로*/temp,
			/*그림너비*/imageInfo.Width,
			/*그림높이*/imageInfo.Height,
			/*밉맵수준*/1,
			/*사용목적*/0,
			/*텍스처 포맷*/D3DFMT_A8R8G8B8,
			/*메모리 폴*/D3DPOOL_MANAGED,
			/*텍스처 필터*/D3DX_DEFAULT,
			/*밉맵 필터*/D3DX_DEFAULT,
			/*알파 키값*/0,
			/*이미지 정보*/NULL,
			/*팔레트*/NULL,
			/*텍스처*/&textures[i]
		)))
		{
			MessageBox(DXUTGetHWND(), temp, L"택스처를 불러올 수 없습니다", MB_OK);
		}

		if (i == 0)
		{
			this->width = imageInfo.Width;
			this->height = imageInfo.Height;
		}

	}
}
CTexture::~CTexture()
{
	for (int i = 0; i < maxScene; i++)
	{
		if (textures[i])
			textures[i]->Release();
	}



	delete[] textures;
}
#pragma once

class CTexture
{
public:
	LPDIRECT3DTEXTURE9* textures; // 그림 배열

	int maxScene;		// 애니메이션 장수
	int width, height;  // 텍스처 크기

	CTexture(LPCWSTR filename, LPCWSTR extname, int maxScene);
	~CTexture();

	LPDIRECT3DTEXTURE9 GetTexture(int idx)
	{
		if (idx < 0 || idx >= maxScene)
			return NULL;
		return textures[idx];
	}
};
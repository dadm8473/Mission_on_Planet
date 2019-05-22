#pragma once
class CTexture
{
	LPDIRECT3DTEXTURE9* _textures;
	D3DXIMAGE_INFO imageInfo;

	int maxScene;
	int width, height;

	LPDIRECT3DTEXTURE9 GetTexture(int idx)
	{
		if (0 > idx || idx > maxScene)
			return NULL;
		return _textures[idx];
	}
public:
	CTexture(LPCWSTR filename, LPCWSTR extname, int maxScene);
	~CTexture();
};


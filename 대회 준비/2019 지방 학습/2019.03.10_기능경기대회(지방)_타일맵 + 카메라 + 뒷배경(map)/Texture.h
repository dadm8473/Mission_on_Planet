#pragma once

class CTexture
{
public:
	LPDIRECT3DTEXTURE9* textures; // �׸� �迭

	int maxScene;		// �ִϸ��̼� ���
	int width, height;  // �ؽ�ó ũ��

	CTexture(LPCWSTR filename, LPCWSTR extname, int maxScene);
	~CTexture();

	LPDIRECT3DTEXTURE9 GetTexture(int idx)
	{
		if (idx < 0 || idx >= maxScene)
			return NULL;
		return textures[idx];
	}
};
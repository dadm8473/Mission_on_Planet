#pragma once
class CAssetManager
{
private:
	static CAssetManager* instance;
	std::map<std::string, CTexture*> textures;

public:
	static CAssetManager* Instance()
	{
		if (!instance)
			instance = new CAssetManager;

		return instance;
	}

public:
	void LoadAssets();
	void ReleaseAssets();
	void LoadTexture(string key, LPCWSTR filename, LPCWSTR extname, int maxScene);

	CTexture* GetTexture(string key);
};

extern CAssetManager* gAssetManager;
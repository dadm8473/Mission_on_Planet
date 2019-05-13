#pragma once
class AssetManager
{
private:
	static AssetManager* instance;
	std::map<std::string, CTexture*> textures;

public:
	static AssetManager* Instance()
	{
		if (!instance)
			instance = new AssetManager();

		return instance;
	}

public:
	CSoundManager* soundManager;
	std::map<std::string, CSound*> sounds;

	void LoadAssts_Sound(string key, LPWSTR filename, float maxBuffer);

	CSound* GetSound(string key)
	{
		auto it = sounds.find(key);

		if (it != sounds.end())
			return it->second;
		else
			return NULL;
	}

public:
	void LoadAssets();
	void ReleaseAssets();
	void LoadTexture(string key, LPCWSTR filename, LPCWSTR extname, int maxScene);
	CTexture* GetTexture(string key);
};

extern AssetManager* gAssetManager;
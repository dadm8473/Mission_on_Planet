#pragma once

struct ScoreInfo
{
public:
	int score = 0;
	int initial[3] = { 0, };
};

class ScoreManager
{
public:
	vector<ScoreInfo> scoreDatas;

public:
	void Save();
	void Load();
	void Sort();
};

extern ScoreManager* gScoreManager;
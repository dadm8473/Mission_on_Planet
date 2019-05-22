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
	void Load();
	void Save();

	bool CompareScore(const ScoreInfo& a, const ScoreInfo& b) { return a.score > b.score; }
	void Sort();
};

extern ScoreManager* gScoreManager;
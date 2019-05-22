#include "DXUT.h"
#include "Header.h"
#include <fstream>
#include <algorithm>

ScoreManager* gScoreManager;

void ScoreManager::Save()
{
	FILE *fp = fopen("./ScoreData.Dat", "wb");

	ScoreInfo wirteData[3];

	for (int i = 0; i < 3; ++i)
		wirteData[i] = scoreDatas[i];

	fwrite(wirteData, sizeof(ScoreInfo), 3, fp);

	fclose(fp);
}

void ScoreManager::Load()
{
	FILE *fp = fopen("./ScoreData.Dat", "wb");

	scoreDatas.clear();

	if (!fp)
	{
		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(ScoreInfo());
	}
	else
	{
		ScoreInfo readData[3];

		fread(readData, sizeof(ScoreInfo), 3, fp);

		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(readData[i]);
	}

	fclose(fp);
}

void ScoreManager::Sort()
{
	if (scoreDatas.size() > 0)
		std::sort(scoreDatas.begin(), scoreDatas.end(), CompareScore);
}

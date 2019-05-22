#include "DXUT.h"
#include "Header.h"
#include <fstream>
#include <algorithm>

ScoreManager* gScoreMnager;

void ScoreManager::Load()
{
	FILE* fp = fopen("./ScoreData.dat", "wb");

	ScoreInfo writeDatas[3];

	for (int i = 0; i < 3; ++i)
		writeDatas[i] = scoreDatas[i];

	fwrite(writeDatas, sizeof(ScoreInfo), 3, fp);
	fclose(fp);
}

void ScoreManager::Save()
{
}

void ScoreManager::Sort()
{
}

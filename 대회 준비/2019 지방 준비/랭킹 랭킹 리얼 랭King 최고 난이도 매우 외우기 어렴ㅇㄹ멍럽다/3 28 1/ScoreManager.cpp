#include "DXUT.h"
#include "Header.h"
#include <fstream>
#include <algorithm>

ScoreManager* gScoreManager;

void ScoreManager::Save()
{
	// ���� ������
	Sort();
	// ������
	FILE* fp = fopen("./ScoreData.dat", "wb");
	// ���� ������
	ScoreInfo writeData[3];
	// score data�� �׾Ƶа� ������� �غ�
	for (int i = 0; i < 3; ++i)
		writeData[i] = scoreDatas[i];
	// fp�� �ֱ�
	fwrite(writeData, sizeof(ScoreInfo), 3, fp);
	// �ݱ�
	fclose(fp);
}

void ScoreManager::Load()
{
	// ���� �����ְ�
	FILE* fp = fopen("./ScoreData.dat", "rb");

	// �ִ��� �����ְ�
	scoreDatas.clear();

	// fp ������ �ϳ� �ͱ۾��ְ� ScoreInfo()�� �ʱ�ȭ �Ϲ� score = 0 initial[3] = {0,} ��
	if (!fp)
		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(ScoreInfo());
	else
	{
		// fp ������ �ҷ��� ���� �������
		ScoreInfo readData[3];
		// �ҷ�����
		fread(readData, sizeof(ScoreInfo), 3, fp);
		// score data�� �־���
		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(readData[i]);
	}
	// �������� �ݱ�
	fclose(fp);
}

bool SortScore(const ScoreInfo& a, const ScoreInfo& b)
{
	return a.score > b.score;
}

void ScoreManager::Sort()
{
	if(scoreDatas.size() > 0)
		std::sort(scoreDatas.begin(), scoreDatas.end(), SortScore);
}

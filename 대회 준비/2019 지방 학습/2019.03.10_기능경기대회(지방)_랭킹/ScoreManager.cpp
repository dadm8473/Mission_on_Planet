#include "DXUT.h"
#include "Header.h"
#include <fstream>
#include <algorithm>

CScoreManager*gScoreManager;

void CScoreManager::Load()
{
	// 2���� ������ �б� ���·� �ҷ�����
	// ./ = ���� ���
	FILE *fp = fopen("./ScoreData.Dat", "rb");

	scoreDatas.clear();

	if(!fp) // ���� ����� ����
	{ // ������ 0���� ä���ش�.
		for(int i = 0 ; i < 3 ; i ++)
			scoreDatas.push_back(ScoreInfo());
	}
	else // ���� ����� �ִ�
	{
		ScoreInfo readData[3];
		fread(readData, sizeof(ScoreInfo), 3, fp);

		for (int i = 0; i < 3; i++)
			scoreDatas.push_back(readData[i]);

		fclose(fp);
	}
}

void CScoreManager::Save()
{
	// 2���� ������ ���� ���·� �ҷ�����
	// ./ = ���� ���
	FILE *fp = fopen("./ScoreData.Dat", "wb");

	if (!fp)
	{
		MessageBox(DXUTGetHWND(), L"���� �ҷ����� ����", L"CScoreManager::Save()", MB_OK);
		return;
	}
	else
	{
		// �����ϱ� ���� ������ ���ݴϴ�.
		Sort();

		ScoreInfo readData[3];

		for (int i = 0; i < 3; i++)
		{
			readData[i] = scoreDatas[i];
		}

		fwrite(readData, sizeof(ScoreInfo), 3, fp);
		
		fclose(fp);
	}
}

bool CompareScore(const ScoreInfo& a, const ScoreInfo& b)
{
	return a.score > b.score;
}

void CScoreManager::Sort()
{
	if (scoreDatas.size() > 0)
	{
		std::sort(scoreDatas.begin(), scoreDatas.end(), CompareScore);
	}
}
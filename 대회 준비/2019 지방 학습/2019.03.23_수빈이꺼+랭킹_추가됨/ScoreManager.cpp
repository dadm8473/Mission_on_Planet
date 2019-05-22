#include "DXUT.h"
#include "Header.h"

// ���� ������� �Ϸ��� fstream
#include <fstream>
// Sort �Լ��� ����Ϸ��� algorithm
#include <algorithm>

// ���� : extern �����ߴٸ� �̰� �� ���������
CScoreManager*gScoreManager;

void CScoreManager::Save()
{
	// ���� : �����ϱ����� �����͸� ������������ ��������� ��
	Sort();

	FILE *fp = fopen("./ScoreData.Dat", "wb");

	ScoreInfo writeData[3];

	for(int i = 0 ; i < 3; i ++)
	{
		writeData[i] = scoreDatas[i];
	}

	fwrite(writeData, sizeof(ScoreInfo), 3, fp);

	fclose(fp);
}

void CScoreManager::Load()
{
	FILE *fp = fopen("./ScoreData.Dat", "rb");

	// ���� : �ε��� �� ���� �����͸� ���������
	scoreDatas.clear();

	if (!fp) // ������ ����
	{
		// ���� : ������ ������ 0 ���� 1 ~ 3���� ä�������
		for (int i = 0; i < 3; i++)
			scoreDatas.push_back(ScoreInfo());
	}
	else // ���� �־�
	{
		ScoreInfo readData[3];

		// ���Ͽ��� �д´�
		// �о�� �����ʹ� readData�� �ִ´�
		// �о�� ������ SocreInfo
		// 3�� �о�´�
		// fp ���Ϸ� ����
		fread(readData, sizeof(ScoreInfo), 3, fp);

		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(readData[i]);
	}

	fclose(fp);

}

// �� ������ �Լ� ���·� ������ش�.
bool CompareScore(const ScoreInfo& a, const ScoreInfo& b)
{
	// �̰� ���������̾�
	return a.score > b.score;
}

void CScoreManager::Sort()
{
	if (scoreDatas.size() > 0)
	{
		// ���� : begin, end�� �Լ��� () �����ϼ���
		std::sort(scoreDatas.begin(), scoreDatas.end(), CompareScore);
	}
}

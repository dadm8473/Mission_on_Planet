#include "DXUT.h"
#include "Header.h"
#include <fstream>
#include <algorithm>

CScoreManager*gScoreManager;

void CScoreManager::Load()
{
	// 2진수 파일을 읽기 상태로 불러오기
	// ./ = 현재 경로
	FILE *fp = fopen("./ScoreData.Dat", "rb");

	scoreDatas.clear();

	if(!fp) // 이전 기록이 없다
	{ // 없으면 0으로 채워준다.
		for(int i = 0 ; i < 3 ; i ++)
			scoreDatas.push_back(ScoreInfo());
	}
	else // 이전 기록이 있다
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
	// 2진수 파일을 쓰기 상태로 불러오기
	// ./ = 현재 경로
	FILE *fp = fopen("./ScoreData.Dat", "wb");

	if (!fp)
	{
		MessageBox(DXUTGetHWND(), L"파일 불러오기 실패", L"CScoreManager::Save()", MB_OK);
		return;
	}
	else
	{
		// 저장하기 전에 정렬을 해줍니다.
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
#include "DXUT.h"
#include "Header.h"
#include <fstream>
#include <algorithm>

ScoreManager* gScoreManager;

void ScoreManager::Save()
{
	// 정렬 때리고
	Sort();
	// 열어줌
	FILE* fp = fopen("./ScoreData.dat", "wb");
	// 적어 넣을꺼
	ScoreInfo writeData[3];
	// score data에 쌓아둔거 적어넣을 준비
	for (int i = 0; i < 3; ++i)
		writeData[i] = scoreDatas[i];
	// fp에 넣기
	fwrite(writeData, sizeof(ScoreInfo), 3, fp);
	// 닫기
	fclose(fp);
}

void ScoreManager::Load()
{
	// 파일 열어주고
	FILE* fp = fopen("./ScoreData.dat", "rb");

	// 있던거 지워주고
	scoreDatas.clear();

	// fp 없으면 하나 맹글어주고 ScoreInfo()로 초기화 하믄 score = 0 initial[3] = {0,} 들어감
	if (!fp)
		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(ScoreInfo());
	else
	{
		// fp 잇으면 불러올 변수 만들어줌
		ScoreInfo readData[3];
		// 불러오고
		fread(readData, sizeof(ScoreInfo), 3, fp);
		// score data에 넣어줌
		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(readData[i]);
	}
	// 열엇으면 닫기
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

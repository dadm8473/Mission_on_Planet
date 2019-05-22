#include "DXUT.h"
#include "Header.h"

// 파일 입출력을 하려면 fstream
#include <fstream>
// Sort 함수를 사용하려면 algorithm
#include <algorithm>

// 주의 : extern 선언했다면 이거 꼭 적어줘야함
CScoreManager*gScoreManager;

void CScoreManager::Save()
{
	// 주의 : 저장하기전에 데이터를 내림차순으로 정렬해줘야 함
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

	// 주의 : 로드할 때 기존 데이터를 지워줘야함
	scoreDatas.clear();

	if (!fp) // 파일이 없어
	{
		// 주의 : 파일이 없으면 0 으로 1 ~ 3위를 채워줘야함
		for (int i = 0; i < 3; i++)
			scoreDatas.push_back(ScoreInfo());
	}
	else // 파일 있어
	{
		ScoreInfo readData[3];

		// 파일에서 읽는다
		// 읽어온 데이터는 readData에 넣는다
		// 읽어올 형태은 SocreInfo
		// 3개 읽어온다
		// fp 파일로 부터
		fread(readData, sizeof(ScoreInfo), 3, fp);

		for (int i = 0; i < 3; ++i)
			scoreDatas.push_back(readData[i]);
	}

	fclose(fp);

}

// 비교 조건을 함수 형태로 만들어준다.
bool CompareScore(const ScoreInfo& a, const ScoreInfo& b)
{
	// 이게 내림차순이야
	return a.score > b.score;
}

void CScoreManager::Sort()
{
	if (scoreDatas.size() > 0)
	{
		// 주의 : begin, end는 함수임 () 조심하세요
		std::sort(scoreDatas.begin(), scoreDatas.end(), CompareScore);
	}
}

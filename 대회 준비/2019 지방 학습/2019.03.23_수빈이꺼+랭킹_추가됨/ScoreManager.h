#pragma once

// ���̺� ������ ����ü
// �� ����ü�� ���Ϸ� �����ϰ� �ҷ��´�.
struct ScoreInfo
{
public :
	int score = 0;
	int initial[3] = { 0, };
};

// ���ھ� 
class CScoreManager
{
public : 
	// 1~3�� �׸��� ���� �ڽ��� ������ �� Vector
	vector<ScoreInfo> scoreDatas;

	void Save();
	void Load();

	// sort�� ����� ���ÿ� �۵��ϰ� �ص� ��
	void Sort();
};

// ���� : Game.cpp���� Init()�ȿ��� gScoreManager �ʱ�ȭ ���ֱ�
extern CScoreManager*gScoreManager;

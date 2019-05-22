#pragma once

extern void Init();
extern void Term();
extern void Reset();
extern void Lost();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam,
	LPARAM lParam);

extern CScene*gScene;

//UTILITY�Լ����� �Ʒ��� ���ּ�
extern float GetAngle(float x, float y);

extern void ChangeScene(string sceneName, int value = 0);
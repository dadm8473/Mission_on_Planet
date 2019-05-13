#pragma once

extern void ChangeScene(string sceneName);

extern void Init();
extern void Term();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
extern float GetAngle(float x, float y);

extern int tileWidth; // Ÿ�� ���α���

extern int ext_Score; // ���ھ�

extern int ext_Stage; // ��������

extern int ext_2Stage_Score;
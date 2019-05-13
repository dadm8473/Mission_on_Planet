#pragma once

extern void ChangeScene(string sceneName);

extern void Init();
extern void Term();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
extern float GetAngle(float x, float y);

extern int tileWidth; // 타일 가로길이

extern int ext_Score; // 스코어

extern int ext_Stage; // 스테이지

extern int ext_2Stage_Score;
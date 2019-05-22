#pragma once

extern void ChangeScene(string sceneName);

extern void Init();
extern void Term();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

extern int tileWidth; // 타일 가로길이

extern int score; // 전체 스코어
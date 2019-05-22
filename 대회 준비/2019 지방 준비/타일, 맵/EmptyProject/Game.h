#pragma once

extern void ChagneScene(string sceneName);

extern void Init();
extern void Term();
extern void Reset();
extern void Lost();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
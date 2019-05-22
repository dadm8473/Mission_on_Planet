#pragma once

extern void ChangeScene(int sceneNum);
extern void Init();
extern void Term();
extern void Lost();
extern void Reset();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

extern void LoadingUpdate(float deltaTime);
extern void LoadingRender();
extern bool isLoading;
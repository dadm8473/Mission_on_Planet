#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage)
	:CScene(), tileEntryInfo(), currentTileEntryIndex(0), tileList()
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));

	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->GetTexture("Tile")->width - 1024.0f;

	mainCamera->SetTarget(NULL);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		if (*it)
			delete(*it);
	}
	tileList.clear();

	if (map)
		delete map;

	if (mainCamera)
		delete mainCamera;
}

void CGameScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	if (mainCamera)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
			mainCamera->position.x -= 700 * deltaTime;
		if (GetKeyState(VK_RIGHT) & 0x8000)
			mainCamera->position.x += 700 * deltaTime;
		if (GetKeyState(VK_UP) & 0x8000)
			mainCamera->position.y -= 700 * deltaTime;
		if (GetKeyState(VK_DOWN) & 0x8000)
			mainCamera->position.y += 700 * deltaTime;

		mainCamera->Update(deltaTime);
	}

	if (map)
		map->Update(deltaTime);

	TileUpdate(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	if (map)
		map->Render(sprite);

	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Render(sprite);
	}
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);
}

void CGameScene::TileUpdate(float deltaTime)
{
	// ���ݱ��� ������ Ÿ���� ����
	float currentTileLength = tileList.size() * gAssetManager->GetTexture("Tile")->width;

	// ����ī�޶� ���� 1280 ���� Ÿ���� �����ϱ� ����
	// ����ī�޶� ��ġ + 1280 �� Ÿ���� ���� ���� �� ��� Ÿ���� �����ϱ� ����
	while (mainCamera->position.x + 1280.0f > currentTileLength)
	{
		// i == tileEntryInfo�� ������ �� �����
		// ����� ���� ���� ���� �� ������ �극��ũ
		if (currentTileEntryIndex == tileEntryInfo.size())
			break;
		// Ÿ�� �������� �������� ������ ������ ģ��
		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);
		// Ÿ�� ����Ʈ 0 - 1�� -1 �̹Ƿ� ����Ʈ üũ�� �� ������ �����ĸ�
		if (currentTileEntryIndex == 0)
		{
			entryPos.x = 0.0f;
			entryPos.y = 384.0f;
		}
		else
		{
			// ���� Ÿ�� �˻縦 ������ ģ��
			CTile* t = tileList[currentTileEntryIndex - 1];
			// ���� Ÿ�Ϸ� �Ѿ�� ���ؼ� ���� ������ ������ ������ x�� �̵� & ��ĭ �Ѿ�� ���̸� ������
			entryPos.x = t->position.x + gAssetManager->GetTexture("Tile")->width;
			// ������ ���̸� �ø��� ������ �������� ���� Ÿ�� ���̿� ���缭 ������ ������ ģ��
			entryPos.y = t->position.y;

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1: // ������
				// ���࿡ ���� Ÿ���� 2���̾ƴϸ� ������ 100 �÷��� ���̳ʽ��� �÷��ִ°��� ���ؾȵǸ� �׸� ��ġ���� �غ���
				if (tileEntryInfo[currentTileEntryIndex - 1].type != 2)
					entryPos.y -= 100.0f;
				break;
			default: // ���� & ������
				// ���� ���� Ÿ���� 2���̸� 100�� ������ ����
				if (tileEntryInfo[currentTileEntryIndex - 1].type == 2)
					entryPos.y += 100.0f;
				break;
			}
		}
		// Ÿ�� ���� ����Ʈ�� �ֱ�
		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
		tileList.push_back(tile);
		// for�� i���� ģ�� ++ ���ֱ�
		currentTileEntryIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

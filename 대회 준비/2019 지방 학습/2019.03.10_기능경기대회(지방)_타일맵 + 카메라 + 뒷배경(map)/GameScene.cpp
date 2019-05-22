#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage) :
	CScene(), tileEntryInfo(), currentTileEntryIndex(0) 
	// int ���� ������ ������ ���� ������ ������ �������ʰ� �ʱ�ȭ�� �ݵ�� �ؾ���
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	// Ÿ�� ���� ����
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));

	// ī�޶��� �����ӿ� ���Ѱ��� �����ϴ� �κ��� �̰Ϳ� ���� ������ ������ �׸����� ÷����
	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->tile_Texture->width - 1024.0f;
	// ������ ��������� �ʿ������ NULL �Ѱ��� 
	mainCamera->SetTarget(NULL);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end();++it)
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

	// ī�޶�
	// �ӽ� : �׽�Ʈ�� ���� ī�޶� Ű����� �̵�
	if (mainCamera)
	{
		if (GetKeyState(VK_LEFT) & 0x0800)
			mainCamera->position.x -= 300 * deltaTime;
		if (GetKeyState(VK_RIGHT) & 0x0800)
			mainCamera->position.x += 300 * deltaTime;
		if (GetKeyState(VK_UP) & 0x0800)
			mainCamera->position.y -= 300 * deltaTime;
		if (GetKeyState(VK_DOWN) & 0x0800)
			mainCamera->position.y += 300 * deltaTime;

		mainCamera->Update(deltaTime);
	}

	// ��
	// �� ���ӿ��� ���� �ڿ����̴� �����
	if (map)
		map->Update(deltaTime);

	// Ÿ�� ===================================================================================================================================
	//  - ���� ���� 
	//    ȭ���� ���� ������(ī�޶��� ��ġ + ȭ�� ���� ũ��)����
	//    ������ Ÿ�ϵ��� ���� ���� ���� ������ ���ο� Ÿ���� �����Ѵ�.

	// ���� ������ Ÿ���� ���� = ������ Ÿ�� �� * Ÿ�� �ý�ó�� ���α���
	float currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;

	// ȭ���� ���� ������ = ���� ī�޶��� ��ġ + ȭ���� ���� ũ��

	// while �ݺ������� ���� ȭ���� ���� ������ ��ġ�� ���� ������ Ÿ���� ���̺��� ū�� ��
	// ���ǿ� �����ϸ� Ÿ�� ���� ����

	// �Ʒ��� + 1280���� ���� ������ Ÿ�� ���� ��� �������ִµ� �װ��� ȭ�� ���̿� �� �°� �����ϸ� ������� ���ϱ�� ��¦ �� ũ�� ������ ��
	while (mainCamera->position.x + 1280.0f > currentTileLength)
	{

		// ���� �����Ǿ���ϴ� Ÿ���� ��ȣ(currentTileEntryIndex)�� Ÿ���� ���� ����(tileEntryInfo)���� ũ�ų� ���� ���� Ÿ�� ������ �������
		// �ٵ� ���� ���� ����� �߳�.. >= �� �� ������

		// �߰� ���� : �迭�� �ε����� 0���� �����̱� ������ �迭 ���̰� 5�� �迭�� 5�� �ε����� �����ϸ� ������ �׷��� �׷� <- �̰� �𸣰����� ����
		if (currentTileEntryIndex == tileEntryInfo.size()) break;

		// entryPos�� Ÿ���� ������ ��ġ��
		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		// Ÿ���� �����Ҷ� ���� ������ Ÿ���� ��ġ ������ ���� ���� ������ Ÿ���� ��ġ�� ���ؾ��ϴµ�
		// 0�� �� ó�� �����Ǵ� Ÿ���� ���� ������ ���⿡ ������ ��ġ�� �Է��Ѵ�.
		if (currentTileEntryIndex == 0)
		{
			entryPos.x = 0.0f;
			entryPos.y = 384.0f;
		}
		else
		{
			// �� �κ��� ���� Ÿ���� ��ġ ������ ���� ������ Ÿ���� ��ġ�� ����ϴ� ��

			// ���ϰ� ������� �̺κ� ������ ���߳�
			
			/*
			CTile* t = tileList[currentTileEntryIndex - 1];
			
			entryPos.x = t->position.x + gAssetManager->tile_Texture->width;
			entryPos.y = t->position.y;
			*/

			// �̺κ� �̷��� �����ϼ�
			auto it = tileList.begin();
			std::advance(it, currentTileEntryIndex - 1);

			entryPos.x = (*it)->position.x + gAssetManager->tile_Texture->width;
			entryPos.y = (*it)->position.y;
			// �� ���ٱ��� ���ŷ� �����ϼ���
			// ���� ���� : List�� TileList�� ����� auto�� �̿��ؼ� �����ؾ���
			//			   �׷��� Vector<>������ ����� �� ���� ���� ó�� [index]�� �迭 ���� ���� ������


			// �̰� ���� �����Ǿ�� �ϴ� Ÿ���� �ε��� (currentTileEntryIndex)�� ���� 
			// ���� �����Ǿ� �ϴ� Ÿ���� ����(Type : ����)�� ��� �� ������ �̿��� Y���� ��ġ�� ��� �� ��
			// 0 : ����
			// 1 : ������
			// 2 : ������

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1: // ������

				// �� ���ǹ��� �۷� Ǯ�ڸ�
				// ���� ������ Ÿ���� �������ε� ���� Ÿ���� ������ Ÿ���� �ƴϸ� Ÿ���� Y��ǥ�� ���� ���� ��ŭ(100) �ø���.
				if (tileEntryInfo[currentTileEntryIndex - 1].type != 2)
					entryPos.y -= 100.0f;
				break;
			default: // ���� & ������

				// �� ���ǹ��� �۷� Ǯ�ڸ�
				// ���� ������ Ÿ���� ������ �Ǵ� �����ε� ���� Ÿ���� ������ Ÿ���̶�� Ÿ���� Y��ǥ�� �Ʒ��� ���� ��ŭ(100) ������.
				if (tileEntryInfo[currentTileEntryIndex - 1].type == 2)
					entryPos.y += 100.0f;
				break;
			}

			// �̷��� �Ǵ� ������ �����ϱ� ����Ŷ�� �����ϴµ� �߰� ������ �׸����� ÷����
		}

		// �̷��� Ÿ���� ������ ��ġ�� ���� Ÿ���� ������ �����ϸ鼭 �����ϸ��
		CTile*tile = new CTile(entryPos, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
		tileList.push_back(tile); // ������ Ÿ�� ������ ���� �� Push_back


		// �׸��� Ÿ���� ���� �������� ���� ������ Ÿ���� ���̸� ������Ʈ ����
		currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;
		// ���� �����Ǿ�� �ϴ� Ÿ���� �ε��� ������ ������Ʈ
		currentTileEntryIndex++;
	}
	// ��������� Ÿ�� ����

	// ���� �� �ڵ忡�� �̰ͺ��� �� ��� ���� ���� �����ִµ�
	// �װ͵��� Ÿ���� �����Ǹ鼭 ���ÿ� �Ͼ���ϴ� �ϵ��� ���� ���⼭ ó���ϱ� �����̾�

	// ���� ���ڸ� ������ ����, ���� ����, ������ �������� �־� ���� ������ ����� �����ؾ߸� ������ ������ �� ����
	// =======================================================================================================================================

	// ������ Ÿ�� ������Ʈ
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Update(deltaTime);
	}
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	// �� �׸���
	if (map)
		map->Render(sprite);

	// Ÿ�� �׸���
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Render(sprite);
	}
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);
}
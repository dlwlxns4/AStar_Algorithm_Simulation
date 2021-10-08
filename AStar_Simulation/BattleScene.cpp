#include "BattleScene.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"

HRESULT BattleScene::Init()
{
	rocket = new Tank;
	if (FAILED(rocket->Init(TankType::Player)))
	{
		MessageBox(g_hWnd, "로켓을 초기화에 실패했습니다.", "오류", MB_OK);
		return E_FAIL;
	}

	Sleep(3000);

	// 적 매니저
	enemyMgr = new EnemyManager;
	enemyMgr->Init();

	// 배경 이미지
	ImageManager::GetSingleton()->AddImage("Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	backGround = ImageManager::GetSingleton()->FindImage("Image/background.bmp");
	if (backGround == nullptr)
	{
		cout << "Image/bin.bmp 파일 로드에 실패했다." << endl;

		return E_FAIL;
	}

	return S_OK;
}

void BattleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		SceneManager::GetSingleton()->ChangeScene("타이틀씬");
		return;
	}

	if (rocket)
		rocket->Update();

	if (enemyMgr)
		enemyMgr->Update();
}

void BattleScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);

	if (rocket)
		rocket->Render(hdc);

	if (enemyMgr)
		enemyMgr->Render(hdc);
}

void BattleScene::Release()
{
	SAFE_RELEASE(enemyMgr);
}

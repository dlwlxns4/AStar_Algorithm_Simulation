#include "TitleScene.h"
#include "Config.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

HRESULT TitleScene::Init()
{
	// 타이틀씬에서 사용할 UI 이미지도 로드해놓자.
	ImageManager::GetSingleton()->AddImage("Image/button.bmp", 122, 62, 1, 2);

	ImageManager::GetSingleton()->AddImage("Image/bin.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/bin.bmp");

	btnFunction = new ButtonFunction();

	btnGotoBattle = new Button();
	btnGotoBattle->Init(100, 100);
	// 버튼의 기능 셋팅(함수 포인터에 특정함수 주소설정 : 씬이동)
	// 매개변수 (어떤 씬으로, 어떤 로딩씬을)
	arg = new ArgumentFuncPtr;
	arg->sceneName = "전투씬";
	arg->loadingSceneName = "로딩씬";
	btnGotoBattle->SetFunc(&ButtonFunction::ChangeScene, btnFunction, arg);

	btnQuitProgram = new Button();
	btnQuitProgram->Init(WIN_SIZE_X - 100, 100);
	// 버튼의 기능 셋팅(함수 포인터에 특정함수 주소설정 : 닫기)
	btnQuitProgram->SetFunc(&ButtonFunction::QuitProgram, btnFunction);

	return S_OK;
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("전투씬", "로딩씬");
		return;
	}

	if (btnGotoBattle)
		btnGotoBattle->Update();
	if (btnQuitProgram)
		btnQuitProgram->Update();
}

void TitleScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);

	if (btnGotoBattle)
		btnGotoBattle->Render(hdc);
	if (btnQuitProgram)
		btnQuitProgram->Render(hdc);
}

void TitleScene::Release()
{
	SAFE_RELEASE(btnGotoBattle);
	SAFE_RELEASE(btnQuitProgram);
	SAFE_DELETE(btnFunction);
	SAFE_DELETE(arg);
}

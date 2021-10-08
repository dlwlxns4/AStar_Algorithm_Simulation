#include "LoadingScene.h"
#include "Config.h"
#include "Image.h"

HRESULT LoadingScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/loading.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/loading.bmp");

	if (backGround == nullptr)
		return E_FAIL;

	return S_OK;
}

void LoadingScene::Update()
{
}

void LoadingScene::Render(HDC hdc)
{
	backGround->Render(hdc);
}

void LoadingScene::Release()
{
}

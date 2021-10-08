#include "Enemy.h"
#include "Image.h"
#include "AmmoManager.h"

HRESULT Enemy::Init()
{
	elapsedCount = 0;
	fireDelay = rand() % 100;
	fireTimer = 0;

	ImageManager::GetSingleton()->AddImage("Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/ufo.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}

	ammoMgr = new AmmoManager;
	ammoMgr->Init();
	ammoMgr->SetOwner(this);

	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = 100.0f;
	moveSpeed = 1.0f;
	bodySize = 53;

	return S_OK;
}

void Enemy::Update()
{
	elapsedCount++;
	if (elapsedCount >= 10)
	{
		img->SetCurrFrameX(img->GetCurrFrameX() + 1);
		if (img->GetCurrFrameX() >= img->GetMaxFrameX())
		{
			img->SetCurrFrameX(0);
		}
		elapsedCount = 0;
	}

	// Ammo
	/*
		1. 랜덤시간마다 미사일을 한발씩 발사하도록 구현
		2. 딜레이 없이  30발 연속 발사 (1프레임 마다 1발씩)
	*/
	fireTimer++;
	if (fireTimer >= fireDelay)
	{
		ammoMgr->Fire();
		fireTimer = 0;
		fireDelay = rand() % 100;
	}
	ammoMgr->Update();
}

void Enemy::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y, img->GetCurrFrameX(), img->GetCurrFrameY());

	ammoMgr->Render(hdc);
}

void Enemy::Release()
{
	SAFE_RELEASE(ammoMgr);
}

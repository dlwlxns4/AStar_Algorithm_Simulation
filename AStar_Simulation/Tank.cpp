#include "Tank.h"
#include "Image.h"

HRESULT Tank::Init(TankType type)
{
	ImageManager::GetSingleton()->AddImage("Image/rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/rocket.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}

	this->type = type;

	switch (type)
	{
	case TankType::Player:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = WIN_SIZE_Y - 100.0f;

		bodySize = 80;
		moveSpeed = 3.0f;

		barrelSize = 140.0f;
		barrelAngle = 90.0f * (PI / 180.0f);
		break;
	case TankType::Enemy:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = 100.0f;

		bodySize = 100;
		moveSpeed = 5.0f;

		barrelSize = 140.0f;
		barrelAngle = 270.0f * (PI / 180.0f);
		break;
	}
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;

	moveDir = MoveDir::Right;

	isAlive = true;

	ammoCount = 2;
	ammoPack = new Ammo[ammoCount];
	// 미사일 초기화
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Init();
	}

	return S_OK;
}

void Tank::Update()
{
	if (isAlive == false)	return;

	// 위치에 따른 모양값 갱신
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Update();
	}

	switch (type)
	{
	case TankType::Player:
		ProcessInputKey();
		break;
	case TankType::Enemy:
		AutoMove();
		break;
	}
}

void Tank::Render(HDC hdc)
{
	if (isAlive == false)	return;

	// 몸통
	Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);

	// 미사일
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Render(hdc);
	}

	img->Render(hdc, pos.x, pos.y);
}

void Tank::Release()
{
	delete[] ammoPack;
}

void Tank::RotateBarrelAngle(float rotateAngle)
{
	barrelAngle += (rotateAngle * PI / 180.0f);

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;
}

void Tank::Fire()
{
	for (int i = 0; i < ammoCount; i++)
	{
		// 전체 미사일을 순회하면서 발사 됐는지 안됐는지 판단
		if (ammoPack[i].GetIsFire()/* && ammoPack[i].GetIsAlive()*/)
			continue;

		//ammoPack[i].SetIsAlive(true);
		ammoPack[i].SetPos(pos);	// 미사일 위치 변경
		ammoPack[i].SetIsFire(true);	// 미사일 상태 변경
		ammoPack[i].SetMoveAngle(barrelAngle); // 미사일 각도 변경

		break;
	}
}

void Tank::Reload()
{
}

void Tank::AutoMove()
{
	if (shape.right >= WIN_SIZE_X)
	{
		moveDir = MoveDir::Left;
	}
	else if (shape.left <= 0)
	{
		moveDir = MoveDir::Right;
	}

	switch (moveDir)
	{
	case MoveDir::Left:		pos.x -= moveSpeed; break;
	case MoveDir::Right:	pos.x += moveSpeed; break;
	}
}

void Tank::ProcessInputKey()
{
	// 키입력을 확인
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		Fire();
	}

	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		Move(MoveDir::Left);
	}
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		Move(MoveDir::Right);
	}

	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		Move(MoveDir::Up);
	}
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		Move(MoveDir::Down);
	}
}

void Tank::Move(MoveDir dir)
{
	switch (dir)
	{
	case MoveDir::Left: pos.x -= moveSpeed; break;
	case MoveDir::Right: pos.x += moveSpeed; break;
	case MoveDir::Up: pos.y -= moveSpeed; break;
	case MoveDir::Down: pos.y += moveSpeed; break;
	}
}

Tank::Tank()
{
}

Tank::~Tank()
{
}

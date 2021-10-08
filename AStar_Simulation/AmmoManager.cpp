#include "AmmoManager.h"
#include "Ammo.h"
#include "GameObject.h"
#include "Tank.h"

HRESULT AmmoManager::Init()
{
	owner = nullptr;

	//owner->Reload();	// x
	//((Tank*)owner)->Reload();	// o

	ammoMaxCount = 1;
	vecAmmos.resize(ammoMaxCount);

	for (itAmmos = vecAmmos.begin();
		itAmmos != vecAmmos.end(); itAmmos++)
	{
		(*itAmmos) = new Ammo;
		(*itAmmos)->Init();
	}

	return S_OK;
}

void AmmoManager::Update()
{
	for (itAmmos = vecAmmos.begin();
		itAmmos != vecAmmos.end(); itAmmos++)
	{
		(*itAmmos)->Update();
	}
}

void AmmoManager::Render(HDC hdc)
{
	for (itAmmos = vecAmmos.begin();
		itAmmos != vecAmmos.end(); itAmmos++)
	{
		(*itAmmos)->Render(hdc);
	}
}

void AmmoManager::Release()
{
	for (itAmmos = vecAmmos.begin();
		itAmmos != vecAmmos.end(); itAmmos++)
	{
		SAFE_RELEASE((*itAmmos));
	}
	vecAmmos.clear();
}

void AmmoManager::Fire()
{
	if (!owner) return;

	for (itAmmos = vecAmmos.begin();
		itAmmos != vecAmmos.end(); itAmmos++)
	{
		if ((*itAmmos)->GetIsFire())	continue;

		(*itAmmos)->SetIsFire(true);
		(*itAmmos)->SetPos(owner->GetPos());
		(*itAmmos)->SetMoveAngle(DEGREE_TO_RADIAN(270.0f));
		break;
	}
}

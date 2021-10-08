#pragma once
#include "GameEntity.h"

class Image;
class LoadingScene : public GameEntity
{
private:
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};


#pragma once
#include "GameObject.h"
//#include "Image.h"	// 컴파일 관계가 복잡, 컴파일 시간이 오래 걸림

class Image;	// 포함관계
class Iori : public GameObject	// 상속관계
{
private:
	Image* img;
	int frameX, frameY;
	int elapsedCount;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};


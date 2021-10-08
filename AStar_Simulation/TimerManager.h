#pragma once
#include "Config.h"
#include "Singleton.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
private:
	Timer* timer;
	char szText[256];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	float GetDeltaTime();
};


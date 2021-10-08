#include "KeyManager.h"

void KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		keyUp[i] = true;
		keyDown[i] = false;

		//keyUp.set(i, true);
		//keyDown.set(i, false);

		//keyUp.operator<<
	}
}

void KeyManager::Release()
{
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// 함수 호출 시점에 가상키(VK_...)가 어떤 상태인지 확인이 가능하다.
	/*
		1. 0x0000 ( 0000 0000 0000 0000 )
		-> 이전 프레임에 누른적이 없고 호출시점에도 눌려있지 않다.
		2. 0x0001 ( 0000 0000 0000 0001 )
		-> 이전 프레임에 누른적이 있고 호출시점에는 눌려있지 않다.
		3. 0x8000 ( 1000 0000 0000 0000 )
		-> 이전 프레임에 누른적이 없고 호출시점에는 눌려있다.
		4. 0x8001 ( 1000 0000 0000 0001 )
		-> 이전 프레임에 누르적이 있고 호출시점에도 눌려있다.
	*/
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (keyDown[key] == false)
		{
			keyDown[key] = true;
			return true;
		}
	}
	else
	{
		keyDown[key] = false;
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	// 실습1. 이 함수를 완성해보자.
	if (GetAsyncKeyState(key) & 0x8000)
	{
		keyUp[key] = false;
	}
	else
	{
		if (keyUp[key] == false)
		{
			keyUp[key] = true;
			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
//	bool b = 0x8000 & 0x8001;

	static time_t currTime;
	// 실습2. 얘도 해보자.
	if (GetAsyncKeyState(key) & 0x8001)
	{
		//cout << "1. true : " << time(&currTime) << endl;
		return true;
	}
	//else
	//{
	//	cout << "2. false : " << time(&currTime) << endl;
	//}

	//if (GetAsyncKeyState(key) & 0x0001)
	//{
	//	cout << "3. true : " << time(&currTime) << endl;
	//	return true;
	//}
	//else
	//{
	//	cout << "4. false : " << time(&currTime) << endl;
	//}
	//cout << endl << endl;

	return false;
}

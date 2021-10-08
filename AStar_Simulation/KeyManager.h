#pragma once
#include "Config.h"
#include <vector>
#include <bitset>	// stl자료구조 vector
#include "Singleton.h"

using namespace std;

#define KEY_MAX_COUNT	256

class KeyManager : public Singleton<KeyManager>
{
private:
	// 멤버변수 (데이터타입, 자료구조)
	//vector<int>
	//bool keyState[KEY_MAX_COUNT];

//protected:
//	static KeyManager* instance;		// static 멤버 변수
//
//	Singleton() {};		// 생성자, 소멸자를 직접 호출하지 못하게 할거다.
//	~Singleton() {};
//
//public:
//	static KeyManager* GetSingleton();
//	void ReleaseSingleton();

	bitset<KEY_MAX_COUNT>	keyUp;	// 키가 안 눌린 상태인지 아닌지
	bitset<KEY_MAX_COUNT>	keyDown;// 키가 눌린 상태인지 아닌지

public:
	void Init();
	void Release();

	bool IsOnceKeyDown(int key);	// 키가 첫번째로 눌렸는지 판단
	bool IsOnceKeyUp(int key);		// 키가 첫번째로 눌렸다가 떨어졌는지 판단
	bool IsStayKeyDown(int key);	// 키가 눌려져 있는지 판단
};


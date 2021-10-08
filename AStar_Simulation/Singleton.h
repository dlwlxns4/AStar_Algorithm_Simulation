// Singleton.h

// 싱글톤 패턴 : 프로그램에서 하나만 존재하는 객체가 필요할 때 사용되는 패턴
// 예시 ) 키 매니저 (관리하는 객체), 씬 매니저, 플레이어 데이터...

#pragma once

//goto

template <typename T>
/*static*/ class Singleton
{
protected:
	static T* instance;		// static 멤버 변수

	Singleton() {};		// 생성자, 소멸자를 직접 호출하지 못하게 할거다.
	~Singleton() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T* Singleton<T>::GetSingleton()
{
	if (!instance)
	{
		instance = new T;
	}
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

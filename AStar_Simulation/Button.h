#pragma once
#include "Config.h"
#include "GameObject.h"

/* 함수 포인터

	포인터 (변수 포인터)

	int a = 10;
	int* pA = &a;

	(*pA) = 20;


	void Func(void);		// 함수의 원형
	void (*pF)(void);	// 리턴타입과 매개변수가 동일한 함수의 주소를 담을 수 있는 함수포인터
*/

//int AddNum(int a, int b)
//{
//	return a + b;
//}
////
//int MinusNum(int a, int b)
//{
//	return a - b;
//}
////
//int (*pF)(int, int);

class ButtonFunction;
typedef void (*pVoidFunc)(void);
typedef int (*pIntFunc)(int, int);
//typedef void (ButtonFunction::*FuncPtr)(void);
typedef void (ButtonFunction::* FuncPtr)(ArgumentFuncPtr*);

enum class Button_Type { GotoBattle, GotoResult, Close, etc };
enum class Button_State { None, Down, Up };		// FSM : Finite State Machine 유한 상태 기계

class Button : public GameObject
{
private:
	Button_Type type;
	Button_State state;

	ButtonFunction* bf;
	FuncPtr pFunc;
	ArgumentFuncPtr* arg;

	void (*funcPtr)(void);

public:
	virtual HRESULT Init() override;
	virtual HRESULT Init(int posX, int posY);
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	//void SetNum(int num) { this->num = num; }
	//void SetFunc(void (*funcPtr)(void)) { this->funcPtr = funcPtr; }
	//void SetFunc(pF funcPtr) { this->funcPtr = funcPtr; }
	void SetFunc(FuncPtr pFunc, ButtonFunction* bf, ArgumentFuncPtr* arg = nullptr)
	{
		this->pFunc = pFunc; this->bf = bf; this->arg = arg;
	}
};


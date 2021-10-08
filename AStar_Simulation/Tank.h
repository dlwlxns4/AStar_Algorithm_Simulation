#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class Tank : public GameObject	// 상속관계
{
public:
	TankType type;
	// 
	// GameObject 상속 변수
	// 위치, 모양, 이동속도

	// 자체 멤버 변수
	// 포신 (두 점의 좌표)
	POINTFLOAT barrelEnd;
	float barrelSize;
	float barrelAngle;

	int ammoCount;
	Ammo* ammoPack;
	//Ammo ammo[ammoCount];

	MoveDir moveDir;

	bool isAlive;


public:
	HRESULT Init(TankType type);		// 부모클래스의 함수 중 기능이 다른 경우는
	void Update();		// 오버라이딩을 한다
	void Render(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void AutoMove();
	void ProcessInputKey();

	// 실습3. 탱크를 상하좌우(WASD)로 움직여보자.
	void Move(MoveDir dir);

	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	Tank();
	~Tank();
};


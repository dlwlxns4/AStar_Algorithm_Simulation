#pragma once
#include "Config.h"
#include "GameEntity.h"

class Enemy;
class EnemyManager : public GameEntity
{
private:
	vector<Enemy*> vecEnemys;
	vector<Enemy*>::iterator itEnemys;

	int enemyMaxCount;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AddEnemy(float posX, float posY);
};


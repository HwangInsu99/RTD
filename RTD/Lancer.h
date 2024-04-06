#pragma once
#include "Tower.h"
#include "MonsterManager.h"

class Lancer : public Tower
{
public:
	MonsterManager* monsterMgr;
	static CImage images[3];


	static void LoadImage();

	Lancer(int a, int b, int c);
	void Draw(CDC& dc);
	void CheckIn(CRect monRect, int x);
	void Attack();
	void posChange();
	void GetRect(CRect& rect);
	void GetRect2(CRect& rect);
};


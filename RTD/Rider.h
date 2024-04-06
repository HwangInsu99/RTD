#pragma once
#include "Tower.h"
#include "MonsterManager.h"

class Rider : public Tower
{
public:
	MonsterManager* monsterMgr;
	static CImage images[3];


	static void LoadImage();

	Rider(int a, int b, int c);
	void Draw(CDC& dc);
	void CheckIn(CRect monRect, int x);
	void Attack();
	void posChange();
	void GetRect(CRect& rect);
};


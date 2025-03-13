#pragma once
#include "Monster.h"

class Enemy : public Monster
{
public:

	static CImage images;
	int round;

	static void LoadImage();

	Enemy(int a);
	void Draw(CDC& dc);
	void GetRect(CRect& rect);
	void Tick();
	void Damaged(int x);
	void ContactCollide();
};


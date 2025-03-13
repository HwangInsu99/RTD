#pragma once

class Monster
{
public:
	int hp;
	int Dir;
	int speed;
	int x, y;
	bool die;
	bool decrease;
	CRect damageRect;


	virtual void Draw(CDC& dc) = 0;
	virtual void Tick() = 0;
	virtual void GetRect(CRect& rect) = 0;
	virtual void Damaged(int x) = 0;
	virtual void ContactCollide() = 0;
};


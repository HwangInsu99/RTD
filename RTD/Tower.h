#pragma once

class Tower
{
public:
	int a,b,posture,grade;
	int damage;
	int aSpeed;
	int target;
	bool active;
	HWND type;

	virtual void Draw(CDC& dc) = 0;
	virtual void CheckIn(CRect monRect, int x) = 0;
	virtual void posChange() = 0;
};


#pragma once

class Tower
{
public:
	virtual ~Tower() {}

	int a,b,posture,grade;
	int damage;
	int aSpeed;
	int target;
	int range;
	bool active;

	virtual void Draw(CDC& dc) = 0;
	virtual void CheckIn(CRect monRect, int x) = 0;
	virtual void posChange() = 0;
};
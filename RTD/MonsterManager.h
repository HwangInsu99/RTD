#pragma once
class Monster;
class MonsterManager
{
public:
	Monster* monster[15];
	int num, extraMon, fieldMon;

	MonsterManager();
	~MonsterManager();
	void SummMonster(int x);
	void Draw(CDC& dc);
	void Tick();
	void Reset();
	void Damage(int x, int y);
	int CheckHp(int x);
	void LoadImage();
};


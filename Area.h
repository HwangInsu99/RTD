#pragma once

class Monster;
class TowerManager;

class Area
{
public:
	CRect ChRect[10];
	CRect SummRect[46];
	CRect EndRect;
	int Dir;
	int empty[46];
	int num;
	TowerManager* towerMgr;

	Area();
	void ControlTower(int x, int y, STATE z);
	void Draw(CDC& dc, STATE state);
	void NextRound();
	void Check(CRect rect, int x);
	void Tick();
	void LoadImage();
};


#pragma once
//#include <vector>

class Tower;

class TowerManager
{
public:
	Tower* tower[46];
	int money;
	//std::vector<Tower*> tower;


	TowerManager();
	~TowerManager();
	void summTower(int x, int y);
	void UpgradeTower(int x);
	void attackCheck(CRect rect, int x);
	void Tick();
	void Draw(CDC& dc);
	void Delete(int i);
	void LoadImage();
};


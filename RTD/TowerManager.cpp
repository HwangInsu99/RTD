#include "pch.h"
#include "TowerManager.h"
#include "Archer.h"
#include "Lancer.h"
#include "Rider.h"
#include "Saber.h"
#include "Monster.h"


//타워 중앙좌표
int point[] = { 71, 130, 130, 130,	71, 174,130, 174,71, 222, 130, 222 ,225, 130,280, 130,	225, 174,	280, 174,	225, 222,
	280, 222,	373, 155,	433, 155,	373, 219,	433, 219,	30, 301,	78, 301,	135, 301,	30, 357,	78, 357,	135, 357,	225, 302,	280, 302,
	224, 357,	280, 357,	366, 302,	416, 302,	468, 302,	366, 359,	416, 359,	468, 359,	64, 460,	124, 460,
	64, 521,	124, 521,	224, 457,	281, 457,	224, 515,	281, 515,	224, 570,	281, 570,	372, 465,	432, 465,	372, 526,	432, 526 };

TowerManager::TowerManager()
{
	money = 300;
	for (int i = 0; i < 46; i++)
		tower[i] = nullptr;
}


TowerManager::~TowerManager() {
	for (int i = 0; i < 46; i++)
		if (tower[i] != nullptr)
			delete tower[i];
}

void TowerManager::summTower(int x, int y)
{
	if (money >= 50) {
		money = money - 50;
		switch (y)
		{
		case 0:
			tower[x] = new Archer(point[2 * x], point[2 * x + 1], 1);
			break;
		case 1:
			tower[x] = new Lancer(point[2 * x], point[2 * x + 1], 1);
			break;
		case 2:
			tower[x] = new Rider(point[2 * x], point[2 * x + 1], 1);
			break;
		case 3:
			tower[x] = new Saber(point[2 * x], point[2 * x + 1], 1);
			break;
		}
	}
}

void TowerManager::UpgradeTower(int x)
{
	srand((unsigned int)time(NULL));
	int num = rand() % 4;
	if (tower[x]->grade == 1 && money >= 50) {
		delete tower[x];
		tower[x] = nullptr;
		money = money - 50;
		switch (num)
		{
		case 0:
			tower[x] = new Archer(point[2 * x], point[2 * x + 1], 2);
			break;
		case 1:
			tower[x] = new Lancer(point[2 * x], point[2 * x + 1], 2);
			break;
		case 2:
			tower[x] = new Rider(point[2 * x], point[2 * x + 1], 2);
			break;
		case 3:
			tower[x] = new Saber(point[2 * x], point[2 * x + 1], 2);
			break;
		}
	}
	else if (tower[x]->grade == 2 && money >= 100) {
		delete tower[x];
		tower[x] = nullptr;
		money = money - 100;
		switch (num)
		{
		case 0:
			tower[x] = new Archer(point[2 * x], point[2 * x + 1], 3);
			break;
		case 1:
			tower[x] = new Lancer(point[2 * x], point[2 * x + 1], 3);
			break;
		case 2:
			tower[x] = new Rider(point[2 * x], point[2 * x + 1], 3);
			break;
		case 3:
			tower[x] = new Saber(point[2 * x], point[2 * x + 1], 3);
			break;
		}
	}
}

void TowerManager::attackCheck(CRect rect , int x)
{
	//타워가 공격상태가 아닐시 타워의 CheckIn실시
	for (int i = 0; i < 46; i++) {
		if (tower[i] != nullptr) {
			if (!tower[i]->active) {
				tower[i]->CheckIn(rect, x);
			}
		}
	}

}

void TowerManager::Tick()
{
	//타워가 공격상태일시 타워의 posChange실시
	for (int i = 0; i < 46; i++) {
		if (tower[i] != nullptr) {
			if (tower[i]->active) {
				tower[i]->posChange();
			}
		}
	}
}

void TowerManager::Draw(CDC& dc) {
	CString str;
	str.Format(L"돈: %d", money);
	dc.TextOutW(520, 130, str);
	for (int i = 0; i < 46; i++)
		if (tower[i] != nullptr)
			tower[i]->Draw(dc);
}

void TowerManager::Delete(int i) {
	//타워판매
	if (tower[i] != nullptr)
	{
		switch (tower[i]->grade) {
		case 1:
			money = money + 25;
			break;
		case 2:
			money = money + 50;
			break;
		case 3:
			money = money + 100;
			break;
		}
		delete tower[i];
	}
	tower[i] = nullptr;
}


void TowerManager::LoadImage() {
	Archer::LoadImage();
	Lancer::LoadImage();
	Rider::LoadImage();
	Saber::LoadImage();
}
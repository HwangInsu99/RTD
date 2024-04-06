#include "pch.h"
#include "MonsterManager.h"
#include "Enemy.h"
#include "Area.h"
#include "RTDDlg.h"

MonsterManager::MonsterManager()
{
	num = 0; // 현재 라운드
	fieldMon = 0; // 현재 소환되어있는 몬스터의 수
	extraMon = 15; // 소환될 몬스터의 수
	for (int i = 0; i < 15; i++)
		monster[i] = nullptr;
}

MonsterManager::~MonsterManager()
{
	for (int i = 0; i < 15; i++)
		if (monster[i] != nullptr)
			delete monster[i];
}

void MonsterManager::SummMonster(int x)
{
	if (extraMon > 0) {
		monster[num] = new Enemy(x);
		monster[num]->die = false;
		monster[num]->decrease = false;
		extraMon--;
		fieldMon++;
		num++;
	}
}

void MonsterManager::Draw(CDC& dc)
{
	CString str;
	for (int i = 0; i < 15; i++)
		if (monster[i] != nullptr)
			monster[i]->Draw(dc);
	str.Format(L"남은 몬스터 : %d", fieldMon);
	dc.TextOutW(320, 50, str);
}

void MonsterManager::Tick()
{
	Area* area = ((CRTDDlg*)AfxGetMainWnd())->area;
	for (int i = 0; i < 15; i++) {
		if (monster[i] != nullptr) {
			//몬스터를 delete하지 않고 재활용하기때문에 fieldMon을 한번만 감소시키게 하기위한 코드
			if (monster[i]->die && !monster[i]->decrease) {
				monster[i]->decrease = true;
				fieldMon--;
			}
				
			else {
				monster[i]->Tick();
				monster[i]->ContactCollide();
				if(!monster[i]->die)
					area->Check(monster[i]->damageRect, i);
			}
		}
	}
}
void MonsterManager::Reset()
{
	//소환할 몬스터및 현재남은 마리수 초기화
	extraMon = 15;
	num = 0;
	for (int i = 0; i < 15; i++) {
		monster[i]->Dir = 1;
		monster[i]->x = 15;
		monster[i]->y = 115;
	}
}

void MonsterManager::Damage(int x, int y)
{
	if(!monster[x]->die)
		monster[x]->Damaged(y);
}

int MonsterManager::CheckHp(int x)
{
	return monster[x]->hp;
}


void MonsterManager::LoadImage()
{
	Enemy::LoadImage();
}

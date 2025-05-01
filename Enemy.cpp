#include "pch.h"
#include "Monster.h"
#include "Enemy.h"
#include "Area.h"
#include "RTDDlg.h"

CImage Enemy::images;

void Enemy::LoadImage()
{
	images.Load(L"images\\Enemy.png");
}

Enemy::Enemy(int a) {
	x = 15;
	y = 115;
	speed = 10;
	Dir = 4;
	die = false;
	decrease = false;
	this->round = a;
	this->hp = 20 + 10*round;
}


void Enemy::Tick()
{
	//방향전환
	if (!die) {
		if (Dir == 1)
			x += speed;
		else if (Dir == 2)
			y -= speed;
		else if (Dir == 3)
			x -= speed;
		else if (Dir == 4)
			y += speed;
		damageRect.SetRect(x - 10, y - 10, x + 10, y + 10);
	}
}
void Enemy::Damaged(int x)
{
	if (!die) {
		hp = hp - x;
		if (hp <= 0) {
			die = true;
		}
	}
}
//특정좌표에 닿았는지 확인
void Enemy::ContactCollide()
{
	if (!die) {
		Area* area = ((CRTDDlg*)AfxGetMainWnd())->area;
		CRect conRect;
		GetRect(conRect);
		CRect diff;
		for (int i = 0; i < 10; i++) {
			if (diff.IntersectRect(&conRect, &area->ChRect[i])) {
				Dir = (i % 4) + 1;
				return; // 첫 번째 충돌 시 바로 방향을 설정하고 리턴
			}
		}
		if (diff.IntersectRect(&conRect, &area->EndRect)) {
			die = true;
		}
	}
}

void Enemy::Draw(CDC& dc)
{
	if(!die)
		images.Draw(dc, x, y, 25, 25);
}

void Enemy::GetRect(CRect& rect)
{
	if(!die)
		rect.SetRect(x + 5, y + 5, x + 15, y + 15);
}
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
	Dir = 1;
	die = false; //모든 클래스는 본 Enemy가 !die일때 실행한다
	decrease = false; // Enemy재활용을 위한 bool
	this->round = a;
	this->hp = 20 + 10*round;
}


void Enemy::Tick()
{
	//이동
	if (!die) {
		if (Dir == 1)
			y += speed;
		else if (Dir == 2)
			x += speed;
		else if (Dir == 3)
			y -= speed;
		else if (Dir == 4)
			x -= speed;
		damageRect.SetRect(x + 5, y + 5, x + 15, y + 15);
	}
}
void Enemy::Damaged(int x)
{
	if (!die) {
		hp = hp - x;
		if (hp <= 0)
			die = true;
	}
}

void Enemy::ContactCollide()
{
	//방향전환
	if (!die) {
		Area* area = ((CRTDDlg*)AfxGetMainWnd())->area;
		CRect conRect;
		GetRect(conRect);
		CRect diff;
		if (diff.IntersectRect(&conRect, &area->ChRect[0])) {
			Dir = 2;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[1])) {
			Dir = 3;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[2])) {
			Dir = 4;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[3])) {
			Dir = 1;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[4])) {
			Dir = 2;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[5])) {
			Dir = 3;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[6])) {
			Dir = 4;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[7])) {
			Dir = 1;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[8])) {
			Dir = 2;
		}
		else if (diff.IntersectRect(&conRect, &area->ChRect[9])) {
			Dir = 3;
		}
		else if (diff.IntersectRect(&conRect, &area->EndRect)) {
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
	//죽었을시 렉트를 갖지않기에 타워의 CheckIn에 잡히지않는다.
	if(!die)
		rect.SetRect(x + 5, y + 5, x + 15, y + 15);
}


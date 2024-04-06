#include "pch.h"
#include "Archer.h"
#include "Tower.h"
#include "RTDDlg.h"

CImage Archer::images[3];

void Archer::LoadImage()
{
	images[0].Load(L"images\\archer.png");
	images[1].Load(L"images\\archer1.png");
	images[2].Load(L"images\\archer2.png");
}
Archer::Archer(int a, int b, int c)
{
	monsterMgr = ((CRTDDlg*)AfxGetMainWnd())->monsterMgr;
	this->a = a;
	this->b = b;
	this->grade = c;
	this->posture = 0;
	this->active = false;
	this->target = 16;
	damage = 4 + 4 * grade;
}
void Archer::Draw(CDC& dc)
{
	images[posture].Draw(dc, a - (10 + grade * 5), b - (10 + grade * 5), 20 + grade * 10, 20 + grade * 10);
}
void Archer::CheckIn(CRect monRect, int x)
{
	//공격범위에 몬스터가 들어와있을시 대상을 지정
	CRect myRect;
	GetRect(myRect);
	CRect diff;
	if (diff.IntersectRect(&myRect, &monRect) && !active) {
		target = x;
		active = true;
	}
}
void Archer::Attack()
{
	monsterMgr->Damage(target, damage);
}

void Archer::posChange()
{
	//공격동작
	if (posture == 2) {
		Attack();
		posture = 0;
		active = false;
		target = 16;
	}
	else
		posture++;
}

void Archer::GetRect(CRect& rect)
{
	rect.SetRect(a - 120, b - 120, a + 120, b + 120);
}

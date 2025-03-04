#include "pch.h"
#include "Rider.h"
#include "Tower.h"
#include "RTDDlg.h"

CImage Rider::images[3];

void Rider::LoadImage()
{
	images[0].Load(L"images\\rider.png");
	images[1].Load(L"images\\rider1.png");
	images[2].Load(L"images\\rider2.png");
}
Rider::Rider(int a, int b, int c)
{
	monsterMgr = ((CRTDDlg*)AfxGetMainWnd())->monsterMgr;
	this->a = a;
	this->b = b;
	this->grade = c;
	this->posture = 0;
	this->active = false;
	this->target = 16;

	damage = 3 + 4 * grade;
}


void Rider::Draw(CDC& dc)
{
	images[posture].Draw(dc, a - (10 + grade * 5), b - (10 + grade * 5), 20 + grade * 10, 20 + grade * 10);
}
void Rider::CheckIn(CRect monRect, int x)
{
	CRect myRect;
	GetRect(myRect);
	CRect diff;
	if (diff.IntersectRect(&myRect, &monRect) && !active) {
		target = x;
		active = true;
	}
}
void Rider::Attack()
{
	monsterMgr->Damage(target, damage);
}
void Rider::posChange()
{
	if (posture == 2) {
		Attack();
		posture = 0;
		active = false;
		target = 16;
	}
	else
		posture++;
}
void Rider::GetRect(CRect& rect)
{
	rect.SetRect(a - 180, b - 180, a + 180, b + 180);
}

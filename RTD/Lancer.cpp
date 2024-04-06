#include "pch.h"
#include "Lancer.h"
#include "Tower.h"
#include "RTDDlg.h"

CImage Lancer::images[3];

void Lancer::LoadImage()
{
	images[0].Load(L"images\\lancer.png");
	images[1].Load(L"images\\lancer1.png");
	images[2].Load(L"images\\lancer2.png");
}
Lancer::Lancer(int a, int b, int c)
{
	monsterMgr = ((CRTDDlg*)AfxGetMainWnd())->monsterMgr;
	this->a = a;
	this->b = b;
	this->grade = c;
	this->posture = 0;
	this->active = false;
	this->target = 16;

	damage = 3 + 5 * grade;
}

void Lancer::Draw(CDC& dc)
{
	images[posture].Draw(dc, a - (10 + grade * 5), b - (10 + grade * 5), 20 + grade * 10, 20 + grade * 10);
}
void Lancer::CheckIn(CRect monRect, int x)
{
	CRect myRect;
	GetRect(myRect);
	CRect myRect2;
	GetRect2(myRect2);
	CRect diff;
	if (diff.IntersectRect(&myRect, &monRect) && !active) {
		target = x;
		active = true;
	}
	else if (diff.IntersectRect(&myRect2, &monRect) && !active) {
		target = x;
		active = true;
	}
}
void Lancer::Attack()
{
	monsterMgr->Damage(target, damage);
}
void Lancer::posChange()
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
void Lancer::GetRect(CRect& rect)
{
	rect.SetRect(a - 120, b - 30, a + 120, b + 30);
}

void Lancer::GetRect2(CRect& rect)
{
	rect.SetRect(a - 30, b - 120, a + 30, b + 120);
}

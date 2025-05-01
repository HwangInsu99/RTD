#include "pch.h"
#include "Saber.h"
#include "Tower.h"
#include "RTDDlg.h"

CImage Saber::images[3];

void Saber::LoadImage()
{
	images[0].Load(L"images\\saber.png");
	images[1].Load(L"images\\saber1.png");
	images[2].Load(L"images\\saber2.png");
}
Saber::Saber(int a, int b, int c)
{
	monsterMgr = ((CRTDDlg*)AfxGetMainWnd())->monsterMgr;
	this->a = a;
	this->b = b;
	this->grade = c;
	this->posture = 0;
	this->active = false;
	this->target = 16;
	this->range = 80;
	damage = 5 + 5 * grade;
}
void Saber::Draw(CDC& dc)
{
	images[posture].Draw(dc, a - (10 + grade * 5), b - (10 + grade * 5), 20 + grade * 10, 20 + grade * 10);
}
void Saber::CheckIn(CRect monRect, int x)
{
	CPoint points[4] = {
		CPoint(monRect.left, monRect.top),
		CPoint(monRect.right, monRect.top),
		CPoint(monRect.left, monRect.bottom),
		CPoint(monRect.right, monRect.bottom)
	};
	for (int i = 0; i < 4; i++) {
		int dx = points[i].x - a;
		int dy = points[i].y - b;

		if ((dx * dx + dy * dy) <= (range * range)) {
			target = x;
			active = true;
		}
	}
}
void Saber::Attack()
{
	monsterMgr->Damage(target, damage);
}
void Saber::posChange()
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
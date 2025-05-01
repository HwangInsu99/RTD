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
	this->range = 110;
	damage = 3 + 5 * grade;
}
void Lancer::Draw(CDC& dc)
{
	images[posture].Draw(dc, a - (10 + grade * 5), b - (10 + grade * 5), 20 + grade * 10, 20 + grade * 10);
}
void Lancer::CheckIn(CRect monRect, int x)
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
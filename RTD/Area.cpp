#include "pch.h"
#include "Area.h"
#include "TowerManager.h"
#include "Monster.h"

Area::Area()
{
	towerMgr = new TowerManager();
	Dir = 1;
	num = 0;
	EndRect = new CRect(167,113,193,130);

	//몬스터 방향전환 좌표
	ChRect[0] = new CRect(19, 250, 36, 265);
	ChRect[1] = new CRect(470, 250, 485, 265);
	ChRect[2] = new CRect(470, 110, 485, 120);
	ChRect[3] = new CRect(310, 110, 325, 120);
	ChRect[4] = new CRect(310, 575, 325, 583);
	ChRect[5] = new CRect(470, 575, 485, 583);
	ChRect[6] = new CRect(470, 390, 485, 395);
	ChRect[7] = new CRect(14, 396, 20, 415);
	ChRect[8] = new CRect(14, 575, 20, 583);
	ChRect[9] = new CRect(173, 575, 188, 583);

	//타워 생성가능위치 좌표
	SummRect[0] = new CRect(50, 115, 95, 145);
	SummRect[1] = new CRect(105, 115, 155, 145);
	SummRect[2] = new CRect(50, 153, 95, 195);
	SummRect[3] = new CRect(105, 153, 155, 195);
	SummRect[4] = new CRect(50, 204, 95, 240);
	SummRect[5] = new CRect(105, 204, 155, 240);
	SummRect[6] = new CRect(205, 115, 245, 145);
	SummRect[7] = new CRect(258, 115, 303, 145);
	SummRect[8] = new CRect(205, 153, 245, 195);
	SummRect[9] = new CRect(258, 153, 303, 195);
	SummRect[10] = new CRect(205, 204, 245, 240);
	SummRect[11] = new CRect(258, 204, 303, 240);
	SummRect[12] = new CRect(348, 134, 397, 186);
	SummRect[13] = new CRect(406, 132, 460, 186);
	SummRect[14] = new CRect(348, 194, 397, 244);
	SummRect[15] = new CRect(406, 194, 460, 244);
	SummRect[16] = new CRect(12, 275, 48, 327);
	SummRect[17] = new CRect(54, 275, 102, 327);
	SummRect[18] = new CRect(109, 275, 161, 327);
	SummRect[19] = new CRect(12, 334, 48, 380);
	SummRect[20] = new CRect(54, 334, 102, 380);
	SummRect[21] = new CRect(109, 334, 161, 380);
	SummRect[22] = new CRect(201, 277, 248, 328);
	SummRect[23] = new CRect(256, 277, 304, 328);
	SummRect[24] = new CRect(201, 334, 248, 380);
	SummRect[25] = new CRect(256, 334, 304, 380);
	SummRect[26] = new CRect(346, 275, 386, 327);
	SummRect[27] = new CRect(393, 275, 440, 327);
	SummRect[28] = new CRect(447, 275, 489, 327);
	SummRect[29] = new CRect(346, 334, 386, 385);
	SummRect[30] = new CRect(393, 334, 440, 385);
	SummRect[31] = new CRect(447, 334, 489, 385);
	SummRect[32] = new CRect(38, 435, 90, 486);
	SummRect[33] = new CRect(97, 435, 152, 486);
	SummRect[34] = new CRect(38, 492, 90, 550);
	SummRect[35] = new CRect(97, 492, 152, 550);
	SummRect[36] = new CRect(201, 432, 248, 482);
	SummRect[37] = new CRect(255, 432, 307, 482);
	SummRect[38] = new CRect(201, 488, 248, 542);
	SummRect[39] = new CRect(255, 488, 307, 542);
	SummRect[40] = new CRect(201, 548, 248, 591);
	SummRect[41] = new CRect(255, 548, 307, 591);
	SummRect[42] = new CRect(348, 438, 397, 493);
	SummRect[43] = new CRect(404, 436, 460, 494);
	SummRect[44] = new CRect(348, 500, 397, 552);
	SummRect[45] = new CRect(404, 500, 460, 552);

	for (int i = 0; i < 46; i++)
		empty[i] = 4;
}


void Area::ControlTower(int x, int y, STATE state)
{
	CPoint clickP(x, y);

	srand((unsigned int)time(NULL));
	

	if (state == 1) { // 타워 생성
		for (int i = 0; i < 46; i++) {
			if (SummRect[i].PtInRect(clickP) && empty[i] == 4) {
				num = rand() % 4;
				empty[i] = num;
				towerMgr->summTower(i,num);
				break;
			}
		}
	}
	else if (state == 2) { // 업그레이드
		for (int i = 0; i < 46; i++) {
			if (SummRect[i].PtInRect(clickP) && empty[i] != 4) {
				towerMgr->UpgradeTower(i);
			}
		}
	}
	else if (state == 3) { // 팔기
		for (int i = 0; i < 46; i++) {
			if (SummRect[i].PtInRect(clickP) && empty[i] != 4) {
				empty[i] = 5;
				towerMgr->Delete(i);
				break;
			}
		}
	}
}

void Area::Draw(CDC& dc, STATE state) {
	CString str;
	if (state == 1) {
		str.Format(L"생성");
		dc.TextOutW(520, 70, str);
	}
	else if (state == 2) {
		str.Format(L"업그레이드");
		dc.TextOutW(520, 70, str);
	}
	else if (state == 3) {
		str.Format(L"판매");
		dc.TextOutW(520, 70, str);
	}

	towerMgr->Draw(dc);
}

void Area::NextRound()
{
	towerMgr->money = towerMgr->money + 200;
}

void Area::Check(CRect rect, int x)
{
	towerMgr->attackCheck(rect, x);
}

void Area::Tick()
{
	towerMgr->Tick();
}

void Area::LoadImage() {
	towerMgr->LoadImage();
}
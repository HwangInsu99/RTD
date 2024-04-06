// SocCom.cpp: 구현 파일
//

#include "pch.h"
#include "RTD.h"
#include "SocCom.h"


// SocCom

SocCom::SocCom()
{
}

SocCom::~SocCom()
{
}


// SocCom 멤버 함수


void SocCom::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}

void SocCom::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hWnd, UM_RECEIVE_WM_USER, 0, 0);
	CSocket::OnReceive(nErrorCode);

}

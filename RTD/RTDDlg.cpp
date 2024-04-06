
// RTDDlg.cpp: 구현 파일

// 준비완료 버튼을 만들어서 

#include "pch.h"
#include "framework.h"
#include "RTD.h"
#include "RTDDlg.h"
#include "Area.h"
#include "MonsterManager.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRTDDlg 대화 상자



CRTDDlg::CRTDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RTD_DIALOG, pParent)
	,m_strIP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	monsterMgr = new MonsterManager();
	area = new Area();
	round = 1;
	round2 = 1;
	y = 0;
	state = 0;
	victory = 0;
	connected = false;
	progress = false;
	backG.Load(L"images\\BackG.png");
	connStr.Load(L"images\\conn.png");
	create.Load(L"images\\create.png");
	upgrade.Load(L"images\\upgrade.png");
	sell.Load(L"images\\sell.png");

}

CRTDDlg::~CRTDDlg() {
	delete monsterMgr;
	delete area;
}

void CRTDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRTDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_MESSAGE(UM_RECEIVE_WM_USER, OnReceive)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


LPARAM CRTDDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	TCHAR pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);

	m_socCom.Receive(pTmp, 256);
	strTmp.Format(L"%s", pTmp);

	if (strTmp == "Victory") {
		victory = 2;
		progress = false;
		Invalidate();
	}
	if (strTmp == "START")
		progress = true;
	else if (_ttoi(strTmp) > 0 )
		round2 = _ttoi(strTmp);

	return LPARAM();
}

// CRTDDlg 메시지 처리기

BOOL CRTDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	monsterMgr->LoadImage();
	area->LoadImage();

	SetTimer(1, 70, nullptr);
	SetTimer(2, 500, nullptr);
	SetTimer(3, 250, nullptr);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRTDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE) { // 클라이언트 종료시 서버로 메세지
		m_socCom.Send(L"DISCONNECT", 256);
		this->EndDialog(IDCANCEL);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRTDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		CRect rect;
		this->GetClientRect(&rect);

		CDC MemDC;
		CBitmap* pOldBitmap, bmp;

		MemDC.CreateCompatibleDC(&dc);
		bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		pOldBitmap = MemDC.SelectObject(&bmp);
		MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
		
		backG.Draw(MemDC, 0, 100, 500, 500);
		create.Draw(MemDC, 520, 180, 70, 70);
		upgrade.Draw(MemDC, 520, 280, 70, 70);
		sell.Draw(MemDC, 520, 380, 70, 70);


		if (victory == 1) {
			str.Format(L"YOU WIN");
			MemDC.TextOutW(250, 30, str);
		}
		else if (victory == 2) {
			str.Format(L"you Lose");
			MemDC.TextOutW(250, 30, str);
		}
		else {
			str.Format(L"Round : % d", round);
			MemDC.TextOutW(250, 30, str);
		}
		CString shot;
		shot.Format(L"상대 라운드");
		MemDC.TextOutW(500, 10, shot);
		str2.Format(L"Round : %d", round2);
		MemDC.TextOutW(500, 30, str2);
		connStr.Draw(MemDC, 20, 20, 50, 30);


		monsterMgr->Draw(MemDC);
		area->Draw(MemDC, state);

		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

		MemDC.SelectObject(pOldBitmap);

		MemDC.DeleteDC();
		bmp.DeleteObject();

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRTDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRTDDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint(650, 650);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CRTDDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//좌표에 대응하는 버튼이벤트
	//서버접속
	if (point.x >= 20 && point.x <= 70 && point.y >= 20 && point.y <= 50 && !connected)
		Connect();
	//생성
	else if (point.x <= 590 && point.x >= 520 && point.y >= 180 && point.y <= 250)
		state = 1;
	//업그레이드
	else if (point.x <= 590 && point.x >= 520 && point.y >= 280 && point.y <= 350)
		state = 2;
	//판매
	else if (point.x <= 590 && point.x >= 520 && point.y >= 380 && point.y <= 450)
		state = 3;
	//초기화
	else if (state != 0) {
		area->ControlTower(point.x, point.y, state);
		state = 0;
	}
	Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CRTDDlg::OnTimer(UINT_PTR nIDEvent)
{
	//서버에서 시작신호를 주지않으면 작동하지않음
	if (progress) {
		switch (nIDEvent)
		{
			//몬스터매니저및 라운드와 승리확인
		case 1:
			monsterMgr->Tick();
			if (monsterMgr->extraMon <= 0 && monsterMgr->fieldMon <= 0 && round != 8) {
				round++;
				area->NextRound();
				SendRound();
				monsterMgr->Reset();
				Wait(3000);
				SetTimer(2, 500, nullptr);
			}
			else if (monsterMgr->extraMon <= 0 && monsterMgr->fieldMon <= 0 && round == 8) {
				victory = 1;
				SendRound();
				Invalidate();
				KillTimer(1);
				KillTimer(3);
			}
			Invalidate();
			break;
			//라운드 별 몬스터소환
		case 2:
			if (monsterMgr->extraMon <= 0) {
				KillTimer(2);
			}
			else {
				monsterMgr->SummMonster(round);
				Invalidate();
			}
			break;
			//타워관련
		case 3:
			area->Tick();
			break;
		}
	}
	
	CDialogEx::OnTimer(nIDEvent);
}


void CRTDDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'q' || nChar == 'Q') {
		state = 1;
	}
	else if (nChar == 'w' || nChar == 'W') {
		state = 2;
	}
	else if (nChar == 'e' || nChar == 'E') {
		state = 3;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRTDDlg::Wait(DWORD dwMillisecond) {
	//타이머에 딜레이를주기위한 코드
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount64();

	while (GetTickCount64() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}


void CRTDDlg::Connect()
{
	//서버접속
	UpdateData(TRUE);
	m_socCom.Create();
	m_socCom.Connect(m_strIP, 5000);
	m_socCom.Init(this->m_hWnd);
	connected = true;
}

void CRTDDlg::SendRound()
{
	//상대방에게 자신의 현재 라운드 혹은 승리여부를 보냄
	UpdateData(TRUE);
	TCHAR pTmp[256];
	CString strTmp;

	if(victory == 1)
		strTmp.Format(L"Victory");
	else
		strTmp.Format(L"%d", round);
	memset(pTmp, '\0', 256);
	wcscat_s(pTmp, strTmp);

	m_socCom.Send(pTmp, 256);

	UpdateData(FALSE);
}


BOOL CRTDDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;
}

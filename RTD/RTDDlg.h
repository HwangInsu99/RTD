
// RTDDlg.h: 헤더 파일
//

#include "SocCom.h"

#pragma once
class MonsterManager;
class Area;


// CRTDDlg 대화 상자
class CRTDDlg : public CDialogEx
{
// 생성입니다.
public:
	CRTDDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CRTDDlg();

	SocCom m_socCom;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RTD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LPARAM OnReceive(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	MonsterManager* monsterMgr;
	Area* area;
	int round;
	int round2;
	int y;
	int state;
	int victory; // default = 0, win = 1, lose = 2
	CImage backG;
	CImage connStr;
	CImage create, upgrade, sell;
	bool connected;
	bool progress;
	CString str;
	CString str2;
	CString m_strIP;

	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void Wait(DWORD dwMillisecond);
	afx_msg void Connect();
	afx_msg void SendRound();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

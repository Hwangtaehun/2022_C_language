
// RandomWalkDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RandomWalk.h"
#include "RandomWalkDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRandomWalkDlg 대화 상자



CRandomWalkDlg::CRandomWalkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRandomWalkDlg::IDD, pParent)
	, m_nXcnt(5)
	, m_nYcnt(5)
	, m_nMoveCnt(0)
	, m_nTime(0)
	, m_nSpeed(100)
	, m_strVisit(_T(""))
	, m_bCheckVisit(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nX = 0;
	m_nY = 0;
	m_nXsize = 0;
	m_nYsize = 0;
	m_nVisitCount = 0;
}

void CRandomWalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COLCNT, m_nXcnt);
	DDV_MinMaxInt(pDX, m_nXcnt, 3, 30);
	DDX_Text(pDX, IDC_ROWCNT, m_nYcnt);
	DDV_MinMaxInt(pDX, m_nYcnt, 3, 30);
	DDX_Text(pDX, IDC_MOVECOUNT, m_nMoveCnt);
	DDX_Text(pDX, IDC_TIME, m_nTime);
	DDX_Text(pDX, IDC_SPEED, m_nSpeed);
	DDX_Text(pDX, IDC_VISIT, m_strVisit);
	DDX_Control(pDX, IDC_BUTTON_START, m_ctrlStartBt);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_ctrlStopBt);
	DDX_Check(pDX, IDC_CHECK_VISIT, m_bCheckVisit);
}

BEGIN_MESSAGE_MAP(CRandomWalkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CRandomWalkDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CRandomWalkDlg::OnClickedButtonStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_VISIT, &CRandomWalkDlg::OnClickedCheckVisit)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CRandomWalkDlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CRandomWalkDlg 메시지 처리기

BOOL CRandomWalkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_pDC = GetDC();
	m_pDC->SetBkMode(TRANSPARENT);
	m_pDC->SetTextColor(RGB(0, 0, 255));

	m_mainDC.CreateCompatibleDC(m_pDC);
	m_backDC.CreateCompatibleDC(m_pDC);
	m_walkerDC.CreateCompatibleDC(m_pDC);
	m_bitMain.LoadBitmap(IDM_BITMAIN);
	m_bitBack.LoadBitmap(IDM_BACK);
	m_bitWalker.LoadBitmap(IDM_WALKER);
	m_mainDC.SelectObject(&m_bitMain);
	m_backDC.SelectObject(&m_bitBack);
	m_walkerDC.SelectObject(&m_bitWalker);

	InitialData();
	m_ctrlStartBt.EnableWindow(!m_bGameStart);
	m_ctrlStopBt.EnableWindow(m_bGameStart);
	srand((unsigned int)time(NULL));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRandomWalkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRandomWalkDlg::OnPaint()
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
		CDialogEx::OnPaint();
		DrawRectAll();
		DisplayAll();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRandomWalkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRandomWalkDlg::OnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate();
	InitialData();
	DrawRectAll();
	m_nX = rand() % m_nXcnt;
	m_nY = rand() % m_nYcnt;
	m_aWalk[m_nY][m_nX]++;
	m_nVisitCount++;
	DrawWalker(m_nX, m_nY);

	m_bGameStart = TRUE;
	m_ctrlStartBt.EnableWindow(!m_bGameStart);
	m_ctrlStopBt.EnableWindow(m_bGameStart);
	SetTimer(0, 1000, NULL);
	SetTimer(1, m_nSpeed, NULL);
}


void CRandomWalkDlg::OnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bGameStart = FALSE;
	m_ctrlStartBt.EnableWindow(!m_bGameStart);
	m_ctrlStopBt.EnableWindow(m_bGameStart);
	KillTimer(0);
	KillTimer(1);
}


void CRandomWalkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0)
	{
		m_nTime++;
		UpdateData(FALSE);
	}
	else if (nIDEvent == 1)
	{
		Walking();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CRandomWalkDlg::OnClickedCheckVisit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	Invalidate();
}


void CRandomWalkDlg::InitialData()
{
	UpdateData(TRUE);
	if (m_nXcnt < 3 || m_nXcnt > MAXCNT)
		m_nXcnt = 5;
	if (m_nYcnt < 3 || m_nYcnt > MAXCNT)
		m_nYcnt = 5;

	m_nXsize = PIC_SIZE / m_nXcnt;
	m_nYsize = PIC_SIZE / m_nYcnt;

	m_mainRect.left = START_X - 1;
	m_mainRect.top = START_Y - 1;
	m_mainRect.right = START_X + m_nXcnt * (m_nXsize + 2) + 1;
	m_mainRect.bottom = START_Y + m_nYcnt * (m_nYsize + 2) + 1;

	m_strVisit = "";
	m_nMoveCnt = 0;
	m_nTime = 0;
	m_nVisitCount = 0;

	memset((void*)m_aWalk, 0, sizeof(m_aWalk));
}


void CRandomWalkDlg::DrawRectAll()
{
	int x, y;
	for (x = 0; x < m_nXcnt; x++)
	{
		for (y = 0; y < m_nYcnt; y++)
		{
			DrawRect(x, y);
		}
	}
}


void CRandomWalkDlg::DrawRect(int nX, int nY)
{
	//m_pDC->Rectangle(START_X + nX * (m_nXsize + 2), START_Y + nY * (m_nYsize + 2), START_X + (nX + 1) * (m_nXsize + 2), START_Y + nY * (m_nYsize + 2));
	m_pDC->Draw3dRect(START_X + nX * (m_nXsize + 2), START_Y + nY * (m_nYsize + 2), m_nXsize, m_nYsize, RGB(128, 128, 128), RGB(255, 255, 255));
}


void CRandomWalkDlg::Walking()
{
	int bx, by;
	do{
		do{
			bx = m_nX;
			bx += rand() % 3 - 1;
		} while (bx < 0 || bx >= m_nXcnt);

		do{
			by = m_nY;
			by += rand() % 3 - 1;
		} while (by < 0 || by >= m_nYcnt);

	} while (bx == m_nX && by == m_nY);

	DrawPicture(m_nX, m_nY);
	m_nX = bx;
	m_nY = by;
	m_aWalk[m_nY][m_nX]++;
	DrawWalker(m_nX, m_nY);
	m_nMoveCnt++;
	if (m_aWalk[m_nY][m_nX] == 1)
	{
		m_nVisitCount++;
		if (m_nVisitCount >= m_nXcnt * m_nYcnt)
		{
			m_bGameStart = FALSE;
			m_ctrlStartBt.EnableWindow(!m_bGameStart);
			m_ctrlStopBt.EnableWindow(m_bGameStart);
			KillTimer(1);
			KillTimer(0);
		}
	}
	m_strVisit.Format(_T("%d/%d"), m_nVisitCount, m_nXcnt * m_nYcnt);
	UpdateData(FALSE);
}


void CRandomWalkDlg::DisplayAll()
{
	int x, y;
	for (x = 0; x < m_nXcnt; x++)
	{
		for (y = 0; y < m_nYcnt; y++)
		{
			DrawPicture(x, y);
		}
	}
	DrawWalker(m_nX, m_nY);
}


void CRandomWalkDlg::DrawPicture(int nX, int nY)
{
	if (m_aWalk[nY][nX] == 0)
		m_pDC->BitBlt(START_X + 1 + (nX * (m_nXsize + 2)), START_Y + 1 + (nY * (m_nYsize + 2)), m_nXsize, m_nYsize, &m_mainDC, (nX * m_nXsize), (nY * m_nYsize), SRCCOPY);
	else
	{
		m_pDC->BitBlt(START_X + 1 + (nX * (m_nXsize + 2)), START_Y + 1 + (nY * (m_nYsize + 2)), m_nXsize, m_nYsize, &m_backDC, (nX * m_nXsize), (nY * m_nYsize), SRCCOPY);
		if (m_bCheckVisit)
		{
			CString str;
			str.Format(_T("%2d"), m_aWalk[nY][nX]);
			m_pDC->TextOut(START_X + nX * (m_nXsize + 2) + 2, START_Y + nY * (m_nYsize + 2) + 2, str);
		}
	}
}


void CRandomWalkDlg::DrawWalker(int nX, int nY)
{
	m_pDC->StretchBlt(START_X + 1 + (nX * (m_nXsize + 2)), START_Y + 1 + (nY * (m_nYsize + 2)), m_nXsize, m_nYsize, &m_walkerDC, 0, 0, 72, 72, SRCCOPY);
}


void CRandomWalkDlg::OnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


// SjTetris1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SjTetris1.h"
#include "SjTetris1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

POINT Pattern[7][16] =
{
	{ { 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 }, { 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 }, { 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 }, { 0, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 } },
	{ { 0, 0 }, { 1, 0 }, { -1, 0 }, { -2, 0 }, { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, -1 }, { 0, 0 }, { 1, 0 }, { -1, 0 }, { -2, 0 }, { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, -1 } },
	{ { 0, 0 }, { -1, 0 }, { 0, -1 }, { 1, -1 }, { 0, 0 }, { 0, 1 }, { -1, 0 }, { -1, -1 }, { 0, 0 }, { -1, 0 }, { 0, -1 }, { 1, -1 }, { 0, 0 }, { 0, 1 }, { -1, 0 }, { -1, -1 } },
	{ { 0, 0 }, { -1, -1 }, { 0, -1 }, { 1, 0 }, { 0, 0 }, { -1, 0 }, { -1, 1 }, { 0, -1 }, { 0, 0 }, { -1, -1 }, { 0, -1 }, { 1, 0 }, { 0, 0 }, { -1, 0 }, { -1, 1 }, { 0, -1 } },
	{ { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 } },
	{ { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 1 }, { -1, 0 }, { -1, -1 }, { 0, 1 } },
	{ { 0, 0 }, { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 }, { 0, 0 }, { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } }
};

POINT nextPattern[7][4] =
{
	{{-1, 0}, {0, 0}, {-1, 1}, {0, 1}},
	{{-1, 1}, {0, 1}, {1, 1}, {-2, 1}},
	{{0, 1}, {-1, 1}, {0, 0}, {1, 0}},
	{{0, 1}, {-1, 0}, {0, 0}, {1, 1}},
	{{-1, 1}, {-1, 0}, {0, 1}, {1, 1}},
	{{1, 1}, {0, 1}, {-1, 1}, {1, 0}},
	{{0, 1}, {-1, 1}, {1, 1}, {0, 0}}
};

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


// CSjTetris1Dlg 대화 상자



CSjTetris1Dlg::CSjTetris1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSjTetris1Dlg::IDD, pParent)
	, m_nMyNo(0)
	, m_nConnectCnt(0)
	, m_strName(_T(""))
	, m_nPortNo(1234)
	, m_strSendData(_T(""))
	, m_strIpAddress(_T(""))
	, m_nGameMode(2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nX = COL_CNT / 2;
	m_nY = 0;
	m_nPattern = 0;
	m_nRot = 0;
	m_bStart = FALSE;
	m_nBitType = 1;
	m_nNextPattern = 0;
	m_nState = STATE_INIT;
	m_nScore = 0;
	m_nStage = 0;
	m_nTime = 0;

	m_mainRect.left = START_X;
	m_mainRect.top = START_Y;
	m_mainRect.right = START_X + BLOCK_SIZE * COL_CNT + 4;
	m_mainRect.bottom = START_Y + BLOCK_SIZE * ROW_CNT + 4;

	m_nextRect.left = START_X + BLOCK_SIZE * COL_CNT + 22;
	m_nextRect.top = START_Y + 30;
	m_nextRect.right = m_nextRect.left + 130;
	m_nextRect.bottom = m_nextRect.top + 80;

	/*m_mainRect2.left = m_nextRect.right + 35;
	m_mainRect2.top = START_Y;
	m_mainRect2.right = m_mainRect2.left + BLOCK_SIZE * COL_CNT / 2 + 4;
	m_mainRect2.bottom = START_Y + BLOCK_SIZE * ROW_CNT / 2 + 4;*/
	m_nState = 0;
	m_nMyNo = 0;
	m_nConnectCnt = 0;
	m_nScore = 0;
	m_nStage = 0;
	m_nTime = 0;
}

void CSjTetris1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_ctrlStartBt);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_ctrlStopBt);
	DDX_Control(pDX, IDC_CONNECT_BT, m_ctrlConnectBt);
	DDX_Control(pDX, IDC_DISCONNECT_BT, m_ctrlDisConnectBt);
	DDX_Control(pDX, IDC_SEND_BT, m_ctrlSendBt);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_PORTNO, m_nPortNo);
	DDX_Text(pDX, IDC_SEND_DATA, m_strSendData);
	DDX_Control(pDX, IDC_SEND_DATA, m_ctrlSendData);
	DDX_Text(pDX, IDC_IP_ADDRESS, m_strIpAddress);
	DDX_Control(pDX, IDC_IP_ADDRESS, m_ctrlIpAddress);
	DDX_Control(pDX, IDC_RADIOSERVER, m_ctrlRadioServer);
	DDX_Control(pDX, IDC_RADIOSINGLE, m_ctrlRadioSingle);
	DDX_Control(pDX, IDC_RADIOCLIENT, m_ctrlRadioClient);
	DDX_Radio(pDX, IDC_RADIOSERVER, m_nGameMode);
}

BEGIN_MESSAGE_MAP(CSjTetris1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CSjTetris1Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CSjTetris1Dlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CSjTetris1Dlg::OnBnClickedButtonExit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONNECT_BT, &CSjTetris1Dlg::OnClickedConnectBt)
	ON_BN_CLICKED(IDC_DISCONNECT_BT, &CSjTetris1Dlg::OnClickedDisconnectBt)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOSERVER, IDC_RADIOSINGLE, OnGameMode)
	ON_MESSAGE(UM_ACCEPT, &CSjTetris1Dlg::OnAcceptMsg)
	ON_MESSAGE(UM_RECEIVE, &CSjTetris1Dlg::OnReceiveMsg)
	ON_MESSAGE(UM_SOCKET_CLOSE, &CSjTetris1Dlg::OnCloseMsg)
END_MESSAGE_MAP()


// CSjTetris1Dlg 메시지 처리기

BOOL CSjTetris1Dlg::OnInitDialog()
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
	MoveWindow(100, 100, m_mainRect.right * 2 + 300, m_mainRect.bottom + 120);
	m_pDC = GetDC();
	m_bmBlock.LoadBitmap(IDB_BLOCK);
	m_BlockDC.CreateCompatibleDC(m_pDC);
	m_BlockDC.SelectObject(&m_bmBlock);
	m_bmBack.LoadBitmap(IDB_BACKGROUND);
	m_BackDC.CreateCompatibleDC(m_pDC);
	m_BackDC.SelectObject(&m_bmBack);
	m_bmBack2.LoadBitmap(IDB_STOP);
	m_BackDC2.CreateCompatibleDC(m_pDC);
	m_BackDC2.SelectObject(&m_bmBack2);
	m_bmNumber.LoadBitmap(IDB_NUMBER);
	m_NumberDC.CreateCompatibleDC(m_pDC);
	m_NumberDC.SelectObject(&m_bmNumber);

	char hostName[32];
	struct in_addr myIpAddr;
	HOSTENT* pHostEnt = NULL;
	gethostname(hostName, sizeof(hostName));
	pHostEnt = gethostbyname(hostName);
	myIpAddr.S_un.S_addr = *((u_long*)(pHostEnt->h_addr_list[0]));
	m_strIpAddress = inet_ntoa(myIpAddr);
	UpdateData(FALSE);
	m_ctrlConnectBt.EnableWindow(TRUE);
	m_ctrlDisConnectBt.EnableWindow(FALSE);
	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);
	//m_ctrlSendBt.EnableWindow(FALSE);

	srand((unsigned)time(NULL));
	memset((void*)m_Table, -1, sizeof(m_Table));
	//memset((void*)m_Table2, -1, sizeof(m_Table2));
	InitGuestData();
	OnGameMode(NULL);
	//DisplayMsg(_T("6인용 NetWork Tetris 입니다."));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSjTetris1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSjTetris1Dlg::OnPaint()
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
		DrawScr();
		DrawScr2();
		DisplayAllGuest();
		DisplayMsg(_T(""));
		NextBlock(FALSE);
		if (m_nState == STATE_GAME_START)
		{
			NextBlock(TRUE);
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSjTetris1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSjTetris1Dlg::DrawScr()
{
	int i, j, temp, startX, startY;
	m_pDC->Draw3dRect(HOST_X, HOST_Y, HOST_XSIZE + 4, HOST_YSIZE + 3, RGB(128, 128, 128), RGB(255, 255, 255));
	m_pDC->SetTextColor(RGB(0, 0, 255));
	m_pDC->SetBkColor(RGB(190, 190, 190));
	for (i = 0; i < USER_CNT; i++)
	{
		if (i<USER_CNT/2)
		{
			startX = GUEST_X + i * (GUEST_XSIZE + 10) + 4;
			startY = GUEST_Y;
		}
		else
		{
			startX = GUEST_X + ((i - 3) * (GUEST_XSIZE + 10)) + 4;
			startY = GUEST_Y + GUEST_YSIZE + 60;
		}
		m_pDC->Draw3dRect(startX, startY, GUEST_XSIZE + 4, GUEST_YSIZE + 4, RGB(128, 128, 128), RGB(255, 255, 255));
		m_pDC->Draw3dRect(startX, startY + GUEST_YSIZE + 8, GUEST_XSIZE + 4, 46, RGB(128, 128, 128), RGB(255, 255, 255));
		m_pDC->TextOut(startX + 8, startY + GUEST_YSIZE + 10, _T("                  "));
		m_pDC->TextOut(startX + 8, startY + GUEST_YSIZE + 10, m_Guest[i].strName);
		temp = m_Guest[i].nScore;
		for (j = 9; j >= 0; j--)
		{
			if (temp > 0)
			{
				m_pDC->BitBlt(startX + 8 + j * 13, startY + GUEST_YSIZE + 28, 13, 23, &m_NumberDC, 0, (temp % 10) * 23, SRCCOPY);
				temp /= 10;
			}
			else
			{
				m_pDC->BitBlt(startX + 8 + j * 13, startY + GUEST_YSIZE + 28, 13, 23, &m_NumberDC, 0, 11 * 23, SRCCOPY);
				temp /= 10;
			}
		}
	}
	if (m_nState == STATE_GAME_START)
		NextBlock(TRUE);
	else
		NextBlock(FALSE);

	//int row, col;
	//m_pDC->Rectangle(m_mainRect);
	//m_pDC->Rectangle(m_nextRect);
	//for (row = 0; row < ROW_CNT; row++)
	//{
	//	for (col = 0; col < COL_CNT; col++)
	//	{
	//		if (m_Table[0][row][col] == -1)
	//		{
	//			m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, &m_BackDC, col * BLOCK_SIZE, row *BLOCK_SIZE, SRCCOPY);
	//		}
	//		else
	//		{
	//			m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC,
	//				m_Table[0][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
	//		}
	//	}
	//}
	//DrawScr2();
	////m_nScore += 10;
	//NextBlock(m_bStart);
}


void CSjTetris1Dlg::InitialGame()
{
	memset((void *)m_Table, -1, sizeof(m_Table));
	DrawScr();
	DrawScr2();
	DisplayAllGuest();
	NextBlock(FALSE);

	m_nPattern = rand() % 7;
	m_nRot = 0;
	m_nY = 1;
	m_nX = COL_CNT / 2;
	m_bStart = TRUE;
	m_nNextPattern = rand() % 7;

	DrawBlock(TRUE);
	NextBlock(TRUE);
	SetTimer(1, 500, NULL);

	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);
	m_ctrlRadioServer.EnableWindow(FALSE);
	m_ctrlRadioClient.EnableWindow(FALSE);
	m_ctrlRadioSingle.EnableWindow(FALSE);
	m_ctrlSendData.SetFocus();
}


void CSjTetris1Dlg::DrawBlock(bool bFlag)
{
	for (int i = 0; i < 4; i++)
	{
		if (bFlag)
		{
			m_pDC->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, m_nPattern * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
		else
		{
			m_pDC->BitBlt(START_X + 2 + (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE,
				START_Y + 2 + (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BackDC, (m_nX + Pattern[m_nPattern][i + m_nRot * 4].x) * BLOCK_SIZE, (m_nY + Pattern[m_nPattern][i + m_nRot * 4].y) * BLOCK_SIZE, SRCCOPY);
		}
	}
}


BOOL CSjTetris1Dlg::BlockDown()
{
	if (!IsAround(m_nX, m_nY + 1))
	{
		SetTable();
		return FALSE;
	}
	DrawBlock(FALSE);
	m_nY++;
	DrawBlock(TRUE);
	m_Guest[0].nScore += rand() % 5 + 1;
	DrawScr();
	return TRUE;
}


BOOL CSjTetris1Dlg::IsAround(int nX, int nY)
{
	int i, row, col;
	for (i = 0; i < 4; i++)
	{
		col = nX + Pattern[m_nPattern][i + m_nRot * 4].x;
		row = nY + Pattern[m_nPattern][i + m_nRot * 4].y;
		if (col < 0 || col > COL_CNT - 1 || row < 1 || row > ROW_CNT - 1)
		{
			return FALSE;
		}
		if (m_Table[0][row][col] != -1)
		{
			return FALSE;
		}
	}
	return TRUE;
}


void CSjTetris1Dlg::SetTable()
{
	int i, row, col, sw;
	for (i = 0; i < 4; i++)
	{
		m_Table[0][m_nY + Pattern[m_nPattern][i + m_nRot * 4].y][m_nX + Pattern[m_nPattern][i + m_nRot * 4].x] = m_nPattern;
	}
	for (row = ROW_CNT - 1; row >= 0; row--)
	{
		sw = 0;
		for (col = 0; col < COL_CNT; col++)
		{
			if (m_Table[0][row][col] == -1)
				sw = -1;
		}
		if (sw == 0)
		{
			for (i = row; i > 0; i--)
			{
				for (col = 0; col < COL_CNT; col++)
				{
					m_Table[0][i][col] = m_Table[0][i - 1][col];
				}
			}
			for (col = 0; col < COL_CNT; col++)
			{
				m_pDC->BitBlt(START_X + 2 + col * BLOCK_SIZE, START_Y + 2 + row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, &m_BackDC, 0, 0, SRCCOPY);
				m_Guest[0].nScore += 10;
				DrawScr();
				Sleep(20);
			}
			//UpdateData(TRUE);
			//m_nScore += 10;
			//UpdateData(FALSE);
			DrawScr2();
			Sleep(100);
			row++;
		}
	}
	//for (int i = 1; i < 6; i++)
	//{
	//	for (row = 0; row < ROW_CNT; row++)
	//	{
	//		for (col = 0; col < COL_CNT; col++)
	//		{
	//			m_Table[i][row][col] = m_Table[0][row][col];
	//		}
	//	}
	//}
	/*for (int i = 1; i < 6; i++)
	{
		memcpy((void*)m_Table[i], (void*)m_Table[0], COL_CNT * ROW_CNT);
	}
	DrawScr2();*/
	/*for (int i = 1; i < USER_CNT; i++)
	{
		memcpy((void*)m_Table[i], (void*)m_Table[0], COL_CNT * ROW_CNT);
	}
	DisplayAllGuest();*/
	if (m_nGameMode == 0)
	{
		if (m_nState == STATE_GAME_START)
		{
			memcpy((void*)m_sendData.Buf, (void*)m_Table[0], COL_CNT * ROW_CNT);
			m_sendData.nMyNo = 0;
			m_sendData.nScore = m_nScore;
			m_sendData.nFlag = 'T';
			for (int i = 1; i < USER_CNT; i++)
			{
				if (m_Guest[i].pClient->Send((void*)&m_sendData, SEND_SIZE) == -1)
					MessageBox(_T("전송실패"));
			}
		}
	}
	else if (m_nGameMode == 1)
	{
		if (m_nState == STATE_GAME_START)
		{
			memcpy((void*)m_sendData.Buf, (void*)m_Table[0], COL_CNT * ROW_CNT);
			m_sendData.nMyNo = m_nMyNo;
			m_sendData.nScore = m_nScore;
			m_sendData.nFlag = 'T';
			if (m_Client.Send((void*)&m_sendData, SEND_SIZE) == -1)
				MessageBox(_T("전송실패"));
		}
	}
	DisplayMsg(_T(""));
	m_nX = COL_CNT / 2;
	m_nY = 1;
	m_nPattern = m_nNextPattern;
	NextBlock(FALSE);
	m_nNextPattern = rand() % 7;
	NextBlock(TRUE);
	//m_nPattern = rand() % 7;
	m_nRot = 1;
	if (!IsAround(m_nX, m_nY + 1))
	{
		KillTimer(1);
		MessageBox(_T("으악"));
		m_ctrlStartBt.EnableWindow(TRUE);
		m_ctrlStopBt.EnableWindow(FALSE);
		m_nState = STATE_GAME_DIE;
		m_sendData.nFlag = 'F';
		if (m_nGameMode == 0)
		{
			for (int i = 1; i < USER_CNT - 1; i++)
			{
				sprintf_s(m_sendData.Buf, BUFFER_SIZE, "관리자님이  GameOver 되었습니다.");
				if (m_Guest[i].cFlag == 'C')
				{
					if (m_Guest[i].pClient->Send((void*)&m_sendData, SEND_SIZE) == -1)
						MessageBox(_T("전송실패"));
				}
			}
		}
		DrawScr();
		return;
	}
}


void CSjTetris1Dlg::RolateBlock(bool bFlag)
{
	int nRot = m_nRot;
	DrawBlock(FALSE);
	if (++m_nRot > 3)
		m_nRot = 0;
	if (!IsAround(m_nX, m_nY))
		m_nRot = nRot;
	DrawBlock(TRUE);
}


void CSjTetris1Dlg::MoveDown()
{
	while (BlockDown())
	{
		Sleep(30);
	}
}


void CSjTetris1Dlg::MoveRight()
{
	if (!IsAround(m_nX + 1, m_nY))
		return;
	DrawBlock(FALSE);
	m_nX++;
	DrawBlock(TRUE);
}


void CSjTetris1Dlg::MoveLeft()
{
	if (!IsAround(m_nX - 1, m_nY))
		return;
	DrawBlock(FALSE);
	m_nX--;
	DrawBlock(TRUE);
}


void CSjTetris1Dlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InitialGame();
	m_ctrlStartBt.EnableWindow(FALSE);
	m_ctrlStopBt.EnableWindow(TRUE);
	m_ctrlStopBt.SetFocus();
	DisplayMsg(_T("Game Start"));
	if (m_nState == STATE_CONNECT)
	{
		m_sendData.nFlag = 'S';
		if (m_Client.Send((void*)&m_sendData, SEND_SIZE) == -1)
			MessageBox(_T("전송실패"));
	}
	m_nState = STATE_GAME_START;
}


void CSjTetris1Dlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nState = STATE_INIT;
	KillTimer(1);
	m_ctrlStartBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(FALSE);
	if (m_nGameMode == 2)
	{
		m_ctrlRadioServer.EnableWindow(TRUE);
		m_ctrlRadioClient.EnableWindow(TRUE);
		m_ctrlRadioSingle.EnableWindow(TRUE);
	}
	DisplayMsg(_T("Game Stop"));
}


void CSjTetris1Dlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CSjTetris1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	BlockDown();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CSjTetris1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && m_nState >= STATE_CONNECT)
	{
		OnClickedSendBt();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && m_nState == STATE_GAME_START)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			MoveLeft();
			return TRUE;
		case VK_RIGHT:
			MoveRight();
			return TRUE;
		case VK_DOWN:
			MoveDown();
			return TRUE;
		case VK_UP:
			RolateBlock(FALSE);
			return TRUE;
		case VK_SPACE:
		case VK_RETURN:
			MoveDown();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSjTetris1Dlg::NextBlock(bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int i, x = 50, y = 10;
	if (m_nNextPattern == 0)
		x = 65;
	else if (m_nNextPattern == 1)
		x = 65, y = 0;

	if (bFlag)
	{
		for (i = 0; i < 4; i++)
		{
			m_pDC->BitBlt(m_nextRect.left + x + (nextPattern[m_nNextPattern][i].x) * BLOCK_SIZE,
				m_nextRect.top + y + (nextPattern[m_nNextPattern][i].y) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, m_nNextPattern * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
	}
	else
	{
		m_pDC->Rectangle(m_nextRect);
	}
}


void CSjTetris1Dlg::DrawScr2()
{
	// TODO: 여기에 구현 코드 추가.
	int row, col;
	CDC* pDC;
	if (m_nState == STATE_GAME_DIE)
		pDC = &m_BackDC2;
	else
		pDC = &m_BackDC;
	
	for (row = 0; row < ROW_CNT; row++)
	{
		for (col = 0; col < COL_CNT; col++)
		{
			if (m_Table[0][row][col] == -1)
			{
				m_pDC->BitBlt(HOST_X + 2 + col * BLOCK_SIZE, HOST_Y + row * BLOCK_SIZE + 2, BLOCK_SIZE, BLOCK_SIZE, pDC, col * BLOCK_SIZE, row * BLOCK_SIZE, SRCCOPY);
			}
			else
			{
				m_pDC->BitBlt(HOST_X + 2 + col * BLOCK_SIZE, HOST_Y + row * BLOCK_SIZE + 2, BLOCK_SIZE, BLOCK_SIZE, &m_BlockDC, m_Table[0][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
			}
		}
	}

	//CDC* pDC = GetDC();
	//int x = 0, y = 0;
	//for (int i = 1; i < 6; i++)
	//{
	//	if (i < 3)
	//	{
	//		x = (i - 1) * (BLOCK_SIZE * COL_CNT / 2 + 14);
	//		y = 0;
	//	}
	//	else
	//	{
	//		x = (i - 3) * (BLOCK_SIZE * COL_CNT / 2 + 14) - 175;
	//		y = BLOCK_SIZE * ROW_CNT / 2 + 54;
	//	}
	//	//pDC->Rectangle(m_mainRect2.left + x, m_mainRect2.top + y, m_mainRect2.right + x, m_mainRect2.bottom + y);
	//	DrawScr3(i, x, y);
	//}

	//int x = BLOCK_SIZE * COL_CNT / 2; // 2 * x = BLOCK_SIZE * ROW_CNT / 2
	//CDC* pDC = GetDC();

	//for (int i = 0; i < 5; i++)
	//{
	//	if (i < 2)
	//	{
	//		pDC->Rectangle((i + 2) * BLOCK_SIZE * COL_CNT / 2 + 195 + (i * 14), 10, (i + 3) * BLOCK_SIZE * COL_CNT / 2 + 199 + (i * 14), BLOCK_SIZE * ROW_CNT / 2 + 14);
	//	}

	//	else
	//	{
	//		pDC->Rectangle(i * x + 20 + (i - 2) * 14, 2 * x + 64, (i + 1) * x + 24 + (i - 2) * 14, 4 * x + 68);
	//	}
	//}
	//DrawScr3();

	/*int row, col;
	for (int i = 1; i < 6; i++)
	{
		for (row = 0; row < ROW_CNT; row++)
		{
			for (col = 0; col < COL_CNT; col++)
			{
				if (m_Table[i][row][col] == -1)
				{
					m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2, m_mainRect2.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
						col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect3.left + 2 + col * BLOCK_SIZE / 2, m_mainRect3.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
						col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect4.left + 2 + col * BLOCK_SIZE / 2, m_mainRect4.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
						col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect5.left + 2 + col * BLOCK_SIZE / 2, m_mainRect5.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
						col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect6.left + 2 + col * BLOCK_SIZE / 2, m_mainRect6.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
						col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				}
				else
				{
					m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2, m_mainRect2.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
						m_Table[1][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect3.left + 2 + col * BLOCK_SIZE / 2, m_mainRect3.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
						m_Table[2][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect4.left + 2 + col * BLOCK_SIZE / 2, m_mainRect4.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
						m_Table[3][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect5.left + 2 + col * BLOCK_SIZE / 2, m_mainRect5.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
						m_Table[4][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					m_pDC->StretchBlt(m_mainRect6.left + 2 + col * BLOCK_SIZE / 2, m_mainRect6.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
						m_Table[5][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				}
			}
		}
	}*/
	/*for (row = 0; row < ROW_CNT; row++)
	{
		for (col = 0; col < COL_CNT; col++)
		{
			if (m_Table2[row][col] == -1)
			{
				m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2, m_mainRect2.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
					col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect3.left + 2 + col * BLOCK_SIZE / 2, m_mainRect3.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
					col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect4.left + 2 + col * BLOCK_SIZE / 2, m_mainRect4.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
					col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect5.left + 2 + col * BLOCK_SIZE / 2, m_mainRect5.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
					col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect6.left + 2 + col * BLOCK_SIZE / 2, m_mainRect6.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
					col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
			}
			else
			{
				m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2, m_mainRect2.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
					m_Table2[row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect3.left + 2 + col * BLOCK_SIZE / 2, m_mainRect3.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
					m_Table2[row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect4.left + 2 + col * BLOCK_SIZE / 2, m_mainRect4.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
					m_Table2[row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect5.left + 2 + col * BLOCK_SIZE / 2, m_mainRect5.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
					m_Table2[row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
				m_pDC->StretchBlt(m_mainRect6.left + 2 + col * BLOCK_SIZE / 2, m_mainRect6.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
					m_Table2[row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
			}
		}
	}*/
}

void CSjTetris1Dlg::DrawScr3(void* pt, int nClientNo, bool bFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int row = GUEST_Y, col = GUEST_X, startX, startY;
	char(*GuestTable)[COL_CNT] = (char(*)[COL_CNT])pt;
	CDC* memDC = (bFlag) ? &m_BackDC : &m_BackDC2;
	if (nClientNo < USER_CNT /2)
	{
		startX = GUEST_X + nClientNo * (GUEST_XSIZE + 10) + 6;
		startY = GUEST_Y + 2;
	}
	else
	{
		startX = GUEST_X + ((nClientNo - 3) * (GUEST_XSIZE + 10)) + 6;
		startY = GUEST_Y + GUEST_YSIZE + 60;
	}
	for (row = 0; row < ROW_CNT; row++)
	{
		for (col = 0; col < COL_CNT; col++)
		{
			if (GuestTable[row][col] == -1)
				m_pDC->StretchBlt(startX + col * 14, startY + row * 14, 14, 14, memDC, col * 24, row * 24, 24, 24, SRCCOPY);
			else
				m_pDC->StretchBlt(startX + col * 14, startY + row * 14, 14, 14, &m_BlockDC, GuestTable[row][col] * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, m_nBitType * BLOCK_SIZE, SRCCOPY);
		}
	}

	//int row, col;
	//for (row = 0; row < ROW_CNT; row++)
	//{
	//	for (col = 0; col < COL_CNT; col++)
	//	{
	//		if (m_Table[i][row][col] == -1)
	//		{
	//			//m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2 + x, m_mainRect2.top + 2 + row * BLOCK_SIZE / 2 + y,
	//				BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
	//				col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
	//		}
	//		else
	//		{
	//			//m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2 + x, m_mainRect2.top + 2 + row * BLOCK_SIZE / 2 + y,
	//				BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
	//				m_Table[i][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);

	//		}
	//	}
	//}

	/*int row, col;
	m_pDC->Rectangle(m_mainRect2);
	for (int i = 1; i < 6; i++)
	{
		if (i < 3)
		{
			for (row = 0; row < ROW_CNT; row++)
			{
				for (col = 0; col < COL_CNT; col++)
				{
					if (m_Table[i][row][col] == -1)
					{
						m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2 + (i - 1) * (BLOCK_SIZE * COL_CNT / 2 + 14), m_mainRect2.top + 2 + row * BLOCK_SIZE / 2, 
							BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
							col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					}
					else
					{
						m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2 + (i - 1) * (BLOCK_SIZE * COL_CNT / 2 + 14), m_mainRect2.top + 2 + row * BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
							m_Table[i][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);

					}
				}
			}
		}
		else
		{
			for (row = 0; row < ROW_CNT; row++)
			{
				for (col = 0; col < COL_CNT; col++)
				{
					if (m_Table[i][row][col] == -1)
					{
						m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2 - 175 + (i - 3) * (BLOCK_SIZE * COL_CNT / 2 + 14), m_mainRect2.top + 2 + row * BLOCK_SIZE / 2 + BLOCK_SIZE * ROW_CNT / 2 + 54,
							BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BackDC,
							col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);
					}
					else
					{
						m_pDC->StretchBlt(m_mainRect2.left + 2 + col * BLOCK_SIZE / 2 - 175 + (i - 3) * (BLOCK_SIZE * COL_CNT / 2 + 14), m_mainRect2.top + 2 + row * BLOCK_SIZE / 2 + BLOCK_SIZE * ROW_CNT / 2 + 54,
							BLOCK_SIZE / 2, BLOCK_SIZE / 2, &m_BlockDC,
							m_Table[i][row][col] * BLOCK_SIZE, m_nBitType * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, SRCCOPY);

					}
				}
			}
		}*/
	//}
}


void CSjTetris1Dlg::OnClickedConnectBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 0; i < USER_CNT; i++)
	{
		m_Guest[i].cFlag = 'I';
		m_Guest[i].nScore = 0;
		m_Guest[i].pClient = 0;
		m_Guest[i].strName = "";
	}

	if (m_nGameMode == 0)
	{
		m_Guest[0].strName = "관리자";
		UpdateData(TRUE);
		m_ctrlConnectBt.EnableWindow(FALSE);
		m_ctrlConnectBt.SetWindowText(_T("Server 실행중"));
		if (!m_Server.ServerStart(this, m_nPortNo))
		{
			MessageBox(_T("Server Socket 문제 발생"));
			m_ctrlConnectBt.EnableWindow(TRUE);
			m_ctrlConnectBt.SetWindowText(_T("Server Start"));
			return;
		}
		m_ctrlSendBt.EnableWindow(FALSE);
		m_ctrlDisConnectBt.EnableWindow(TRUE);
		DisplayMsg(_T("Server 실행 후 대기 중입니다."));
		m_nState = STATE_WAIT;
		UpdateData(FALSE);
		m_ctrlSendData.SetFocus();
	}
	else if(m_nGameMode == 1)
	{
		UpdateData(TRUE);
		if (m_strName.IsEmpty())
		{
			MessageBox(_T("대화명을 입력하세요."));
			return;
		}
		m_Client.Create();
		m_Client.SetMainWindow(this);
		if (!m_Client.Connect(m_strIpAddress, m_nPortNo))
		{
			MessageBox(_T("Sever에 접속하지 못했네유 !!"));
			m_Client.Close();
			return;
		}
		/*CStringA s2(m_strName);
		const char* c = s2;*/
		/*sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, "%s입니다.", CT2A(m_strName));
		m_sendData.nFlag = 'C';
		if (m_Client.Send((void*)&m_sendData, SEND_SIZE) == -1)
			MessageBox(_T("전송실패"));
			*/
		m_nState = STATE_CONNECT;
		m_ctrlConnectBt.EnableWindow(FALSE);
		m_ctrlConnectBt.SetWindowText(_T("Server연결중"));
		m_ctrlSendBt.EnableWindow(TRUE);
		m_ctrlDisConnectBt.EnableWindow(TRUE);
		m_ctrlSendData.SetFocus();
	}
}


void CSjTetris1Dlg::OnClickedDisconnectBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nGameMode == 0)
	{
		if (AfxMessageBox(_T("Sever를 종료합니다.!!"), MB_YESNO) == IDYES)
		{
			m_ctrlDisConnectBt.EnableWindow(FALSE);
			m_ctrlConnectBt.EnableWindow(TRUE);
			m_ctrlConnectBt.SetWindowText(_T("Server Start"));
			m_Server.ShutDown();
			m_Server.Close();
			for (int i = 1; i < USER_CNT - 1; i++)
			{
				if (m_Guest[i].pClient->m_bConnect)
					m_Guest[i].pClient->Close();
			}
			DisplayMsg(_T("Server를 종료합니다."));
			m_nState = STATE_INIT;
			UpdateData(FALSE);
		}
	}
	else if (m_nGameMode == 1)
	{
		if (AfxMessageBox(_T("Sever와의 연결을 끊을까유 !!"), MB_YESNO) == IDYES)
		{
			m_ctrlConnectBt.EnableWindow(TRUE);
			m_ctrlConnectBt.SetWindowText(_T("Server연결"));
			m_ctrlSendBt.EnableWindow(FALSE);
			m_ctrlDisConnectBt.EnableWindow(FALSE);
			m_nState = STATE_INIT;
			m_Client.Close();
		}
	}
}


void CSjTetris1Dlg::OnClickedSendBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMsg = _T("");
	UpdateData(TRUE);
	if (!m_strSendData.IsEmpty())
	{
		strMsg += m_Guest[m_nMyNo].strName;
		strMsg += m_strSendData;
		CStringA s2(strMsg);
		const char* c = s2;
		sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, "%s", c);
		m_sendData.nFlag = 'C';
		DisplayMsg(strMsg);
		if (m_nGameMode == 0)
		{
			int i;
			for (i = 1; i < USER_CNT; i++)
			{
				if (m_Guest[i].cFlag == 'C')
				{
					if (m_Guest[i].pClient->Send((void*)&m_sendData, SEND_SIZE) == -1)
						MessageBox(_T("전송실패"));
				}
			}
		}
		else if (m_nGameMode == 1)
		{
			if (m_Client.Send((void*)&m_sendData, SEND_SIZE) == -1)
				MessageBox(_T("전송실패"));
		}
		m_strSendData = "";
		UpdateData(FALSE);
	}
	m_ctrlSendData.SetFocus();
}


LRESULT CSjTetris1Dlg::OnAcceptMsg(WPARAM wParam, LPARAM IParam)
{
	CString buf2 = _T("");
	char buf[BUFFER_SIZE] = "";
	//m_nMyNo++;
	CSjClientSocket *pClient = new CSjClientSocket();
	pClient->SetMainWindow(this);
	//m_Guest[0].pClient = pClient;
	int n;

	if (m_nGameMode != 0)
		return 0;

	if (!m_Server.Accept(*pClient))
	{
		MessageBox(_T("Client 연결 실패"));
		return -1;
	}
	if (m_nState == STATE_GAME_START)
	{
		sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, "게임이 진행 중입니다.");
		pClient->Send((void*)&m_sendData, SEND_SIZE);
		pClient->Close();
		delete pClient;
		return 0;
	}
	for (n = 1; n < USER_CNT; n++)
	{
		if (m_Guest[n].cFlag == 'I')
			break;
	}
	if (n < USER_CNT)
	{
		m_Guest[n].pClient = pClient;
		m_Guest[n].pClient->m_bConnect = TRUE;
		m_Guest[n].strName = m_sendData.Buf;
		m_Guest[n].cFlag = m_sendData.nFlag;
		sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, "6인용 Tetris Server입니다");
		m_sendData.nFlag = 'B';
		m_sendData.nMyNo = n;
		
		if (pClient->Send((void*)&m_sendData, SEND_SIZE) == -1)
		{
			MessageBox(_T("환영 Message 전송 실패"));
			m_Guest[n].cFlag = 'I';
			m_Guest[n].pClient->m_bConnect = FALSE;
			pClient->Close();
			delete pClient;
			return -1;
		}
		//MessageBox(_T("ddew"));
		m_nState = STATE_CONNECT;
		m_ctrlSendBt.EnableWindow(TRUE);
		sprintf_s(buf, "%s님이 접속했습니다.\r\n", m_Guest[n].strName);
		pClient->Send(buf, BUFFER_SIZE);
		buf2 = buf;
		DisplayMsg(buf2);
		//pClient->Close();
		delete pClient;
	}
	else
	{
		m_Guest[n].pClient->m_bConnect = FALSE;
		sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, "접속 인원 초과 입니다.");
		m_sendData.nFlag = 'C';
		pClient->Send((void*)&m_sendData, SEND_SIZE);
		pClient->Close();
		delete pClient;
	}
	return LRESULT();
}


LRESULT CSjTetris1Dlg::OnReceiveMsg(WPARAM wParam, LPARAM IParam)
{
	CString strMsg = _T("");
	int i = 0;
	MessageBox(_T("OnReceiveMsg"));
	CSjClientSocket *pClient = (CSjClientSocket*)IParam;
	pClient->Receive((void*)&m_sendData, SEND_SIZE);
	//MessageBox(CA2T(m_sendData.Buf));
	if (m_nGameMode == 0)
	{
	/*	for (i = 1; i < USER_CNT; i++)
		{
			if (m_Guest[i].cFlag == 'C')
			{
				CSjClientSocket *pClient = m_Guest[i].pClient;
				pClient->Receive((void*)&m_sendData, SEND_SIZE);
				switch (m_sendData.nFlag)
				{
				case 'C':
					strMsg += m_Guest[i].strName;
					strMsg += m_sendData.Buf;
					DisplayMsg(strMsg);
					sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, (CT2A)strMsg);
					break;
				case 'T':
					memcpy(pClient, (void*)&m_sendData.Buf, COL_CNT * ROW_CNT);
					m_Guest[i].nScore = m_sendData.nScore;
					DisplayAllGuest();
					DrawScr();
					DisplayMsg(_T(""));
					break;
				case 'F':
					strMsg += m_Guest[i].strName;
					strMsg += "님이 GameOver되었습니다.";
					m_sendData.nScore = 0;
					DisplayMsg(strMsg);
					sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, (CT2A)strMsg);
					break;*/
				/*case 'X':
					strMsg += m_Guest[i].strName;
					strMsg += "님이 게임을 퇴장했습니다.";
					m_sendData.nScore = 0;
					DisplayMsg(strMsg);
					sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, (CT2A)strMsg);
					break;*/
			/*	}
			}
		}
		for (i = 1; i < USER_CNT; i++)
		{
			if (m_Guest[i].cFlag == 'C')
			{
				if (m_Guest[i].pClient->Send((void*)&m_sendData, SEND_SIZE) == -1)
					MessageBox(_T("전송실패"));
			}
		}*/
	}
	else if (m_nGameMode == 1)
	{
		//CString strMsg = _T("");
		//m_Client.Receive((void*)&m_sendData, SEND_SIZE);
		MessageBox(CA2T(m_sendData.Buf));
/*		switch (m_sendData.nFlag)
		{
		case 'B':
			m_nMyNo = m_sendData.nMyNo;
			strMsg += m_sendData.Buf;
			DisplayMsg(strMsg);
			m_Guest[m_nMyNo].pClient = &m_Client;
			break;
		case 'C':
			strMsg += m_sendData.Buf;
			DisplayMsg(strMsg);
			break;
		case 'T':
			if (m_sendData.nMyNo != 0)
			{
				CSjClientSocket *pClient = m_Guest[m_sendData.nMyNo].pClient;
				memcpy(pClient, (void*)&m_sendData.Buf, COL_CNT * ROW_CNT);
				m_Guest[m_sendData.nMyNo].nScore = m_sendData.nScore;
				DisplayAllGuest();
				DrawScr();
				DisplayMsg(_T(""));
				DrawScr();
			}
			else if (m_sendData.nMyNo == 0)
			{
				CSjClientSocket *pClient = m_Guest[m_nMyNo].pClient;
				memcpy(pClient, (void*)&m_sendData.Buf, COL_CNT * ROW_CNT);
				m_Guest[m_nMyNo].nScore = m_sendData.nScore;
				DisplayAllGuest();
				DrawScr();
				DisplayMsg(_T(""));
				DrawScr();
			}
			break;
		case 'S':
			OnBnClickedButtonStart();
			break;
		case 'F':
			if (m_sendData.nMyNo != 0)
			{
				m_Guest[m_sendData.nMyNo].nScore = 0;
				DrawScr();
				strMsg = m_sendData.Buf;
				DisplayMsg(strMsg);
			}
			else
			{
				m_Guest[m_nMyNo].nScore = 0;
				DrawScr();
				strMsg = m_sendData.Buf;
				DisplayMsg(strMsg);
			}
			break;
		case 'X':
			m_Guest[m_sendData.nMyNo].cFlag = 'I';
			strMsg = m_sendData.Buf;
			DisplayMsg(strMsg);
			DisplayAllGuest();
			break;
		}*/
	}
	return LRESULT();
}


LRESULT CSjTetris1Dlg::OnCloseMsg(WPARAM wParam, LPARAM IParam)
{
	/*if (m_nGameMode == 0)
	{
		int No = 0;
		CString strMsg = _T("");
		CSjClientSocket* pClient = (CSjClientSocket *)IParam;
		
		pClient->m_bConnect = FALSE;
		strMsg += pClient->m_strName;
		strMsg += _T("님이 퇴장했습니다.");
		DisplayMsg(strMsg);
		pClient->Close();
		delete pClient;
		
		for (int i = 1; i < USER_CNT; i++)
		{
			if (m_Guest[i].pClient->m_bConnect == false)
			{
				m_Guest[i].cFlag = 'I';
				No = i;
			}
			if (m_Guest[i].cFlag == 'C')
			{
				m_sendData.nMyNo = No;
				m_sendData.nScore = 0;
				m_sendData.nFlag = 'X';
				sprintf_s(m_sendData.Buf, BUFFER_SIZE - 1, (CT2A)strMsg);
				if (m_Guest[i].pClient->Send((void*)&m_sendData, SEND_SIZE) == -1)
					MessageBox(_T("전송실패"));
			}
		}
	}*/
	return LRESULT();
}


void CSjTetris1Dlg::DisplayMsg(CString strMsg)
{
	int i, r = 0, g = 255, b = 0;
	m_pDC->SetBkMode(TRANSPARENT);
	DrawScr();
	DrawScr2();
	if (!strMsg.IsEmpty())
	{
		for (i = MSG_CNT - 1; i > 0; i--)
		{
			m_arrMsg[i] = m_arrMsg[i - 1];
		}
		m_arrMsg[0] = strMsg;
	}
	for (i = 0; i < MSG_CNT; i++)
	{
		m_pDC->SetTextColor(RGB(r, g, b));
		g -= 20;
		m_pDC->TextOut(HOST_X + 5, HOST_Y + i * 20, m_arrMsg[i]);
	}
}


void CSjTetris1Dlg::InitGuestData()
{
	for (int i = 1; i < USER_CNT; i++)
	{
		m_Guest[i].strName = " 접 속 대 기 ";
		m_Guest[i].nScore = 0;
		m_Guest[i].cFlag = 'I';
		m_Guest[i].pClient = NULL;
	}
	m_Guest[0].strName = " 점 수   ";
	m_Guest[0].nScore = 0;
	m_nConnectCnt = 0;
}


void CSjTetris1Dlg::DisplayAllGuest()
{
	// TODO: 여기에 구현 코드 추가.
	int i;
	for (i = 1; i < USER_CNT; i++)
	{
		DrawScr3((void*)m_Table[i], i, TRUE);
		/*if (m_Guest[i].cFlag == 'C')
			DrawScr3((void*)m_Table[i], i, TRUE);
		else
			DrawScr3((void*)m_Table[i], i, FALSE);*/
	}
}


void CSjTetris1Dlg::OnGameMode(UINT nID)
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);
	switch (m_nGameMode)
	{
	case 0:
		m_nMyNo = 0;
		m_ctrlConnectBt.EnableWindow(TRUE);
		m_ctrlDisConnectBt.EnableWindow(FALSE);
		/*m_ctrlStartBt.EnableWindow(FALSE);
		m_ctrlStopBt.EnableWindow(FALSE);*/
		m_strName= _T("관리자");
		UpdateData(FALSE);
		break;
	case 1:
		m_ctrlConnectBt.EnableWindow(TRUE);
		m_ctrlDisConnectBt.EnableWindow(FALSE);
		/*m_ctrlStartBt.EnableWindow(FALSE);
		m_ctrlStopBt.EnableWindow(FALSE);*/
		m_strName = _T("");
		UpdateData(FALSE);
		break;
	case 2:
		m_ctrlConnectBt.EnableWindow(FALSE);
		m_ctrlDisConnectBt.EnableWindow(FALSE);
		m_strName = _T("나홀로");
		UpdateData(FALSE);
		break;
	}
}

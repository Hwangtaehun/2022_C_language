
// SjData1Doc.cpp : CSjData1Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SjData1.h"
#endif

#include "SjData1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSjData1Doc

IMPLEMENT_DYNCREATE(CSjData1Doc, CDocument)

BEGIN_MESSAGE_MAP(CSjData1Doc, CDocument)
	ON_COMMAND(IDM_UP, &CSjData1Doc::OnUp)
	ON_COMMAND(IDM_DOWN, &CSjData1Doc::OnDown)
	ON_COMMAND(IDM_LEFT, &CSjData1Doc::OnLeft)
	ON_COMMAND(IDM_RIGHT, &CSjData1Doc::OnRight)
END_MESSAGE_MAP()


// CSjData1Doc 생성/소멸

CSjData1Doc::CSjData1Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

	m_nCnt = 0;
}

CSjData1Doc::~CSjData1Doc()
{
}

BOOL CSjData1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSjData1Doc serialization

void CSjData1Doc::Serialize(CArchive& ar)
{
	int i;
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar << m_nCnt;
		for (i = 0; i < m_nCnt; i++)
		{
			ar << m_aPoint[i];
			ar << m_aSize[i];
			ar << m_aWidth[i];
			ar << m_aPenColor[i];
			ar << m_aBurshColor[i];
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		ar >> m_nCnt;
		for (i = 0; i < m_nCnt; i++)
		{
			ar >> m_aPoint[i];
			ar >> m_aSize[i];
			ar >> m_aWidth[i];
			ar >> m_aPenColor[i];
			ar >> m_aBurshColor[i];
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSjData1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSjData1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSjData1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSjData1Doc 진단

#ifdef _DEBUG
void CSjData1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSjData1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSjData1Doc 명령


void CSjData1Doc::OnUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < m_nCnt; i++)
	{
		m_aPoint[i].y -= 5;
	}
	UpdateAllViews(NULL);
}


void CSjData1Doc::OnDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < m_nCnt; i++)
	{
		m_aPoint[i].y += 5;
	}
	UpdateAllViews(NULL);
}


void CSjData1Doc::OnLeft()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < m_nCnt; i++)
	{
		m_aPoint[i].x -= 5;
	}
	UpdateAllViews(NULL);
}


void CSjData1Doc::OnRight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < m_nCnt; i++)
	{
		m_aPoint[i].x += 5;
	}
	UpdateAllViews(NULL);
}

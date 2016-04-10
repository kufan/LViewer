// LogView.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLogView* g_pLogView;

typedef struct
{
	char	*title;
	int		nWidth;
}COLUMNSTRUCT;

COLUMNSTRUCT g_Log_Data[] = 
{
	{_T("Time"),			155	},
	{_T("Event"),			806	}
};

int g_Log_Width = 0;
int	g_Log_Count = (sizeof(g_Log_Data) / 8);
/////////////////////////////////////////////////////////////////////////////
// CLogView

IMPLEMENT_DYNCREATE(CLogView, CXTPListView)

CLogView::CLogView()
{
	g_pLogView = this;
}

CLogView::~CLogView()
{
}


BEGIN_MESSAGE_MAP(CLogView, CXTPListView)
	//{{AFX_MSG_MAP(CLogView)
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(IDM_EVENT_DELETE, OnEventDelete)
	ON_COMMAND(IDM_ALL_DELETE, OnAllDelete)
	ON_COMMAND(IDM_EVENT_SAVE, OnEventSave)
	ON_COMMAND(IDM_EVENT_COPY, OnEventCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogView drawing

void CLogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLogView diagnostics

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CXTPListView::AssertValid();
}

void CLogView::Dump(CDumpContext& dc) const
{
	CXTPListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogView message handlers

void CLogView::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{ 
	
	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)(pNMHDR); 
	*pResult = CDRF_NEWFONT; 
	if ( pLVCD->nmcd.dwDrawStage==CDDS_PREPAINT) 
	{ 
		*pResult = CDRF_NOTIFYITEMDRAW; 
	} 
	else if ( pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT )  
	{
		COLORREF   m_crTextBk , m_clrText; 
		int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec); 	
		CListCtrl &m_list = GetListCtrl(); 
 		CString str = m_pListCtrl->GetItemText(nItem ,1); 
		bool bDBImplFail = false;
 		if (str.Find(_T("主机下线")) == 0)
 		{ 
 			m_crTextBk = RGB(255, 255, 255) ; 
 			m_clrText  =  RGB(255,0,0) ; //粉色
 		}else
		if (str.Find(_T("主机上线")) == 0)
 		{
			m_crTextBk =  RGB(255, 255, 255);
			m_clrText  =  RGB(0,139,139);
 		}else
		if (str.Find(_T("欢迎使用")) == 0)
		{
			m_crTextBk =  RGB(255, 255, 255);
			m_clrText  =  RGB(218,165,32);
		}else
		if (str.Find(_T("已经开始测试")) == 0)
		{
			m_crTextBk =  RGB(255, 255, 255);
			m_clrText  =  RGB(0,180,250);
		}else
		if (str.Find(_T("已经停止测试")) == 0)
		{
			m_crTextBk =  RGB(255, 255, 255);
			m_clrText  =  RGB(0,180,125);
		}else
		{
			m_crTextBk =  RGB(255, 255, 255);
			m_clrText  =  RGB(0,0,0);//黑色
		}
		pLVCD->clrTextBk = m_crTextBk; 
		pLVCD->clrText = m_clrText; 	
		*pResult = CDRF_DODEFAULT; 
	} 
} 

void CLogView::OnInitialUpdate() 
{
	CXTPListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_pLogList = &GetListCtrl();

	HIMAGELIST hImageListSmall = NULL;
	Shell_GetImageLists(NULL, &hImageListSmall);
	ListView_SetImageList(m_pListCtrl->m_hWnd, hImageListSmall, LVSIL_SMALL);

	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	m_header.SetTheme(new CXTHeaderCtrlThemeOffice2003());
	m_header.EnablePopupMenus(TRUE);
	EnableControls(FALSE);
	ModifyDrawStyle(XTTHEME_WINXPTHEMES, 4);
	ModifyDrawStyle(HDR_XTP_HOTTRACKING, TRUE);
	ModifyDrawStyle(XTTHEME_HOTTRACKING, TRUE);	
    EnableUserSortColor(FALSE);

	m_pLogList->SetExtendedStyle(/*LVIF_PARAM |*/ LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP|/*LVS_EX_FLATSB|*/
		LVS_EX_ONECLICKACTIVATE | /*LVS_EX_UNDERLINEHOT |*/LVS_EX_SUBITEMIMAGES /*|LVS_EX_GRIDLINES*/);
	
	for (int i = 0; i < g_Log_Count; i++)
	{	
		m_pLogList->InsertColumn(i, g_Log_Data[i].title);
		m_pLogList->SetColumnWidth(i, g_Log_Data[i].nWidth);
		g_Log_Width += g_Log_Data[i].nWidth; // 总宽度
	}
}

void CLogView::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;
	
	// set sort image for header and sort column.
	//	m_listCtrl.SetSortImage(m_nSortedCol, m_bAscending);
	CXTSortClass csc(m_pListCtrl, m_nSortedCol);
	csc.Sort(m_bAscending, xtSortString);
}

BOOL CLogView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;
	if (pHDNotify->hdr.code == HDN_ITEMCLICKA || pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		SortColumn(pHDNotify->iItem, !m_bAscending);
	}
	return CXTPListView::OnNotify(wParam, lParam, pResult);
}

void CLogView::EnableControls(BOOL bRedraw)
{
	XTOSVersionInfo()->IsWinXPOrGreater();
	XTOSVersionInfo()->IsWinXPOrGreater();
	
	if (bRedraw)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
	}
}

void CLogView::ModifyDrawStyle(UINT uFlag, BOOL bRemove)
{
	CXTHeaderCtrlTheme* pTheme = m_header.GetTheme();
	if (pTheme)
	{
		DWORD dwStyle = pTheme->GetDrawStyle() & ~uFlag;
		
		if (bRemove)
			dwStyle |= uFlag;
		
		pTheme->SetDrawStyle(dwStyle, &m_header);
		m_header.RedrawWindow();
	}
}

BOOL CLogView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |=  LVS_REPORT;
	return CXTPListView::PreCreateWindow(cs);
}

void CLogView::OnSize(UINT nType, int cx, int cy) 
{
	CXTPListView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_pLogList == NULL)
		return;
	
	CRect rcClient;
	GetClientRect(rcClient);
	
	int	nClientWidth = rcClient.Width();
	int nIndex = g_Log_Count - 1;
	
	if (nClientWidth < g_Log_Width)
		return;
	
	m_pLogList->SetColumnWidth(nIndex, nClientWidth - g_Log_Width + g_Log_Data[nIndex].nWidth);
}

void CLogView::InsertLogItem(LPCTSTR Text,int Mode, int Flag)
{
	char m_Text[512] = {0};
	CTime time = CTime::GetCurrentTime();		//构造CTime对象 

	CString strTime = time.Format("[%Y-%m-%d %H:%M:%S]");
	m_pLogList->InsertItem(0, strTime, Flag);//int InsertItem( int nItem, LPCTSTR lpszItem, int nImage );
	m_pLogList->SetItemText(0, 1, Text);  //BOOL SetItemText( int nItem, int nSubItem, LPTSTR lpszText );
}

void CLogView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	CMenu	popup;
	popup.LoadMenu(IDR_LOG);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p;
	GetCursorPos(&p);
//	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
	CXTPCommandBars::TrackPopupMenu(pM, 0, p.x, p.y,this);
}

void CLogView::OnEventDelete() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_pLogList->GetFirstSelectedItemPosition();
	if  (pos  ==  NULL)
	{
		::MessageBox(NULL,"Please Select Event ...","Notice",MB_ICONINFORMATION);
		return;
	}
	else
	{
		while (pos)
		{
			int nItem = m_pLogList->GetNextSelectedItem(pos);
			m_pLogList->DeleteItem(nItem);
			pos = m_pLogList->GetFirstSelectedItemPosition();
		}
	}
}

void CLogView::OnAllDelete() 
{
	// TODO: Add your command handler code here
	m_pLogList->DeleteAllItems();
}

void CLogView::OnEventSave() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_pLogList->GetFirstSelectedItemPosition();
	if  (pos  ==  NULL)
	{
		::MessageBox(NULL,"Please Select Event ...","Notice",MB_ICONINFORMATION);
		return;
	}
	else
	{
		CTime time = CTime::GetCurrentTime(); ///构造CTime对象 
		CString strTime = time.Format("%Y-%m-%d %H-%M-%S");
		
		CFileDialog dlg(FALSE, _T("log"), strTime, OFN_OVERWRITEPROMPT, _T("*.log|*.log|*.txt|*.log"), NULL);
		if (dlg.DoModal() != IDOK)
			return;
		CFile file;
		char strip[50] = {0};
		if (file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
		{
			while (pos)
			{
				int nItem = m_pLogList->GetNextSelectedItem(pos);
				CString strTitle;
				strTitle.Format(_T("Time:%s	Event:%s"), m_pLogList->GetItemText(nItem, 0),m_pLogList->GetItemText(nItem, 1));
				char *strip = strTitle.GetBuffer(strTitle.GetLength() + 1);	//CString转换为char*
				strTitle.ReleaseBuffer();
				strcat(strip, "\r\n");
				file.Write(strip, strlen(strip));
				memset(strip, 0, 50);
			}
			file.Close();
			strTime = time.Format("[%Y-%m-%d %H:%M:%S]") + " Event Saved ...";
			::MessageBox(0,strTime,"Notice",MB_ICONINFORMATION);
	  }
	}
}

void CLogView::OnEventCopy() 
{
	// TODO: Add your command handler code here
	int nItem;
    CString strText(_T(""));
    POSITION pos = m_pLogList->GetFirstSelectedItemPosition();
	if  (pos  ==  NULL)
	{
		::MessageBox(NULL,"Please Select Event ...","Notice",MB_ICONINFORMATION);
		return;
	}
	else
	{
		//获取所有选中项目的内容。
		while (pos)
		{
			nItem = m_pLogList->GetNextSelectedItem(pos);
			strText += m_pLogList->GetItemText(nItem, 0) + " ";
			strText += m_pLogList->GetItemText(nItem, 1) + _T("\r\n");
		}
		//将内容保存到剪贴板。
		if (!strText.IsEmpty())
		{
			if (OpenClipboard())
			{
				EmptyClipboard();
				HGLOBAL hClipboardData = GlobalAlloc(GHND | GMEM_SHARE, (strText.GetLength() + 1) * sizeof(TCHAR));
				if (hClipboardData)
				{
					TCHAR* pszData = (TCHAR *)GlobalLock(hClipboardData);
					_tcscpy(pszData, strText);
					GlobalUnlock(hClipboardData);
					SetClipboardData(CF_TEXT, hClipboardData);
				}
				CloseClipboard();
			}
		}
	}
}




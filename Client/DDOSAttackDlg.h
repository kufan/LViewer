#if !defined(AFX_DDOSATTACKDLG_H__F1B94207_A6DF_420D_84CC_81F4122DD9DC__INCLUDED_)
#define AFX_DDOSATTACKDLG_H__F1B94207_A6DF_420D_84CC_81F4122DD9DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DDOSAttackDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDDOSAttackDlg dialog
#include "ClientView.h"
#include "WebAttackDlg.h"
#include "FlowAttackDlg.h"

class CDDOSAttackDlg : public CDialog
{
// Construction
public:
	CDDOSAttackDlg(CWnd* pParent = NULL);   // standard constructor
	CClientView *Point;
	void StatusTextOut(int iPane,LPCTSTR ptzFormat, ...);
	VOID InitailizeStatus();
// Dialog Data
	//{{AFX_DATA(CDDOSAttackDlg)
	enum { IDD = IDD_ATTACK_DIALOG };
	CXTPTabCtrl	m_TabCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDOSAttackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDDOSAttackDlg)
	afx_msg void OnClose();
	afx_msg void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeDdosAttack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWebAttackDlg m_WebAttack;
	CFlowAttackDlg m_FlowAttack;
	CStatusBarCtrl m_wndStatusBar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDOSATTACKDLG_H__F1B94207_A6DF_420D_84CC_81F4122DD9DC__INCLUDED_)

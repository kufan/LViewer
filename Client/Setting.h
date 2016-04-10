#if !defined(AFX_Setting_H__CA28388C_8306_4FD8_84E0_AE175B7C76C8__INCLUDED_)
#define AFX_Setting_H__CA28388C_8306_4FD8_84E0_AE175B7C76C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetting dialog

class CSetting : public CDialog
{
// Construction
public:
	CSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetting)
	enum { IDD = IDD_SETTING };
	CXTPButton	m_bisDisableSound_XTP;
	CXTPEdit	m_showtips;
	CXTPEdit	m_listen_port_XTP;
	CXTPButton	m_disable_poptips_XTP;
	CXTPEdit	m_connect_max_XTP;
	CXTPButton	m_connect_auto_XTP;
	UINT	m_max_connections;
	BOOL	m_connect_auto;
	BOOL	m_bIsDisablePopTips;
	UINT	m_listen_port;
	BOOL	m_bisDisableSound;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetting)
	afx_msg void OnApply();
	afx_msg void OnDisablePoptips();
	afx_msg void OnConnectAuto();
	virtual BOOL OnInitDialog();
	afx_msg void OnDisableSound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Setting_H__CA28388C_8306_4FD8_84E0_AE175B7C76C8__INCLUDED_)

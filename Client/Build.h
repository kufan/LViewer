#if !defined(AFX_BUILD_H__ACCDD992_A526_4D3B_A7BC_F325331462D9__INCLUDED_)
#define AFX_BUILD_H__ACCDD992_A526_4D3B_A7BC_F325331462D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Build.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuild dialog

class CBuild : public CDialog
{
// Construction
public:
	CBuild(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuild)
	enum { IDD = IDD_BUILD };
	CEdit	m_biaozhi;
	CComboBox	m_insatll_way;
	CEdit	m_svcname;
	CEdit	m_shelp;
	CEdit	m_scname;
	CEdit	m_version;
	CEdit	m_port;
	CEdit	m_dns;
	CComboBox	m_online_group;
	BOOL	m_green;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuild)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuild)
	virtual BOOL OnInitDialog();
	afx_msg void OnBuild();
	afx_msg void OnGreen();
	afx_msg void OnSelchangeInstallWay();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_bFirstShow;
	bool m_Servers;
	bool m_RunUP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILD_H__ACCDD992_A526_4D3B_A7BC_F325331462D9__INCLUDED_)

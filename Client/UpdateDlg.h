#if !defined(AFX_UPDATEDLG_H__4B1865D2_D586_4E97_B1AE_E41DED8DA2D3__INCLUDED_)
#define AFX_UPDATEDLG_H__4B1865D2_D586_4E97_B1AE_E41DED8DA2D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog

class CUpdateDlg : public CDialog
{
// Construction
public:
	CUpdateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpdateDlg)
	enum { IDD = IDD_UPDATE_DLG };
	CXTPHyperLink	m_SignNOIP;
	CComboBox	m_Combo_DnsIP;
	CString	m_DnsUser;
	CString	m_DnsPass;
	CString	m_DnsDomain;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

protected:
	// Generated message map functions
	//{{AFX_MSG(CUpdateDlg)
	afx_msg void OnBtnDnsupdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetwan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDLG_H__4B1865D2_D586_4E97_B1AE_E41DED8DA2D3__INCLUDED_)

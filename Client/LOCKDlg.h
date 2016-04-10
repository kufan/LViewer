#if !defined(AFX_LOCKDLG_H__88C18C85_7482_400D_AC5B_FD17C8CA3BDA__INCLUDED_)
#define AFX_LOCKDLG_H__88C18C85_7482_400D_AC5B_FD17C8CA3BDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LOCKDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLOCKDlg dialog

class CLOCKDlg : public CDialog
{
// Construction
public:
	CLOCKDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLOCKDlg)
	enum { IDD = IDD_LOCK_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLOCKDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	// Generated message map functions
	//{{AFX_MSG(CLOCKDlg)
	afx_msg void OnSetlock();
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCKDLG_H__88C18C85_7482_400D_AC5B_FD17C8CA3BDA__INCLUDED_)

#if !defined(AFX_FLOWATTACKDLG_H__7B51D657_6831_414F_B4D5_EFFD012A14CC__INCLUDED_)
#define AFX_FLOWATTACKDLG_H__7B51D657_6831_414F_B4D5_EFFD012A14CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlowAttackDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlowAttackDlg dialog
#include "EasySize.h"


class CFlowAttackDlg : public CDialog
{
// Construction
public:
	CFlowAttackDlg(CWnd* pParent = NULL);   // standard constructor
	LPSTR HexToDecimal(LPSTR Transition=NULL,BOOL Format=FALSE);
	WORD ForMatFlowAddr(LPSTR szAddr,WORD iPort);
	CHAR htod(CHAR c);
	VOID ShowThreads();
	DECLARE_EASYSIZE

	LPVOID Point;//∏∏¥∞ø⁄÷∏’Î
	LPVOID ViewPoint;//View ÷∏’Î

// Dialog Data
	//{{AFX_DATA(CFlowAttackDlg)
	enum { IDD = IDD_CUSTOMATTACK_DIALOG };
	CComboBox	m_ModelCtrl;
	CSliderCtrl	m_TimeCtrl;
	CSliderCtrl	m_ThreadCtrl;
	CSpinButtonCtrl	m_RateCtrl;
	CSpinButtonCtrl	m_HotsNumCtrl;
	CString	m_Decimal;
	CString	m_HexData;
	UINT	m_HostNum;
	UINT	m_SendRate;
	UINT	m_Thread;
	UINT	m_AttackTime;
	CString	m_Target;
	UINT	m_Port;
	BOOL	m_Select;
	BOOL	m_Auto;
	CString	m_TipShow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlowAttackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFlowAttackDlg)
	afx_msg void OnChangeEditDecimal();
	afx_msg void OnSetfocusEditDecimal();
	afx_msg void OnSetfocusEditHex();
	afx_msg void OnChangeEditHex();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCustomdrawSliderTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderThread(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStartAttack();
	afx_msg void OnStartStop();
	afx_msg void OnSelecthost();
	afx_msg void OnChangeTargetWeb();
	afx_msg void OnSetfocusTargetWeb();
	afx_msg void OnSetfocusComboModel();
	afx_msg void OnSelchangeComboModel();
	afx_msg void OnSetfocusThreadnums();
	afx_msg void OnChangeThreadnums();
	afx_msg void OnChangeAttacktimes();
	afx_msg void OnSetfocusAttacktimes();
	afx_msg void OnSetfocusSendRate();
	afx_msg void OnChangeSendRate();
	afx_msg void OnChangeHostnums();
	afx_msg void OnSetfocusHostnums();
	afx_msg void OnChangeAttckport();
	afx_msg void OnSetfocusAttckport();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_MarkPos;
	WORD m_Size;
	WORD iTaskID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOWATTACKDLG_H__7B51D657_6831_414F_B4D5_EFFD012A14CC__INCLUDED_)

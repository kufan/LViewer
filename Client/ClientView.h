// ClientView.h : interface of the CClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ClientVIEW_H__14553897_2664_48B4_A82B_6D6F8F789ED3__INCLUDED_)
#define AFX_ClientVIEW_H__14553897_2664_48B4_A82B_6D6F8F789ED3__INCLUDED_

#include "IniFile.h"
#include "SEU_QQwry.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClientView : public CXTPListView
{
protected: // create from serialization only
	CClientView();
	DECLARE_DYNCREATE(CClientView)

// Attributes
//	WORD SendDDosAttackCommand(LPATTACK m_Attack,INT HostNums,BOOL AutoAttack,WORD iTaskID);
//	WORD SendDDostStopCommand(WORD iTaskID);
//	VOID SendAutoAttack(ClientContext *Context);
public:

// Operations
public:
// Overrides
	int CountID;
	void SendSelectCommand(PBYTE pData, UINT nSize);
	void NewInitialUpdate();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientView)
	public:
	virtual void OnInitialUpdate(); // called first time after construct
	protected:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	CIniFile	   m_IniFile;
	CListCtrl *m_pListCtrl;
	CIOCPServer* m_iocpServer;
	virtual ~CClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int             m_nSortedCol;
	bool            m_bAscending;
	CXTPHeaderCtrl   m_header;
	void SortColumn(int iCol, bool bAsc);
// Generated message map functions
protected:
	//{{AFX_MSG(CClientView)
	afx_msg void ModifyDrawStyle(UINT uFlag, BOOL bRemove);
	afx_msg void EnableControls(BOOL bRedraw);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFilemanager();
	afx_msg void OnScreenspy();
	afx_msg void OnDownexec();
	afx_msg void OnWebcam();
	afx_msg void OnRemove();
	afx_msg void OnKeyboard();
	afx_msg void OnSystem();
	afx_msg void OnRemoteshell();
	afx_msg void OnLogoff();
	afx_msg void OnReboot();
	afx_msg void OnShutdown();
	afx_msg void OnSelectAll();
	afx_msg void OnUnselectAll();
	afx_msg void OnOpenUrlHide();
	afx_msg void OnOpenUrlShow();
	afx_msg void OnCleanevent();
	afx_msg void OnRenameRemark();
	afx_msg void OnUpdateServer();
	afx_msg void OnAudioListen();
	afx_msg void OnDisconnect();
	afx_msg void OnShowmsg();
	afx_msg void OnChangegroup();
	afx_msg void OnSysinfo();
// 	afx_msg void OnDdos();
	afx_msg int FindCountry(CString local);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CImageList   I_ImageList;
	SEU_QQwry *m_QQwry;
	afx_msg LRESULT OnOpenManagerDialog(WPARAM /*wParam*/, LPARAM /*lParam*/);
	afx_msg	LRESULT OnOpenScreenSpyDialog(WPARAM, LPARAM);
	afx_msg	LRESULT	OnOpenWebCamDialog(WPARAM, LPARAM);
	afx_msg	LRESULT	OnOpenAudioDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenKeyBoardDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenSystemDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenShellDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnRemoveFromList(WPARAM, LPARAM);
	afx_msg LRESULT OnAddToList(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenSysInfoDialog(WPARAM, LPARAM);
//private:
//	BOOL m_AutoAttack;//新上线自动...
//	ATTACK m_AutoAttackData;//自动攻击参数.
// 	WORD m_AutoTask;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ClientVIEW_H__14553897_2664_48B4_A82B_6D6F8F789ED3__INCLUDED_)

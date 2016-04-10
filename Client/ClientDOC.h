// ClientDoc.h : interface of the CClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ClientDOC_H__57FB1788_3C2A_40A9_BAB7_3F192505E38E__INCLUDED_)
#define AFX_ClientDOC_H__57FB1788_3C2A_40A9_BAB7_3F192505E38E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClientDoc : public CDocument
{
protected: // create from serialization only
	CClientDoc();
	DECLARE_DYNCREATE(CClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDoc)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ClientDOC_H__57FB1788_3C2A_40A9_BAB7_3F192505E38E__INCLUDED_)

// Skin.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "Skin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkin dialog


CSkin::CSkin(CWnd* pParent /*=NULL*/)
	: CDialog(CSkin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSkin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkin, CDialog)
	//{{AFX_MSG_MAP(CSkin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnReleasedcaptureSlider2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER3, OnReleasedcaptureSlider3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER4, OnReleasedcaptureSlider4)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER5, OnReleasedcaptureSlider5)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER6, OnReleasedcaptureSlider6)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER7, OnReleasedcaptureSlider7)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER8, OnReleasedcaptureSlider8)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER9, OnReleasedcaptureSlider9)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER10, OnReleasedcaptureSlider10)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER11, OnReleasedcaptureSlider11)
	ON_BN_CLICKED(IDC_SET_SKIN, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkin message handlers

void CSkin::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	SkinH_AdjustHSV( ((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->GetPos(),
//					  ((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->GetPos(), 
//					  ((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->GetPos()
//					  );
	
	*pResult = 0;
}

BOOL CSkin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	pSlider->SetRange(-180,180,TRUE);
	pSlider->SetPos(0);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	pSlider->SetRange(-100,100,TRUE);
	pSlider->SetPos(0);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER3);
	pSlider->SetRange(-100,100,TRUE);
	pSlider->SetPos(0);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER4);
	pSlider->SetRange(0,255,TRUE);
	pSlider->SetPos(120);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER5);
	pSlider->SetRange(2,19,TRUE);
	pSlider->SetPos(2);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER6);
	pSlider->SetRange(0,20,TRUE);
	pSlider->SetPos(0);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER7);
	pSlider->SetRange(0,255,TRUE);
	pSlider->SetPos(0);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER8);
	pSlider->SetRange(0,255,TRUE);
	pSlider->SetPos(0);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER9);
	pSlider->SetRange(0,255,TRUE);
	pSlider->SetPos(0);

	pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER10);
	pSlider->SetRange(0,255,TRUE);
	pSlider->SetPos(0);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSkin::OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnReleasedcaptureSlider1(pNMHDR, pResult); 	
	*pResult = 0;
}

void CSkin::OnReleasedcaptureSlider3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedcaptureSlider1(pNMHDR, pResult);
	*pResult = 0;
}

void CSkin::OnReleasedcaptureSlider4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	SkinH_AdjustAero( 
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER4))->GetPos(),
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER7))->GetPos(), 
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER6))->GetPos(),
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER5))->GetPos(),
		0, 0,
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER8))->GetPos(),
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER9))->GetPos(),
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER10))->GetPos()
// 	);


// 	*pResult = 0;
// }

void CSkin::OnReleasedcaptureSlider5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedcaptureSlider4(pNMHDR, pResult);
	*pResult = 0;
}

void CSkin::OnReleasedcaptureSlider6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedcaptureSlider4(pNMHDR, pResult);
	*pResult = 0;
}

void CSkin::OnColor() 
{
	// TODO: Add your control notification handler code here
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "É«µ÷",((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "±¥ºÍ",((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "ÁÁ¶È",((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "Í¸Ã÷",((CSliderCtrl*)GetDlgItem(IDC_SLIDER4))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "ÒõÓ°´óÐ¡",((CSliderCtrl*)GetDlgItem(IDC_SLIDER5))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "ÒõÓ°ÇåÎú",((CSliderCtrl*)GetDlgItem(IDC_SLIDER6))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "ÒõÓ°ÁÁ¶È",((CSliderCtrl*)GetDlgItem(IDC_SLIDER7))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "ColorR",((CSliderCtrl*)GetDlgItem(IDC_SLIDER8))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "ColorG",((CSliderCtrl*)GetDlgItem(IDC_SLIDER9))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "ColorB",((CSliderCtrl*)GetDlgItem(IDC_SLIDER10))->GetPos());
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Æ¤·ô", "Menu",((CSliderCtrl*)GetDlgItem(IDC_SLIDER11))->GetPos());
		OnCancel();
}

void CSkin::OnReleasedcaptureSlider7(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedcaptureSlider4(pNMHDR, pResult);
	*pResult = 0;
}

void CSkin::OnReleasedcaptureSlider8(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedcaptureSlider4(pNMHDR, pResult);
	*pResult = 0;
}

void CSkin::OnReleasedcaptureSlider9(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedcaptureSlider4(pNMHDR, pResult);
	*pResult = 0;
}

void CSkin::OnReleasedcaptureSlider10(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnReleasedcaptureSlider4(pNMHDR, pResult);
	*pResult = 0;
}

void CSkin::OnReleasedcaptureSlider11(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
// 	SkinH_SetMenuAlpha(((CSliderCtrl*)GetDlgItem(IDC_SLIDER11))->GetPos());
	*pResult = 0;
}
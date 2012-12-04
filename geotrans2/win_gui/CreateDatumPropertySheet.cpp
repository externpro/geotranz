// CreateDatumPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "CreateDatumPropertySheet.h"
#include "3ParamPropertyPage.h"
#include "7ParamPropertyPage.h"
#include "mastervw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateDatumPropertySheet

IMPLEMENT_DYNAMIC(CCreateDatumPropertySheet, CPropertySheet)

CCreateDatumPropertySheet::CCreateDatumPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CCreateDatumPropertySheet::CCreateDatumPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
  AddPage( _3ParamPropertyPage = new C3ParamPropertyPage());
  AddPage( _7ParamPropertyPage = new C7ParamPropertyPage());
}

CCreateDatumPropertySheet::~CCreateDatumPropertySheet()
{
  delete _3ParamPropertyPage;
  delete _7ParamPropertyPage;
}


BEGIN_MESSAGE_MAP(CCreateDatumPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CCreateDatumPropertySheet)
ON_BN_CLICKED(IDOK, OnOK)
ON_BN_CLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateDatumPropertySheet message handlers

void CCreateDatumPropertySheet::setViews( CMasterView* _upperView, CMasterView* _lowerView )
{
  upperView = _upperView;
  lowerView = _lowerView;
}


BOOL CCreateDatumPropertySheet::OnInitDialog() 
{
  m_bModeless = FALSE;   
  m_nFlags |= WF_CONTINUEMODAL;

  BOOL bResult = CPropertySheet::OnInitDialog();

  m_bModeless = TRUE;
  m_nFlags &= ~WF_CONTINUEMODAL;

CWnd* pWnd = NULL;
 pWnd = GetDlgItem(ID_APPLY_NOW);

if(pWnd != NULL)

pWnd->ShowWindow(SW_HIDE);

  return bResult;
}


void CCreateDatumPropertySheet::OnCancel() 
{
	// TODO: Add extra cleanup here

  CPropertySheet::EndDialog(1);
	//CPropertySheet::OnCancel();
}


void CCreateDatumPropertySheet::OnOK() 
{
  long error_code;
  if( GetActiveIndex() == 0 )
    error_code = _3ParamPropertyPage->createDatum();
  else
    error_code = _7ParamPropertyPage->createDatum();

  if( !error_code )
    CPropertySheet::EndDialog(1);

  upperView->FillListBox();
  lowerView->FillListBox();
}


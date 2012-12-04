// deldatumvw.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "strtoval.h"
#include "deldatumvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteDatumView dialog


CDeleteDatumView::CDeleteDatumView(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteDatumView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteDatumView)
	m_datum_index = -1;
	//}}AFX_DATA_INIT
}


void CDeleteDatumView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteDatumView)
	DDX_CBIndex(pDX, IDC_DELETE_DATUM_COMBOBOX, m_datum_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteDatumView, CDialog)
	//{{AFX_MSG_MAP(CDeleteDatumView)
	ON_CBN_SELCHANGE(IDC_DELETE_DATUM_COMBOBOX, OnSelchangeDeleteDatumCombobox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// This function is called after the constructor but before it is displayed
BOOL CDeleteDatumView::OnInitDialog()
{
  CDialog::OnInitDialog();
  FillListBox();
  UpdateData(FALSE);
  return (TRUE);
}


/////////////////////////////////////////////////////////////////////////////
// CDeleteDatumView message handlers

void CDeleteDatumView::OnSelchangeDeleteDatumCombobox() 
{
  CWnd *wPtr = GetDlgItem(IDC_DELETE_DATUM_COMBOBOX);
  m_datum_index = ((CComboBox*)wPtr)->GetCurSel( );
  UpdateData(FALSE);
}

void CDeleteDatumView::OnOK() 
{
  char datum_code[10];

  long error_code = Get_Datum_Code(m_datum_index+1, datum_code);
  
  if (!error_code) 
	 error_code = Remove_Datum( datum_code );

  if (!error_code) 
	 CDialog::OnOK();

  else
  {
    char err_str[256];
    char temp_err_str[256];
    sprintf(err_str,"Error:\n");
    Get_Return_Code_String(error_code,"\n",temp_err_str);
    strcat(err_str, temp_err_str);
    AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
  }
}

/// Our Function
void CDeleteDatumView::FillListBox()
{
  long count;

  long error_code = Get_Datum_Count(&count);
  if (error_code)
    AfxMessageBox("Error getting datum count!",MB_OK | MB_ICONEXCLAMATION);
  else
  {  
    CWnd* wPtr = GetDlgItem(IDC_DELETE_DATUM_COMBOBOX);
    
    for (int i = 0; i < count; i++)
    {
      char datum_code[10];
      error_code = Get_Datum_Code(i+1,datum_code);
      sprintf(datum_code,"%s:",datum_code);

      char datum_name[40];
      error_code = Get_Datum_Name(i+1,datum_name);

      char datum_full_name[50];
      sprintf(datum_full_name,"%-7s%s",datum_code,datum_name);
      ((CComboBox*)wPtr)->AddString(datum_full_name);
    }
    long index;
    Get_Datum_Index ("WGE", &index);
    ((CComboBox*)wPtr)->SetCurSel(index-1);
    OnSelchangeDeleteDatumCombobox();
  }
}


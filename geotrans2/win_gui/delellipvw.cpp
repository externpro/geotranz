// deletellipvw.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "strtoval.h"
#include "delellipvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteEllipsoid dialog


CDeleteEllipsoid::CDeleteEllipsoid(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteEllipsoid::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteEllipsoid)
	m_ellipsoid_index = -1;
	//}}AFX_DATA_INIT
}


void CDeleteEllipsoid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteEllipsoid)
	DDX_CBIndex(pDX, IDC_DELETE_ELLIPSOID_COMBOBOX, m_ellipsoid_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteEllipsoid, CDialog)
	//{{AFX_MSG_MAP(CDeleteEllipsoid)
	ON_CBN_SELCHANGE(IDC_DELETE_ELLIPSOID_COMBOBOX, OnSelchangeDeleteEllipsoidCombobox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// This function is called after the constructor but before it is displayed
BOOL CDeleteEllipsoid::OnInitDialog()
{
  CDialog::OnInitDialog();
  FillListBox();
  UpdateData(FALSE);
  return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CDeleteEllipsoid message handlers

void CDeleteEllipsoid::OnSelchangeDeleteEllipsoidCombobox() 
{
   CWnd *wPtr = GetDlgItem(IDC_DELETE_ELLIPSOID_COMBOBOX);
   m_ellipsoid_index = ((CComboBox*)wPtr)->GetCurSel( );
   UpdateData(FALSE);	
}

void CDeleteEllipsoid::OnOK() 
{
  char ellipsoid_code[10];

  long error_code = Get_Ellipsoid_Code(m_ellipsoid_index+1, ellipsoid_code);
  if (!error_code) 
  {
    error_code = Remove_Ellipsoid(ellipsoid_code);
  }
 
  if (!error_code) 
  {
	  CDialog::OnOK();
  }	
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
void CDeleteEllipsoid::FillListBox()
{
  long count;

  long error_code = Get_Ellipsoid_Count(&count);
  if (error_code)
    AfxMessageBox("Error getting ellipsoid count!",MB_OK | MB_ICONEXCLAMATION);
  else
  {  
    CWnd* wPtr = GetDlgItem(IDC_DELETE_ELLIPSOID_COMBOBOX);
    
    for (int i = 0; i < count; i++)
    {
      char ellipsoid_code[10];
      error_code = Get_Ellipsoid_Code(i+1,ellipsoid_code);
      sprintf(ellipsoid_code,"%s:",ellipsoid_code);

      char ellipsoid_name[40];
      error_code = Get_Ellipsoid_Name(i+1,ellipsoid_name);

      char ellipsoid_full_name[50];
      sprintf(ellipsoid_full_name,"%-7s%s",ellipsoid_code,ellipsoid_name);
      ((CComboBox*)wPtr)->AddString(ellipsoid_full_name);
    }
    long index;
    Get_Ellipsoid_Index ("WE", &index);
    ((CComboBox*)wPtr)->SetCurSel(index-1);
    OnSelchangeDeleteEllipsoidCombobox();
  }
}

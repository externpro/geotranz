// Ellipsevw.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "strtoval.h"
#include "ellipsevw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEllipsoidView dialog


CEllipsoidView::CEllipsoidView(CWnd* pParent /*=NULL*/)
	: CDialog(CEllipsoidView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEllipsoidView)
	m_ellipsoid_code = _T("WE");
	m_ellipsoid_name = _T("WGS84");
	m_semimajor_axis = _T("6378137");
	m_inverse_flat = _T("300");
	//}}AFX_DATA_INIT
  m_ellipsoid_code_value = "WE";
  m_ellipsoid_name_value = "WGS84";
  m_semimajor_axis_value = 6378137.0;
  m_inverse_flat_value = 1 / 300.0;
}


void CEllipsoidView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEllipsoidView)
	DDX_Text(pDX, IDC_ELLIPSOID_CODE, m_ellipsoid_code);
	DDX_Text(pDX, IDC_ELLIPSOID_NAME, m_ellipsoid_name);
	DDX_Text(pDX, IDC_ELLIPSOID_SEMIMAJOR_AXIS, m_semimajor_axis);
	DDX_Text(pDX, IDC_ELLIPSOID_INVERSE_FLAT, m_inverse_flat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEllipsoidView, CDialog)
	//{{AFX_MSG_MAP(CEllipsoidView)
	ON_EN_CHANGE(IDC_ELLIPSOID_CODE, OnChangeEllipsoidCode)
	ON_EN_CHANGE(IDC_ELLIPSOID_NAME, OnChangeEllipsoidName)
	ON_EN_CHANGE(IDC_ELLIPSOID_SEMIMAJOR_AXIS, OnChangeEllipsoidSemimajorAxis)
	ON_EN_CHANGE(IDC_ELLIPSOID_INVERSE_FLAT, OnChangeEllipsoidInverseFlat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEllipsoidView message handlers

void CEllipsoidView::OnChangeEllipsoidCode() 
{
  UpdateData(TRUE);
  m_ellipsoid_code_value = LPCTSTR (m_ellipsoid_code);	
}

void CEllipsoidView::OnChangeEllipsoidName() 
{
  UpdateData(TRUE);
  m_ellipsoid_name_value = LPCTSTR (m_ellipsoid_name);	
}

void CEllipsoidView::OnChangeEllipsoidSemimajorAxis() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_ELLIPSOID_SEMIMAJOR_AXIS);
  double temp_val;
  if (String_to_Double(m_semimajor_axis,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_semimajor_axis_value = temp_val;
  }
}


void CEllipsoidView::OnChangeEllipsoidInverseFlat() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_ELLIPSOID_INVERSE_FLAT);
  double temp_val;
  if (String_to_Double(m_inverse_flat,&temp_val))
  {
    int start,end;
   ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_inverse_flat_value = (1/temp_val);
  }
}

void CEllipsoidView::OnCancel() 
{
	CDialog::OnCancel();
}

void CEllipsoidView::OnOK() 
{
  long error_code = Define_Ellipsoid (m_ellipsoid_code_value, m_ellipsoid_name_value,
                                      m_semimajor_axis_value, m_inverse_flat_value);
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

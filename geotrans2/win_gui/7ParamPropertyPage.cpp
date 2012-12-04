// 7ParamPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "strtoval.h"
#include "7ParamPropertyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C7ParamPropertyPage property page

IMPLEMENT_DYNCREATE(C7ParamPropertyPage, CPropertyPage)

C7ParamPropertyPage::C7ParamPropertyPage() : CPropertyPage(C7ParamPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(C7ParamPropertyPage)
	m_datum_code = _T("WGE");
	m_deltaX = _T("0");
	m_deltaY = _T("0");
	m_deltaZ = _T("0");
	m_datum_name = _T("World Geodetic System 1984");
	m_rotationX = _T("0");
	m_rotationY = _T("0");
	m_rotationZ = _T("0");
	m_scale = _T("0");
	m_ellipsoid_index = -1;
	//}}AFX_DATA_INIT
	m_datum_code_value = "WGE";
	m_datum_name_value = "World Geodetic System 1984";
  m_deltaX_value = 0.0;
  m_deltaY_value = 0.0;
  m_deltaZ_value = 0.0;
  m_rotationX_value = 0.0;
  m_rotationY_value = 0.0;
  m_rotationZ_value = 0.0;
  m_scale_value = 0.0;
}

C7ParamPropertyPage::~C7ParamPropertyPage()
{
}

void C7ParamPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C7ParamPropertyPage)
	DDX_Text(pDX, IDC_DATUM_CODE, m_datum_code);
	DDX_Text(pDX, IDC_DATUM_DELTAX, m_deltaX);
	DDX_Text(pDX, IDC_DATUM_DELTAY, m_deltaY);
	DDX_Text(pDX, IDC_DATUM_DELTAZ, m_deltaZ);
	DDX_Text(pDX, IDC_DATUM_NAME, m_datum_name);
	DDX_Text(pDX, IDC_DATUM_ROTATIONX, m_rotationX);
	DDX_Text(pDX, IDC_DATUM_ROTATIONY, m_rotationY);
	DDX_Text(pDX, IDC_DATUM_ROTATIONZ, m_rotationZ);
	DDX_Text(pDX, IDC_7PARAM_DATUM_SCALE, m_scale);
	DDX_CBIndex(pDX, IDC_DATUM_ELLIPSOID_COMBOBOX, m_ellipsoid_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C7ParamPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(C7ParamPropertyPage)
	ON_EN_CHANGE(IDC_DATUM_CODE, OnChangeDatumCode)
	ON_EN_CHANGE(IDC_DATUM_NAME, OnChangeDatumName)
	ON_EN_CHANGE(IDC_DATUM_DELTAX, OnChangeDatumDeltax)
	ON_EN_CHANGE(IDC_DATUM_DELTAY, OnChangeDatumDeltay)
	ON_EN_CHANGE(IDC_DATUM_DELTAZ, OnChangeDatumDeltaz)
	ON_EN_CHANGE(IDC_DATUM_ROTATIONX, OnChangeDatumRotationX)
	ON_EN_CHANGE(IDC_DATUM_ROTATIONY, OnChangeDatumRotationY)
	ON_EN_CHANGE(IDC_DATUM_ROTATIONZ, OnChangeDatumRotationZ)
	ON_CBN_SELCHANGE(IDC_DATUM_ELLIPSOID_COMBOBOX, OnSelchangeDatumEllipsoidCombobox)
	ON_EN_CHANGE(IDC_7PARAM_DATUM_SCALE, OnChange7ParamDatumScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////

void C7ParamPropertyPage::FillListBox()
{
  long count;

  long error_code = Get_Ellipsoid_Count(&count);
  if (error_code)
    AfxMessageBox("Error getting ellipsoid count!",MB_OK | MB_ICONEXCLAMATION);
  else
  {  
    CWnd* wPtr = GetDlgItem(IDC_DATUM_ELLIPSOID_COMBOBOX);
    
    for (int i=0; i < count; i++)
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
    OnSelchangeDatumEllipsoidCombobox();
  }
}


long C7ParamPropertyPage::createDatum()
{
  char ellipsoid_code[10];

  long error_code = Get_Ellipsoid_Code(m_ellipsoid_index+1, ellipsoid_code);
  error_code = Define_Datum (Seven_Param_Datum_Type, m_datum_code_value, m_datum_name_value, ellipsoid_code,
                             m_deltaX_value, m_deltaY_value, m_deltaZ_value,
                             -1, -1, -1,
                             -90, 90, -180, 180,
                             m_rotationX_value, m_rotationY_value, m_rotationZ_value, m_scale_value);
  if (error_code) 
 /* {
    CDialog::OnOK();
  }
  else*/
  {
    char err_str[256];
    char temp_err_str[256];
    sprintf(err_str,"Error:\n");
    Get_Return_Code_String(error_code,"\n",temp_err_str);
    strcat(err_str, temp_err_str);
    AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
  }

  return error_code;
}



/////////////////////////////////////////////////////////////////////////////
// C7ParamPropertyPage message handlers


BOOL C7ParamPropertyPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
  FillListBox();
  UpdateData(FALSE);

  return (TRUE);
}


void C7ParamPropertyPage::OnChangeDatumCode() 
{
  UpdateData(TRUE);
  m_datum_code_value = LPCTSTR (m_datum_code);	
}


void C7ParamPropertyPage::OnChangeDatumName() 
{
  UpdateData(TRUE);
  m_datum_name_value = LPCTSTR (m_datum_name);	
}


void C7ParamPropertyPage::OnChangeDatumDeltax() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_DELTAX);
  double temp_val;
  if (String_to_Double(m_deltaX,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_deltaX_value = temp_val;
  }
}


void C7ParamPropertyPage::OnChangeDatumDeltay() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_DELTAY);
  double temp_val;
  if (String_to_Double(m_deltaY,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_deltaY_value = temp_val;
  }
}


void C7ParamPropertyPage::OnChangeDatumDeltaz() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_DELTAZ);
  double temp_val;
  if (String_to_Double(m_deltaZ,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_deltaZ_value = temp_val;
  }
}


void C7ParamPropertyPage::OnChangeDatumRotationX() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_ROTATIONX);
  double temp_val;
  if (String_to_Double(m_rotationX,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_rotationX_value = temp_val;
  }
}


void C7ParamPropertyPage::OnChangeDatumRotationY() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_ROTATIONY);
  double temp_val;
  if (String_to_Double(m_rotationY,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_rotationY_value = temp_val;
  }
}


void C7ParamPropertyPage::OnChangeDatumRotationZ() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_ROTATIONZ);
  double temp_val;
  if (String_to_Double(m_rotationZ,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_rotationZ_value = temp_val;
  }
}


void C7ParamPropertyPage::OnSelchangeDatumEllipsoidCombobox() 
{
   CWnd* wPtr = GetDlgItem(IDC_DATUM_ELLIPSOID_COMBOBOX);
   m_ellipsoid_index = ((CComboBox*)wPtr)->GetCurSel( );
 
   UpdateData(FALSE);
}


void C7ParamPropertyPage::OnChange7ParamDatumScale() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_7PARAM_DATUM_SCALE);
  double temp_val;
  if (String_to_Double(m_scale,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_scale_value = temp_val;
  }
}


/*BOOL C7ParamPropertyPage::OnKillActive()
{
  return TRUE;
}


void C7ParamPropertyPage::OnOK() 
{
  char ellipsoid_code[10];

  long error_code = Get_Ellipsoid_Code(m_ellipsoid_index+1, ellipsoid_code);
 /* error_code = Define_Datum (m_datum_code_value, m_datum_name_value, ellipsoid_code,
                             m_deltaX_value, m_deltaY_value, m_deltaZ_value,
                             m_sigmaX_value, m_sigmaY_value, m_sigmaZ_value,
                             m_south_lat_value, m_north_lat_value, m_west_lon_value, m_east_lon_value);*/
 /* if (!error_code) 
    CPropertyPage::OnOK();
  else
  {
    char err_str[256];
    char temp_err_str[256];
    sprintf(err_str,"Error:\n");
    Get_Return_Code_String(error_code,"\n",temp_err_str);
    strcat(err_str, temp_err_str);
    AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
  }
}*/

// 3ParamPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "strtoval.h"
#include "3ParamPropertyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3ParamPropertyPage property page

IMPLEMENT_DYNCREATE(C3ParamPropertyPage, CPropertyPage)

C3ParamPropertyPage::C3ParamPropertyPage() : CPropertyPage(C3ParamPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(C3ParamPropertyPage)
	m_datum_code = _T("WGE");
	m_deltaX = _T("0");
	m_deltaY = _T("0");
	m_deltaZ = _T("0");
	m_datum_name = _T("World Geodetic System 1984");
	m_sigmaX = _T("-1");
	m_sigmaY = _T("-1");
	m_sigmaZ = _T("-1");
	m_ellipsoid_index = -1;
	m_east_lon = _T("180 00 00E");
	m_north_lat = _T("90 00 00N");
	m_south_lat = _T("90 00 00S");
	m_west_lon = _T("180 00 00W");
	//}}AFX_DATA_INIT
	m_datum_code_value = "WGE";
	m_datum_name_value = "World Geodetic System 1984";
  m_deltaX_value = 0.0;
  m_deltaY_value = 0.0;
  m_deltaZ_value = 0.0;
  m_sigmaX_value = -1.0;
  m_sigmaY_value = -1.0;
  m_sigmaZ_value = -1.0;
  m_west_lon_value = -PI;
  m_east_lon_value = +PI;
  m_south_lat_value = -PI/2.0;
  m_north_lat_value = +PI/2.0;

  close_property_page = true;
}

C3ParamPropertyPage::~C3ParamPropertyPage()
{
}

void C3ParamPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3ParamPropertyPage)
	DDX_Text(pDX, IDC_DATUM_CODE, m_datum_code);
	DDX_Text(pDX, IDC_DATUM_DELTAX, m_deltaX);
	DDX_Text(pDX, IDC_DATUM_DELTAY, m_deltaY);
	DDX_Text(pDX, IDC_DATUM_DELTAZ, m_deltaZ);
	DDX_Text(pDX, IDC_DATUM_NAME, m_datum_name);
	DDX_Text(pDX, IDC_DATUM_SIGMAX, m_sigmaX);
	DDX_Text(pDX, IDC_DATUM_SIGMAY, m_sigmaY);
	DDX_Text(pDX, IDC_DATUM_SIGMAZ, m_sigmaZ);
	DDX_CBIndex(pDX, IDC_DATUM_ELLIPSOID_COMBOBOX, m_ellipsoid_index);
	DDX_Text(pDX, IDC_DATUM_EAST_LON, m_east_lon);
	DDX_Text(pDX, IDC_DATUM_NORTH_LAT, m_north_lat);
	DDX_Text(pDX, IDC_DATUM_SOUTH_LAT, m_south_lat);
	DDX_Text(pDX, IDC_DATUM_WEST_LON, m_west_lon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3ParamPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(C3ParamPropertyPage)
	ON_EN_CHANGE(IDC_DATUM_CODE, OnChangeDatumCode)
	ON_EN_CHANGE(IDC_DATUM_NAME, OnChangeDatumName)
	ON_EN_CHANGE(IDC_DATUM_DELTAX, OnChangeDatumDeltax)
	ON_EN_CHANGE(IDC_DATUM_DELTAY, OnChangeDatumDeltay)
	ON_EN_CHANGE(IDC_DATUM_DELTAZ, OnChangeDatumDeltaz)
	ON_EN_CHANGE(IDC_DATUM_SIGMAX, OnChangeDatumSigmax)
	ON_EN_CHANGE(IDC_DATUM_SIGMAY, OnChangeDatumSigmay)
	ON_EN_CHANGE(IDC_DATUM_SIGMAZ, OnChangeDatumSigmaz)
	ON_CBN_SELCHANGE(IDC_DATUM_ELLIPSOID_COMBOBOX, OnSelchangeDatumEllipsoidCombobox)
	ON_EN_CHANGE(IDC_DATUM_EAST_LON, OnChangeDatumEastLon)
	ON_EN_CHANGE(IDC_DATUM_NORTH_LAT, OnChangeDatumNorthLat)
	ON_EN_CHANGE(IDC_DATUM_SOUTH_LAT, OnChangeDatumSouthLat)
	ON_EN_CHANGE(IDC_DATUM_WEST_LON, OnChangeDatumWestLon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////

// This function is called after the constructor but before it is displayed
void C3ParamPropertyPage::FillListBox()
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


long C3ParamPropertyPage::createDatum()
{
  char ellipsoid_code[10];

  long error_code = Get_Ellipsoid_Code(m_ellipsoid_index+1, ellipsoid_code);
  error_code = Define_Datum (Three_Param_Datum_Type, m_datum_code_value, m_datum_name_value, ellipsoid_code,
                             m_deltaX_value, m_deltaY_value, m_deltaZ_value,
                             m_sigmaX_value, m_sigmaY_value, m_sigmaZ_value,
                             m_south_lat_value, m_north_lat_value, m_west_lon_value, m_east_lon_value,
                             0, 0, 0, 0);
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
// C3ParamPropertyPage message handlers

BOOL C3ParamPropertyPage::OnInitDialog()
{
  CDialog::OnInitDialog();
  FillListBox();
  UpdateData(FALSE);
  return (TRUE);
}


void C3ParamPropertyPage::OnChangeDatumCode() 
{
  UpdateData(TRUE);
  m_datum_code_value = LPCTSTR (m_datum_code);	
}


void C3ParamPropertyPage::OnChangeDatumName() 
{
  UpdateData(TRUE);
  m_datum_name_value = LPCTSTR (m_datum_name);	
}


void C3ParamPropertyPage::OnChangeDatumDeltax() 
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


void C3ParamPropertyPage::OnChangeDatumDeltay() 
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


void C3ParamPropertyPage::OnChangeDatumDeltaz() 
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


void C3ParamPropertyPage::OnChangeDatumSigmax() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_SIGMAX);
  double temp_val;
  if (String_to_Double(m_sigmaX,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_sigmaX_value = temp_val;
  }
}


void C3ParamPropertyPage::OnChangeDatumSigmay() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_SIGMAY);
  double temp_val;
  if (String_to_Double(m_sigmaY,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_sigmaY_value = temp_val;
  }
}


void C3ParamPropertyPage::OnChangeDatumSigmaz() 
{
  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_SIGMAZ);
  double temp_val;
  if (String_to_Double(m_sigmaZ,&temp_val))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_sigmaZ_value = temp_val;
  }
}


void C3ParamPropertyPage::OnSelchangeDatumEllipsoidCombobox() 
{
   CWnd* wPtr = GetDlgItem(IDC_DATUM_ELLIPSOID_COMBOBOX);
   m_ellipsoid_index = ((CComboBox*)wPtr)->GetCurSel( );
 
   UpdateData(FALSE);
}


void C3ParamPropertyPage::OnChangeDatumEastLon() 
{
  UpdateData(TRUE);
  double temp_val;
  int error_code = String_to_Longitude(m_east_lon,&temp_val);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_EAST_LON);
  if (error_code)
  {
    int start, end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_east_lon_value = temp_val * (PI/180);
  }
}


void C3ParamPropertyPage::OnChangeDatumNorthLat() 
{
  UpdateData(TRUE);
  double temp_val;
  int error_code = String_to_Latitude(m_north_lat,&temp_val);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_NORTH_LAT);
  if (error_code)
  {
    int start, end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_north_lat_value = temp_val * (PI/180);
  }
}


void C3ParamPropertyPage::OnChangeDatumSouthLat() 
{
  UpdateData(TRUE);
  double temp_val;
  int error_code = String_to_Latitude(m_south_lat,&temp_val);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_SOUTH_LAT);
  if (error_code)
  {
    int start, end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_south_lat_value = temp_val * (PI/180);
  }
}


void C3ParamPropertyPage::OnChangeDatumWestLon() 
{
  UpdateData(TRUE);
  double temp_val;
  int error_code = String_to_Longitude(m_west_lon,&temp_val);
  CWnd* pWnd = GetDlgItem(IDC_DATUM_WEST_LON);
  if (error_code)
  {
    int start, end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    m_west_lon_value = temp_val * (PI/180);
  }
}


/*BOOL C3ParamPropertyPage::OnKillActive()
{
  char ellipsoid_code[10];

  long error_code = Get_Ellipsoid_Code(m_ellipsoid_index+1, ellipsoid_code);
  error_code = Define_Datum (m_datum_code_value, m_datum_name_value, ellipsoid_code,
                             m_deltaX_value, m_deltaY_value, m_deltaZ_value,
                             m_sigmaX_value, m_sigmaY_value, m_sigmaZ_value,
                             m_south_lat_value, m_north_lat_value, m_west_lon_value, m_east_lon_value);
  if (!error_code) 
  if( close_property_page )
    return TRUE;
  else
    return FALSE;*/
    //CPropertyPage::OnOK();
 /* else
  {
    char err_str[256];
    char temp_err_str[256];
    sprintf(err_str,"Error:\n");
    Get_Return_Code_String(error_code,"\n",temp_err_str);
    strcat(err_str, temp_err_str);
    AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
    return FALSE;
  }
}*/


/*void C3ParamPropertyPage::OnOK() 
{
  char ellipsoid_code[10];

  //if( !close_property_page )
  //  close_property_page = true;

  long error_code = Get_Ellipsoid_Code(m_ellipsoid_index+1, ellipsoid_code);
  error_code = Define_Datum (m_datum_code_value, m_datum_name_value, ellipsoid_code,
                             m_deltaX_value, m_deltaY_value, m_deltaZ_value,
                             m_sigmaX_value, m_sigmaY_value, m_sigmaZ_value,
                             m_south_lat_value, m_north_lat_value, m_west_lon_value, m_east_lon_value);
  if (!error_code) 
    CPropertyPage::OnOK();
  else
  {
    char err_str[256];
    char temp_err_str[256];
    sprintf(err_str,"Error:\n");
    Get_Return_Code_String(error_code,"\n",temp_err_str);
    strcat(err_str, temp_err_str);
    AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
    close_property_page = false;
    //C3ParamPropertyPage::OnKillActive();
   // close_property_page = true;
   // C3ParamPropertyPage::OnKillActive();
    CPropertyPage::OnOK();
  }
}*/


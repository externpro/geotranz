// mastervw.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "mastervw.h"
#include "engine.h"
#include "strtoval.h"
#include "source.h"
//#include "filevw.h"
//#include "datumvw.h"
//#include "ellipsevw.h"
//#include "delellipvw.h"
//#include "deldatumvw.h"
#include "mainfrm.h"
#include "geotrdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMasterView

IMPLEMENT_DYNCREATE(CMasterView, CFormView)

CMasterView::CMasterView()
  : CFormView(CMasterView::IDD)
{
  //{{AFX_DATA_INIT(CMasterView)
  m_datum_combobox = _T("");
  m_edit1_str = _T("");
  m_edit2_str = _T("");
  m_edit3_str = _T("");
  m_edit5_str = _T("");
  m_edit7_str = _T("");
  m_edit8_str = _T("");
  m_edit9_str = _T("");
  m_edit21_str = _T("");
  m_edit22_str = _T("");
  m_edit23_str = _T("");
  m_edit24_str = _T("");
  m_edit25_str = _T("");
  m_edit26_str = _T("");
  m_edit27_str = _T("");
  m_edit28_str = _T("");
  m_edit29_str = _T("");
  m_edit30_str = _T("");
  m_static1_str = _T("");
  m_static2_str = _T("");
  m_static3_str = _T("");
  m_static5_str = _T("");
  m_static7_str = _T("");
  m_static8_str = _T("");
  m_static9_str = _T("");
  m_static21_str = _T("");
  m_static22_str = _T("");
  m_static23_str = _T("");
  m_static24_str = _T("");
  m_static25_str = _T("");
  m_static26_str = _T("");
  m_static27_str = _T("");
  m_static28_str = _T("");
  m_static29_str = _T("");  
  m_static30_str = _T("");
  m_ellipsoid_edit = _T("");
  m_errsrc = _T("");
  m_ups_hemi_n = -1;
  m_zone_edit_str = _T("");
  m_ce90_str = _T("");
  m_le90_str = _T("N/A");
  m_se90_str = _T("N/A");
  m_edit_coord_str = _T("");
  m_static_coord_str = _T("");
  usePrevAccuracies = false;
  //}}AFX_DATA_INIT

  _3dConversion = false;
}

CMasterView::~CMasterView()
{
}

void CMasterView::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CMasterView)
  DDX_Control(pDX, IDC_HEIGHT_COMBOBOX, m_height_combobox);
  DDX_CBString(pDX, IDC_DATUM_COMBOBOX, m_datum_combobox);
  DDX_Text(pDX, IDC_EDIT1, m_edit1_str);
  DDX_Text(pDX, IDC_EDIT2, m_edit2_str);
  DDX_Text(pDX, IDC_EDIT3, m_edit3_str);
  DDX_Text(pDX, IDC_EDIT5, m_edit5_str);
  DDX_Text(pDX, IDC_EDIT7, m_edit7_str);
  DDX_Text(pDX, IDC_EDIT8, m_edit8_str);
  DDX_Text(pDX, IDC_EDIT9, m_edit9_str);
  DDX_Text(pDX, IDC_EDIT21, m_edit21_str);
  DDX_Text(pDX, IDC_EDIT22, m_edit22_str);
  DDX_Text(pDX, IDC_EDIT23, m_edit23_str);
  DDX_Text(pDX, IDC_EDIT24, m_edit24_str);
  DDX_Text(pDX, IDC_EDIT25, m_edit25_str);
  DDX_Text(pDX, IDC_EDIT26, m_edit26_str);
  DDX_Text(pDX, IDC_EDIT27, m_edit27_str);
  DDX_Text(pDX, IDC_EDIT28, m_edit28_str);
  DDX_Text(pDX, IDC_EDIT29, m_edit29_str);
  DDX_Text(pDX, IDC_EDIT30, m_edit30_str);
  DDX_Text(pDX, IDC_STATIC1, m_static1_str);
  DDX_Text(pDX, IDC_STATIC2, m_static2_str);
  DDX_Text(pDX, IDC_STATIC3, m_static3_str);
  DDX_Text(pDX, IDC_STATIC5, m_static5_str);
  DDX_Text(pDX, IDC_STATIC7, m_static7_str);
  DDX_Text(pDX, IDC_STATIC8, m_static8_str);
  DDX_Text(pDX, IDC_STATIC9, m_static9_str);
  DDX_Text(pDX, IDC_STATIC21, m_static21_str);
  DDX_Text(pDX, IDC_STATIC22, m_static22_str);
  DDX_Text(pDX, IDC_STATIC23, m_static23_str);
  DDX_Text(pDX, IDC_STATIC24, m_static24_str);
  DDX_Text(pDX, IDC_STATIC25, m_static25_str);
  DDX_Text(pDX, IDC_STATIC26, m_static26_str);
  DDX_Text(pDX, IDC_STATIC27, m_static27_str);
  DDX_Text(pDX, IDC_STATIC28, m_static28_str);
  DDX_Text(pDX, IDC_STATIC29, m_static29_str);  
  DDX_Text(pDX, IDC_STATIC30, m_static30_str);
  DDX_Text(pDX, IDC_ELLIPSOID_EDIT, m_ellipsoid_edit);
  DDX_CBString(pDX, IDC_ERRSRC, m_errsrc);
  DDX_Radio(pDX, IDC_UPS_HEMI_N, m_ups_hemi_n);
  DDX_Text(pDX, IDC_ZONE_EDIT, m_zone_edit_str);
  DDX_Text(pDX, ID_CE90, m_ce90_str);
  DDX_Text(pDX, ID_LE90, m_le90_str);
  DDX_Text(pDX, ID_SE90, m_se90_str);
  DDX_Text(pDX, IDC_EDIT_COORDSTR, m_edit_coord_str);
  DDX_Text(pDX, IDC_STATIC_COORDSTR, m_static_coord_str);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMasterView, CFormView)
  //{{AFX_MSG_MAP(CMasterView)
ON_WM_CTLCOLOR()
ON_CBN_SELCHANGE(IDC_SELECT_PROJECTION, OnSelchangeSelectProjection)
ON_CBN_SELCHANGE(IDC_DATUM_COMBOBOX, OnSelchangeDatumCombobox)
ON_CBN_SELCHANGE(IDC_ERRSRC, OnSelchangeErrsrc)
ON_BN_CLICKED(IDC_UPS_HEMI_N, OnHemiN)
ON_BN_CLICKED(IDC_UPS_HEMI_S, OnHemiS)
ON_BN_CLICKED(IDC_SET_ZONE_BUTTON, OnSetUtmZone)
ON_BN_CLICKED(IDC_STD_PARALLEL1_71, OnStdParallel71)
ON_BN_CLICKED(IDC_STD_PARALLEL1_74, OnStdParallel74)
ON_EN_CHANGE(ID_CE90, OnChangeCE90)
ON_EN_CHANGE(ID_LE90, OnChangeLE90)
ON_EN_CHANGE(ID_SE90, OnChangeSE90)
  ON_CBN_SELCHANGE(IDC_HEIGHT_COMBOBOX, OnSelchangeHeightCombobox)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMasterView diagnostics

#ifdef _DEBUG
void CMasterView::AssertValid() const
{
  CFormView::AssertValid();
}

void CMasterView::Dump(CDumpContext& dc) const
{
  CFormView::Dump(dc);
}

CGeotransDoc* CMasterView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeotransDoc)));
  return (CGeotransDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMasterView message handlers
void CMasterView::OnSelchangeSelectProjection() 
{
  Initialize_Form();
  ((CMainFrame*)GetParentFrame())->Check_3D_Conversion();
  ((CMainFrame*)GetParentFrame())->Check_Valid_Conversion();
}

HBRUSH CMasterView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
  if (nCtlColor == CTLCOLOR_EDIT)
  {
    return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
  }
  else
  {
    if (pWnd->GetDlgCtrlID() == IDC_SELECT_PROJECTION)
      return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
    CMainFrame* pMainFrame = (CMainFrame*)GetParentFrame();
    pDC->SetBkColor(pMainFrame->GetBackgroundColor());
    pDC->SetTextColor(pMainFrame->GetTextColor());
    return pMainFrame->GetBackgroundBrush();
  }
}

void CMasterView::OnSelchangeDatumCombobox() 
{

  CWnd* wPtr = GetDlgItem(IDC_DATUM_COMBOBOX);
  datum_index = ((CComboBox*)wPtr)->GetCurSel( ) + 1;

  char code[10];
  long error_code = Get_Datum_Code(datum_index,code);
  sprintf(code,"%s:",code);

  char name[40];
  error_code = Get_Datum_Name(datum_index,name);

  char full_name[50];
  sprintf(full_name,"%-8s%s",code,name);
  m_datum_combobox = full_name;

  error_code =  Get_Datum_Ellipsoid_Code ( datum_index, code );
  long ell_index;
  error_code = Get_Ellipsoid_Index ( code, &ell_index );
  error_code = Get_Ellipsoid_Name ( ell_index, name );
  sprintf(full_name,"%s: %s",code,name);
  m_ellipsoid_edit = full_name;

  ((CMainFrame*)GetParentFrame())->Check_Valid_Conversion();

  UpdateData(FALSE);
}

void CMasterView::FillListBox()
{
  long count;

  long error_code = Get_Datum_Count(&count);
  if (error_code)
    AfxMessageBox("Error getting datum count!",MB_OK | MB_ICONEXCLAMATION);
  else
  {
    CWnd* wPtr = GetDlgItem(IDC_DATUM_COMBOBOX);
    ((CComboBox*)wPtr)->ResetContent();    

    for (int i = 0; i < count; i++)
    {
      char datum_code[10];
      error_code = Get_Datum_Code(i+1,datum_code);
      sprintf(datum_code,"%s:",datum_code);

      char datum_name[40];
      error_code = Get_Datum_Name(i+1,datum_name);

      char datum_full_name[50];
      sprintf(datum_full_name,"%-8s%s",datum_code,datum_name);

      ((CComboBox*)wPtr)->AddString(datum_full_name);
    }
    ((CComboBox*)wPtr)->SetCurSel(0);
    datum_index = 1;
    OnSelchangeDatumCombobox();
  }
}


void CMasterView::FillSourcesListBox()
{
  long count;

  Source_Count(&count);
  CWnd* wPtr = GetDlgItem(IDC_ERRSRC);
  ((CComboBox*)wPtr)->ResetContent();    

  for (int i=0; i < count; i++)
  {
    char source_name[51];
    long error_code = Source_Name(i+1,source_name);
    if (error_code)
      AfxMessageBox("Error getting source name!",MB_OK | MB_ICONEXCLAMATION);
    else
      ((CComboBox*)wPtr)->AddString(source_name);
  }
  ((CComboBox*)wPtr)->SetCurSel(0);
  OnSelchangeErrsrc();
}


void CMasterView::OnSelchangeErrsrc() 
{
  CWnd *pWnd;
  char str[15];

  CWnd* wPtr = GetDlgItem(IDC_ERRSRC);
  long source_index = ((CComboBox*)wPtr)->GetCurSel( ) + 1;

  char name[51];
  long error_code = Source_Name(source_index,name);
  m_errsrc = name;

  double ce90, le90, se90;
  error_code = Source_Accuracy(source_index, &ce90, &le90, &se90);
  if (ce90 == -1.0)
  {
    pWnd = GetDlgItem(ID_CE90);
    ((CEdit*)pWnd)->SetWindowText("Unk");
    m_ce90_str = "Unk";
  }
  else
  {
    sprintf(str,"%1.0f",ce90);
    pWnd = GetDlgItem(ID_CE90);
    ((CEdit*)pWnd)->SetWindowText(str);
    m_ce90_str = str;
  }
  if (!_3dConversion)
  {
    pWnd = GetDlgItem(ID_LE90);
    ((CEdit*)pWnd)->SetWindowText("N/A");
    m_le90_str = "N/A";
    pWnd = GetDlgItem(ID_SE90);
    ((CEdit*)pWnd)->SetWindowText("N/A");
    m_se90_str = "N/A";
  }
  else
  {
    if (le90 == -1.0)
    {
      pWnd = GetDlgItem(ID_LE90);
      ((CEdit*)pWnd)->SetWindowText("Unk");
      m_le90_str = "Unk";
    }
    else
    {
      sprintf(str,"%1.0f",le90);
      pWnd = GetDlgItem(ID_LE90);
      ((CEdit*)pWnd)->SetWindowText(str);
      m_le90_str = str;
    }
    if (se90 == -1.0)
    {
      pWnd = GetDlgItem(ID_SE90);
      ((CEdit*)pWnd)->SetWindowText("Unk");
      m_se90_str = "Unk";
    }
    else
    {
      sprintf(str,"%1.0f",se90);
      pWnd = GetDlgItem(ID_SE90);
      ((CEdit*)pWnd)->SetWindowText(str);
      m_se90_str = str;
    }
  }

  usePrevAccuracies = false;
  UpdateData(TRUE);
}

// Set geodetic format
void CMasterView::SetFormat(int in_format)
{
  format = in_format;
}


// Set sign/hemisphere option
void CMasterView::SetHemiFlag(int hFlag)
{
  hemiFlag = hFlag;
}

//________________________________________________
//________________________________________________
//______________New Functions.____________________
//________________________________________________
//________________________________________________
// This function is called to set the engine with GUI values.
int CMasterView::GetParams( Input_Output dir )
{
  int status = 0;
  char err_str[256];

  UpdateData(TRUE); 
  /* get parameters */
  if (!f16GRS)
  {
    switch (type)
    {
    case Albers_Equal_Area_Conic:
      {
        // Layout 4*2*2
        Albers_Equal_Area_Conic_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit21_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit22_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Latitude(m_edit23_str,&temp_val);
        params.std_parallel_1 = temp_val*PI/180;
        int error4 = String_to_Latitude(m_edit24_str,&temp_val);
        params.std_parallel_2 = temp_val*PI/180;
        int error5 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error6 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5 || error6)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid 1st Standard Parallel","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid 2nd Standard Parallel","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error6)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Albers_Equal_Area_Conic_Params(Interactive,dir,params);
        break;
      }
    case Azimuthal_Equidistant:
      {
        // Layout 2*2*2
        Azimuthal_Equidistant_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else   
        Set_Azimuthal_Equidistant_Params(Interactive,dir,params);
        break;
      }
    case Bonne:
      {
        // Layout 2*2*2
        Bonne_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Bonne_Params(Interactive,dir,params);
        break;
      }
    case BNG:
      {
        // Layout:0*0*1
        // no params
        break;
      }
    case Cassini:
      {
        // Layout 2*2*2
        Cassini_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Cassini_Params(Interactive,dir,params);
        break;
      }
    case Cylindrical_Equal_Area:
      {
        // Layout 2*2*2
        Cylindrical_Equal_Area_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Cylindrical_Equal_Area_Params(Interactive,dir,params);
        break;
      }
    case Eckert4:
      {
        // Layout 1*2*2
        Eckert4_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit2_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error3 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Eckert4_Params(Interactive,dir,params);
        break;
      }
    case Eckert6:
      {
        // Layout 1*2*2
        Eckert6_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit2_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error3 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Eckert6_Params(Interactive,dir,params);
        break;
      }
    case Equidistant_Cylindrical:
      {
        // Layout 2*2*2
        Equidistant_Cylindrical_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.std_parallel = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Standard Parallel","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Equidistant_Cylindrical_Params(Interactive,dir,params);
        break;
      }
    case Geocentric:
      {
        // Layout:0*0*3
        // no params
        break;
      }
    case Geodetic:
      {
        // Layout:0*0*3   
        // height type
        Geodetic_Parameters params;
        params.height_type = (Height_Types)geo_height;
        Set_Geodetic_Params(Interactive,dir,params);
        break;
      }
    case GARS:
    case GEOREF:
      {
        // Layout: 0*0*1
        // no params
        break;
      }
    case Gnomonic:
      {
        // Layout: 2*2*2
        Gnomonic_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Gnomonic_Params(Interactive,dir,params);
        break;
      }
    case Lambert_Conformal_Conic_1:
      {
        // Layout: 3*2*2
        Lambert_Conformal_Conic_1_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit1_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit2_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit3_str,&temp_val);
        params.scale_factor = temp_val;
        int error4 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error5 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Scale Factor","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
        Set_Lambert_Conformal_Conic_1_Params(Interactive,dir,params);
        break;
      }
    case Lambert_Conformal_Conic_2:
      {
        // Layout: 4*2*2
        Lambert_Conformal_Conic_2_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit21_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit22_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Latitude(m_edit23_str,&temp_val);
        params.std_parallel_1 = temp_val*PI/180;
        int error4 = String_to_Latitude(m_edit24_str,&temp_val);
        params.std_parallel_2 = temp_val*PI/180;
        int error5 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error6 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5 || error6)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid 1st Standard Parallel","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid 2nd Standard Parallel","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error6)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Lambert_Conformal_Conic_2_Params(Interactive,dir,params);
        break;
      }
    case Local_Cartesian:
      {
        // Layout: 3*1*3
        Local_Cartesian_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit1_str,&temp_val);
        params.origin_longitude = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit2_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit3_str,&temp_val);
        params.origin_height = temp_val;
        int error4 = String_to_Longitude(m_edit5_str,&temp_val);
        params.orientation = temp_val*PI/180;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Origin Longitude","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Origin Height","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid Orientation","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
        Set_Local_Cartesian_Params(Interactive,dir,params);
        break;
      }     
    case Mercator:
      {
        // Layout: 3*2*2
        Mercator_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit1_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit2_str,&temp_val);
        params.latitude_of_true_scale = temp_val*PI/180;
        int error3 = String_to_Double(m_edit3_str,&temp_val);
        params.scale_factor = temp_val;
        int error4 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error5 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Latitude of True Scale","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Scale Factor","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
        Set_Mercator_Params(Interactive,dir,params);
        break;
      }
    case MGRS:
    case USNG:
      {
        // Layout:0*0*1
        // no params
        break;
      }
    case Miller_Cylindrical:
      {
        // Layout:1*2*2
        Miller_Cylindrical_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit2_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error3 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Miller_Cylindrical_Params(Interactive,dir,params);
        break;
      }
    case Mollweide:
      {
        // Layout:1*2*2
        Mollweide_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit2_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error3 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Mollweide_Params(Interactive,dir,params);
        break;
      }
    case Neys:
      {
        // Layout: 4*2*2
        Neys_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit21_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit22_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = 0;     
        if (std_parallel1 == 0)
          params.std_parallel_1 = 71.0*PI/180;
        else if (std_parallel1 == 1)
          params.std_parallel_1 = 74.0*PI/180;
        else
          error3 = 1;

        int error4 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error5 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid 1st Standard Parallel","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Neys_Params(Interactive,dir,params);
        break;
      }
    case NZMG:
      {
        // Layout:0*0*2
        // no params
        break;
      }
   case Oblique_Mercator:
      {
        // Layout:4*4*2
        Oblique_Mercator_Parameters params;
        double temp_val;
        int error1 = String_to_Latitude(m_edit21_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error2 = String_to_Double(m_edit22_str,&temp_val);
        params.scale_factor = temp_val;
        int error3 = String_to_Longitude(m_edit23_str,&temp_val);
        params.longitude_1 = temp_val*PI/180;
        int error4 = String_to_Latitude(m_edit24_str,&temp_val);
        params.latitude_1 = temp_val*PI/180;
        int error5 = String_to_Longitude(m_edit25_str,&temp_val);
        params.longitude_2 = temp_val*PI/180;
        int error6 = String_to_Latitude(m_edit26_str,&temp_val);
        params.latitude_2 = temp_val*PI/180;
        int error7 = String_to_Double(m_edit27_str,&temp_val);
        params.false_easting = temp_val;
        int error8 = String_to_Double(m_edit28_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5 || error6 || error7 || error8)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Scale Factor","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Longitude 1","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid Latitude 1","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid Longitude 2","\n",temp_err_str);
          if (error6)
            Error_Append("Invalid Latitude 2","\n",temp_err_str);
          if (error7)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error8)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
        Set_Oblique_Mercator_Params(Interactive,dir,params);
        break;
      }
    case Orthographic:
      {
        // Layout:2*2*2
        Orthographic_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Orthographic_Params(Interactive,dir,params);
        break;
      }
    case Polar_Stereo:
      {
        // Layout:2*2*2
        Polar_Stereo_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.longitude_down_from_pole = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.latitude_of_true_scale = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid longitude down from pole","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid latitude of true scale","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Polar_Stereo_Params(Interactive,dir,params);
        break;
      }
    case Polyconic:
      {
        // Layout:2*2*2
        Polyconic_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Polyconic_Params(Interactive,dir,params);
        break;
      }
    case Sinusoidal:
      {
        // Layout:1*2*2
        Sinusoidal_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit2_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error3 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Sinusoidal_Params(Interactive,dir,params);
        break;

      }
    case Stereographic:
      {
        // Layout 2*2*2
        Stereographic_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit22_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit23_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error4 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else   
        Set_Stereographic_Params(Interactive,dir,params);
        break;
      }
    case Transverse_Cylindrical_Equal_Area:
      {
        // Layout:3*2*2
        Transverse_Cylindrical_Equal_Area_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit1_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit2_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit3_str,&temp_val);
        params.scale_factor = temp_val;
        int error4 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error5 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Scale Factor","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
        Set_Transverse_Cylindrical_Equal_Area_Params(Interactive,dir,params);
        break;
      }
    case Transverse_Mercator:
      {
        // Layout:3*2*2
        Transverse_Mercator_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit1_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit2_str,&temp_val);
        params.origin_latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit3_str,&temp_val);
        params.scale_factor = temp_val;
        int error4 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error5 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3 || error4 || error5)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Origin Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Scale Factor","\n",temp_err_str);
          if (error4)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error5)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
        Set_Transverse_Mercator_Params(Interactive,dir,params);
        break;
      }
    case UPS:
      {
        // Layout:0*0*2
        // Hemisphere
        break; 
      }
    case UTM:
      {
        // Layout:0*0*2
        // Hemisphere
        // Zone
        UTM_Parameters params;
        double temp_val;
        int error1 = 0;
        if (tog_check)
        {
          params.override = 1;
          error1 = String_to_Double(m_zone_edit_str,&temp_val);
          if (!(temp_val < 1) || (temp_val > 60))
            params.zone = (long)temp_val;
          else
            error1 = 1;
        }
        else
        {
          params.override = 0;
          params.zone = 0;
        }
        if (error1)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          Error_Append("Invalid Zone","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_UTM_Params(Interactive,dir,params);
        break; 
      }
    case Van_der_Grinten:
      {
        //Layout: 1*2*2
        Van_der_Grinten_Parameters params;
        double temp_val;
        int error1 = String_to_Longitude(m_edit2_str,&temp_val);
        params.central_meridian = temp_val*PI/180;
        int error2 = String_to_Double(m_edit26_str,&temp_val);
        params.false_easting = temp_val;
        int error3 = String_to_Double(m_edit27_str,&temp_val);
        params.false_northing = temp_val;
        if(error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Central Meridian","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid False Easting","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid False Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else 
        Set_Van_der_Grinten_Params(Interactive,dir,params);
        break;
      }

    } // end of switch
  }
  return status;
} // End of GetParams(dir);

// -------------------------------------------------------
// -------------------------------------------------------
int CMasterView::GetCoords( Input_Output dir  )
{
/*
 * This function is called to set the engine with GUI values.
 */
  int status = 0;
  char err_str[256];
  UpdateData(TRUE);
  if (f16GRS)
  {
    // F-16 GRS

    // Layout:0*0*1
    MGRS_Tuple coord;
    int length;
    char temp[16] = "";
    length = strlen(m_edit_coord_str);
    strcpy(temp, m_edit_coord_str);
    if ((temp[length - 1] == '0') && (temp[length - 2] == '0'))
    {
      strncpy(coord.string, temp, length - 2);
      coord.string[length-2] = '\0';
    }
    else
    {
      strcpy(coord.string, temp);
      coord.string[length] = '\0';
    }

    Set_MGRS_Coordinates(Interactive,dir,coord);
  }
  else
  {
  /* get coordinates*/
    switch (type)
    {
    case Albers_Equal_Area_Conic:
      {
        // Layout 4*2*2
        Albers_Equal_Area_Conic_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Albers_Equal_Area_Conic_Coordinates(Interactive,dir,coord);
        break;
      }
    case Azimuthal_Equidistant:
      {
        // Layout 2*2*2
        Azimuthal_Equidistant_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Azimuthal_Equidistant_Coordinates(Interactive,dir,coord);
        break;
      }
    case Bonne:
      {
        // Layout 2*2*2
        Bonne_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Bonne_Coordinates(Interactive,dir,coord);
        break;
      }
    case BNG:
      {
        // Layout:0*0*1
        BNG_Tuple coord;
        strcpy(coord.string,m_edit_coord_str);
        Set_BNG_Coordinates(Interactive,dir,coord);
        break;
      }
    case Cassini:
      {
        // Layout 2*2*2
        Cassini_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Cassini_Coordinates(Interactive,dir,coord);
        break;
      }
    case Cylindrical_Equal_Area:
      {
        // Layout 2*2*2
        Cylindrical_Equal_Area_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Cylindrical_Equal_Area_Coordinates(Interactive,dir,coord);
        break;
      }
    case Eckert4:
      {
        // Layout 1*2*2
        Eckert4_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Eckert4_Coordinates(Interactive,dir,coord);
        break;
      }
    case Eckert6:
      {
        // Layout 1*2*2
        Eckert6_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Eckert6_Coordinates(Interactive,dir,coord);
        break;
      }
    case Equidistant_Cylindrical:
      {
        // Layout 2*2*2
        Equidistant_Cylindrical_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Equidistant_Cylindrical_Coordinates(Interactive,dir,coord);
        break;
      }
    case Geocentric:
      {
        // Layout:0*0*3
        Geocentric_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit7_str,&temp_val);
        coord.x = temp_val;
        int error2 = String_to_Double(m_edit8_str,&temp_val);
        coord.y = temp_val;
        int error3 = String_to_Double(m_edit9_str,&temp_val);
        coord.z = temp_val;
        if (error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid coord X","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid coord Y","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid coord Z","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Geocentric_Coordinates(Interactive,dir,coord);
        break;
      }
    case Geodetic:
      {
        // Layout:0*0*3   
        // height type
        Geodetic_Tuple coord;
        double temp_val;
        int error1 = String_to_Longitude(m_edit7_str,&temp_val);
        coord.longitude = temp_val*PI/180;
        int error2 = String_to_Latitude(m_edit8_str,&temp_val);
        coord.latitude = temp_val*PI/180;
        int error3 = String_to_Double(m_edit9_str,&temp_val);
        coord.height = temp_val;
        if (error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Longitude","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Latitude","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Height","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Geodetic_Coordinates(Interactive,dir,coord);
        break;
      }
    case GARS:
      {
        // Layout: 0*0*1
        GARS_Tuple coord;
        strcpy(coord.string, m_edit_coord_str);
        Set_GARS_Coordinates(Interactive, dir, coord);
        break;
      }
    case GEOREF:
      {
        // Layout: 0*0*1
        GEOREF_Tuple coord;
        strcpy(coord.string, m_edit_coord_str);
        Set_GEOREF_Coordinates(Interactive, dir, coord);
        break;
      }
    case Gnomonic:
      {
        // Layout: 2*2*2
        Gnomonic_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Gnomonic_Coordinates(Interactive,dir,coord);
        break;
      }
    case Lambert_Conformal_Conic_1:
      {
        // Layout: 4*2*2
        Lambert_Conformal_Conic_1_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Lambert_Conformal_Conic_1_Coordinates(Interactive,dir,coord);
        break;
      }
    case Lambert_Conformal_Conic_2:
      {
        // Layout: 4*2*2
        Lambert_Conformal_Conic_2_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Lambert_Conformal_Conic_2_Coordinates(Interactive,dir,coord);
        break;
      }
    case Local_Cartesian:
      {
        // Layout: 3*1*3
        Local_Cartesian_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit7_str,&temp_val);
        coord.x = temp_val;
        int error2 = String_to_Double(m_edit8_str,&temp_val);
        coord.y = temp_val;
        int error3 = String_to_Double(m_edit9_str,&temp_val);
        coord.z = temp_val;
        if (error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid coord X","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid coord Y","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid coord Z","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Local_Cartesian_Coordinates(Interactive,dir,coord);
        break;
      }     
    case Mercator:
      {
        // Layout: 3*2*2
        Mercator_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Mercator_Coordinates(Interactive,dir,coord);
        break;
      }
    case MGRS:
      {
        // Layout:0*0*1
        MGRS_Tuple coord;
        strcpy(coord.string,m_edit_coord_str);
        Set_MGRS_Coordinates(Interactive,dir,coord);
        break;
      }
    case Miller_Cylindrical:
      {
        // Layout:1*2*2
        Miller_Cylindrical_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Miller_Cylindrical_Coordinates(Interactive,dir,coord);
        break;
      }
    case Mollweide:
      {
        // Layout:1*2*2
        Mollweide_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Mollweide_Coordinates(Interactive,dir,coord);
        break;
      }
    case Neys:
      {
        // Layout: 4*2*2
        Neys_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Neys_Coordinates(Interactive,dir,coord);
        break;
      }
    case NZMG:
      {
        // Layout 0*0*2
        NZMG_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_NZMG_Coordinates(Interactive,dir,coord);
        break;
      }
    case Oblique_Mercator:
      {
        // Layout:4*4*2
        Oblique_Mercator_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Oblique_Mercator_Coordinates(Interactive,dir,coord);
        break;
      }
    case Orthographic:
      {
        // Layout:2*2*2
        Orthographic_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Orthographic_Coordinates(Interactive,dir,coord);
        break;
      }
    case Polar_Stereo:
      {
        // Layout:2*2*2
        Polar_Stereo_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Polar_Stereo_Coordinates(Interactive,dir,coord);
        break;
      }
    case Polyconic:
      {
        // Layout:2*2*2
        Polyconic_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Polyconic_Coordinates(Interactive,dir,coord);
        break;
      }
    case Sinusoidal:
      {
        // Layout:1*2*2
        Sinusoidal_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Sinusoidal_Coordinates(Interactive,dir,coord);
        break;
      }
    case Stereographic:
      {
        // Layout 2*2*2
        Stereographic_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Stereographic_Coordinates(Interactive,dir,coord);
        break;
      }
    case Transverse_Cylindrical_Equal_Area:
      {
        // Layout:3*2*2
        Transverse_Cylindrical_Equal_Area_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Transverse_Cylindrical_Equal_Area_Coordinates(Interactive,dir,coord);
        break;
      }
    case Transverse_Mercator:
      {
        // Layout:3*2*2
        Transverse_Mercator_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Transverse_Mercator_Coordinates(Interactive,dir,coord);
        break;
      }
    case UPS:
      {
        // Layout:0*0*2
        // Hemisphere
        UPS_Tuple coord;
        double temp_val;
        if (hemisphere_type == 0)
          coord.hemisphere = 'N';
        else
          coord.hemisphere = 'S';
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_UPS_Coordinates(Interactive,dir,coord);
        break;
      }
    case USNG:
      {
        // Layout:0*0*1
        USNG_Tuple coord;
        strcpy(coord.string,m_edit_coord_str);
        Set_USNG_Coordinates(Interactive,dir,coord);
        break;
      }
    case UTM:
      {
        // Layout:0*0*2
        // Hemisphere
        // Zone
        UTM_Tuple coord;
        double temp_val;
        if (hemisphere_type == 0)
          coord.hemisphere = 'N';
        else
          coord.hemisphere = 'S';
        int error1 = String_to_Double(m_zone_edit_str,&temp_val);
        if (!(temp_val < 0) || (temp_val > 60))
          coord.zone = (long)temp_val;
        else
          error1 = 1;
        int error2 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error3 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2 || error3)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Zone","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error3)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_UTM_Coordinates(Interactive,dir,coord);
        break;
      }
    case Van_der_Grinten:
      {
        //Layout: 1*2*2
        Van_der_Grinten_Tuple coord;
        double temp_val;
        int error1 = String_to_Double(m_edit29_str,&temp_val);
        coord.easting = temp_val;
        int error2 = String_to_Double(m_edit30_str,&temp_val);
        coord.northing = temp_val;
        if (error1 || error2)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(dir,type,"\n",temp_err_str);
          if (error1)
            Error_Append("Invalid Easting","\n",temp_err_str);
          if (error2)
            Error_Append("Invalid Northing","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
          Set_Van_der_Grinten_Coordinates(Interactive,dir,coord);
        break;
      }
    } // end of switch
  }
  return status;
} // end of GetCoords(dir);

// -------------------------------------------------------
// -------------------------------------------------------
void CMasterView::SetCoords( Input_Output dir )
{
/*
 * This function is called to set the GUI with engine values.
 */
  if (f16GRS)
  {
    // F-16 GRS
    // Layout:0*0*1
    MGRS_Tuple coord;
    Precision precis;

    Get_MGRS_Coordinates(Interactive,dir,&coord);
    Get_Precision(&precis);
    if (precis == Degree)
      strcat(coord.string, "00");
    m_edit_coord_str = coord.string;
    UpdateData(FALSE);    
  }
  else
  {
    char buf[50];
    switch (type)
    {
    case Albers_Equal_Area_Conic:
      {
        // Layout 4*2*2
        Albers_Equal_Area_Conic_Tuple coord;
        Get_Albers_Equal_Area_Conic_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Azimuthal_Equidistant:
      {
        // Layout 2*2*2
        Azimuthal_Equidistant_Tuple coord;
        Get_Azimuthal_Equidistant_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Bonne:
      {
        // Layout 2*2*2
        Bonne_Tuple coord;
        Get_Bonne_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case BNG:
      {
        // Layout:0*0*1
        BNG_Tuple coord;
        Get_BNG_Coordinates(Interactive,dir,&coord);
        /* setting string */
        m_edit_coord_str = coord.string;
        UpdateData(FALSE);    
        break;
      }
    case Cassini:
      {
        // Layout 2*2*2
        Cassini_Tuple coord;
        Get_Cassini_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);
        break;
      }
    case Cylindrical_Equal_Area:
      {
        // Layout 2*2*2
        Cylindrical_Equal_Area_Tuple coord;
        Get_Cylindrical_Equal_Area_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Eckert4:
      {
        // Layout 1*2*2
        Eckert4_Tuple coord;
        Get_Eckert4_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Eckert6:
      {
        // Layout 1*2*2
        Eckert6_Tuple coord;
        Get_Eckert6_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Equidistant_Cylindrical:
      {
        // Layout 2*2*2
        Equidistant_Cylindrical_Tuple coord;
        Get_Equidistant_Cylindrical_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Geocentric:
      {
        // Layout:0*0*3
        Geocentric_Tuple coord;
        Get_Geocentric_Coordinates(Interactive,dir,&coord);
        /* setting X */
        Meter_to_String(coord.x, buf);
        m_edit7_str = buf;
        /* setting Y */
        Meter_to_String(coord.y, buf);
        m_edit8_str = buf;
        /* setting Z */
        Meter_to_String(coord.z, buf);
        m_edit9_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Geodetic:
      {
        Geodetic_Tuple coord;
        Get_Geodetic_Coordinates(Interactive,dir,&coord);
        char lat_str[14],lon_str[15];

        double lat_val = coord.latitude;
        double long_val = coord.longitude;

        use_NSEW = (hemiFlag == NSEW) ? TRUE : FALSE;
        use_Minutes = (format != DD) ? TRUE : FALSE;
        use_Seconds = (format == DMS) ? TRUE : FALSE;

        Longitude_to_String((long_val*180)/PI, lon_str, use_NSEW, use_Minutes, use_Seconds);
        Latitude_to_String((lat_val*180)/PI, lat_str, use_NSEW, use_Minutes, use_Seconds);
        m_edit7_str = lon_str;
        m_edit8_str  = lat_str;
        Meter_to_String(coord.height, buf);
        m_edit9_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case GARS:
      {
        // Layout: 0*0*1
        GARS_Tuple coord;
        Get_GARS_Coordinates(Interactive,dir,&coord);
        /* setting string */
        m_edit_coord_str = coord.string;
        UpdateData(FALSE);    
        break;
      }
    case GEOREF:
      {
        // Layout: 0*0*1
        GEOREF_Tuple coord;
        Get_GEOREF_Coordinates(Interactive,dir,&coord);
        /* setting string */
        m_edit_coord_str = coord.string;
        UpdateData(FALSE);    
        break;
      }
    case Gnomonic:
      {
        // Layout: 2*2*2
        Gnomonic_Tuple coord;
        Get_Gnomonic_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Lambert_Conformal_Conic_1:
      {
        // Layout: 3*2*2
        Lambert_Conformal_Conic_1_Tuple coord;
        Get_Lambert_Conformal_Conic_1_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Lambert_Conformal_Conic_2:
      {
        // Layout: 4*2*2
        Lambert_Conformal_Conic_2_Tuple coord;
        Get_Lambert_Conformal_Conic_2_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Local_Cartesian:
      {
        // Layout: 3*1*3
        Local_Cartesian_Tuple coord;
        Get_Local_Cartesian_Coordinates(Interactive,dir,&coord);
        /* setting X */
        Meter_to_String(coord.x, buf);
        m_edit7_str = buf;
        /* setting Y */
        Meter_to_String(coord.y, buf);
        m_edit8_str = buf;
        /* setting Z */
        Meter_to_String(coord.z, buf);
        m_edit9_str = buf;
        UpdateData(FALSE);    
        break;
      }     
    case Mercator:
      {
        // Layout: 3*2*2
        Mercator_Tuple coord;
        Get_Mercator_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
      /* setting scale factor */
        Mercator_Parameters params;
        Get_Mercator_Params(Interactive,dir,&params);
        sprintf(buf,"%1.5lf", params.scale_factor);
        m_edit3_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case MGRS:
      {
        // Layout:0*0*1
        MGRS_Tuple coord;
        Get_MGRS_Coordinates(Interactive,dir,&coord);
        /* setting string */
        m_edit_coord_str = coord.string;
        UpdateData(FALSE);    
        break;
      }
    case Miller_Cylindrical:
      {
        // Layout:1*2*2
        Miller_Cylindrical_Tuple coord;
        Get_Miller_Cylindrical_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Mollweide:
      {
        // Layout:1*2*2
        Mollweide_Tuple coord;
        Get_Mollweide_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Neys:
      {
        // Layout: 4*2*2
        Neys_Tuple coord;
        Get_Neys_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case NZMG:
      {
        // Layout 0*0*2
        NZMG_Tuple coord;
        Get_NZMG_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Oblique_Mercator:
    {
       //Layout:4*4*2
       Oblique_Mercator_Tuple coord;
       Get_Oblique_Mercator_Coordinates(Interactive,dir,&coord);
      /* setting easting */
       Meter_to_String(coord.easting, buf);
       m_edit29_str = buf;
      /* setting northing */
       Meter_to_String(coord.northing, buf);
       m_edit30_str = buf;
       UpdateData(FALSE);   
       break;
    }
    case Orthographic:
      {
        // Layout:2*2*2
        Orthographic_Tuple coord;
        Get_Orthographic_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Polar_Stereo:
      {
        // Layout:2*2*2
        Polar_Stereo_Tuple coord;
        Get_Polar_Stereo_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Polyconic:
      {
        // Layout:2*2*2
        Polyconic_Tuple coord;
        Get_Polyconic_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Sinusoidal:
      {
        // Layout:1*2*2
        Sinusoidal_Tuple coord;
        Get_Sinusoidal_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Stereographic:
      {
        // Layout 2*2*2
        Stereographic_Tuple coord;
        Get_Stereographic_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Transverse_Cylindrical_Equal_Area:
      {
        // Layout:3*2*2
        Transverse_Cylindrical_Equal_Area_Tuple coord;
        Get_Transverse_Cylindrical_Equal_Area_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Transverse_Mercator:
      {
        // Layout:3*2*2
        Transverse_Mercator_Tuple coord;
        Get_Transverse_Mercator_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case UPS:
      {
        // Layout:0*0*2
        // Hemisphere
        UPS_Tuple coord;
        Get_UPS_Coordinates(Interactive,dir,&coord);
  //      CWnd* pWnd;
        if (coord.hemisphere == 'N')
        {
          hemisphere_type = 0;
          m_ups_hemi_n = 0;
        }
        else
        {
          hemisphere_type = 1;
          m_ups_hemi_n = 1;
        }
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case USNG:
      {
        // Layout:0*0*1
        USNG_Tuple coord;
        Get_USNG_Coordinates(Interactive,dir,&coord);
        /* setting string */
        m_edit_coord_str = coord.string;
        UpdateData(FALSE);    
        break;
      }
    case UTM:
      {
        // Layout:0*0*2
        // Hemisphere
        // Zone
        UTM_Tuple coord;
  //      CWnd* pWnd;
        Get_UTM_Coordinates(Interactive,dir,&coord);
        if (coord.hemisphere == 'N')
        {
          hemisphere_type = 0;
          m_ups_hemi_n = 0;
        }
        else
        {
          hemisphere_type = 1;
          m_ups_hemi_n = 1;
        }
        sprintf(buf,"%1.0ld",coord.zone);
        m_zone_edit_str = buf;
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }
    case Van_der_Grinten:
      {
        //Layout: 1*2*2
        Van_der_Grinten_Tuple coord;
        Get_Van_der_Grinten_Coordinates(Interactive,dir,&coord);
        /* setting easting */
        Meter_to_String(coord.easting, buf);
        m_edit29_str = buf;
        /* setting northing */
        Meter_to_String(coord.northing, buf);
        m_edit30_str = buf;
        UpdateData(FALSE);    
        break;
      }

    }// end of Switch()
  }
}// end of SetCoords()

// -------------------------------------------------------
// -------------------------------------------------------
// This function fills the height drop down combo box.
void CMasterView::FillHeightList()
{
  m_height_combobox.AddString( "No Height" );
  m_height_combobox.AddString( "Ellipsoid Height" );
  m_height_combobox.AddString( "MSL-EGM96-15M-BL Height (recommended)" );
  m_height_combobox.AddString( "MSL-EGM96-VG-NS Height" );
  m_height_combobox.AddString( "MSL-EGM84-10D-BL Height" );
  m_height_combobox.AddString( "MSL-EGM84-10D-NS Height" );

  m_height_combobox.SetCurSel( 0 );
}

// -------------------------------------------------------
// -------------------------------------------------------
// This function fills the projection drop down list box.
void CMasterView::FillProjectionList( Coordinate_Type type )
{
  //long error_code, i;
  long count;
 // char system_name[50];
 // CWnd *wPtr;

  long error_code = Get_Coordinate_System_Count(&count);
  if (error_code)
    MessageBox("Error getting coordinate system count!",NULL,MB_OK);
  else
  {
    UpdateData(TRUE);
  /*Get ptr to projection list..projection list 
    only manipulated by calling SetCurSel with
    desired projection type.*/
    CWnd* wPtr = GetDlgItem(IDC_SELECT_PROJECTION);
    for (int i=0; i < count; i++)
    {
      char system_name[50];
      error_code = Get_Coordinate_System_Name(i+1,system_name);
      ((CComboBox*)wPtr)->AddString(system_name);
    }
    ((CComboBox*)wPtr)->AddString("F-16 Grid Reference System");
    ((CComboBox*)wPtr)->SetCurSel((long)type);
    OnSelchangeSelectProjection();
  }
}

// -------------------------------------------------------
// -------------------------------------------------------
void CMasterView::Initialize_Form(void)
{
  // TODO: Add your control notification handler code here
  //CWnd *pWnd;
 // long system_index;
 // long error_code;
 // char longitude[15];
 // char latitude[14];

  use_NSEW = (hemiFlag == NSEW) ? TRUE : FALSE;
  use_Minutes = (format != DD) ? TRUE : FALSE;
  use_Seconds = (format == DMS) ? TRUE : FALSE;

  UpdateData(TRUE);
  CWnd* pWnd = GetDlgItem(IDC_SELECT_PROJECTION);
  long system_index = ((CComboBox*)pWnd)->GetCurSel() + 1;

  long error_code = Get_Coordinate_System_Type (system_index, &type);
  /* Hide general-purpose output edit fields */
  pWnd = GetDlgItem(IDC_EDIT1);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC1);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT2);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC2);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT3);
  pWnd->ShowWindow(SW_HIDE);
  // Initialize. Set to READ only for Mercator scale factor
  ((CEdit*)pWnd)->SetReadOnly(FALSE); 
  pWnd = GetDlgItem(IDC_STATIC3);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT5);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC5);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT7);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC7);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT8);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC8);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT9);
  pWnd->ShowWindow(SW_HIDE);
  ((CEdit*)pWnd)->SetReadOnly(FALSE); 
  // Initialize. Set to READ only for Geodetic "No Height."
  pWnd = GetDlgItem(IDC_STATIC9);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT21);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC21);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT22);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC22);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT23);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC23);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT24);
  pWnd->ShowWindow(SW_HIDE);
  ((CEdit*)pWnd)->SetReadOnly(FALSE); 
  // Initialize. Set to READ only for Ney's Std Parallel 2
  pWnd = GetDlgItem(IDC_STATIC24);
  pWnd->ShowWindow(SW_HIDE);

  pWnd = GetDlgItem(IDC_EDIT25);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC25);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT26);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC26);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT27);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC27);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT28);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC28);
  pWnd->ShowWindow(SW_HIDE);

  pWnd = GetDlgItem(IDC_EDIT29);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC29);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_EDIT30);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC30);
  pWnd->ShowWindow(SW_HIDE);

  /* Hide UPS/UTM Hemisphere controls */
  pWnd = GetDlgItem(IDC_UPS_HEMI_GROUP);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_UPS_HEMI_S);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_UPS_HEMI_N);
  pWnd->ShowWindow(SW_HIDE);

  /* Hide UTM zone override controls */
  pWnd = GetDlgItem(IDC_ZONE_TITLE);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_SET_ZONE_BUTTON);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_ZONE_EDIT);
  pWnd->ShowWindow(SW_HIDE);

  /* Hide Neys std parallel 1 controls */
  pWnd = GetDlgItem(IDC_STD_PARALLEL1_GROUP);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STD_PARALLEL1_71);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STD_PARALLEL1_74);
  pWnd->ShowWindow(SW_HIDE);

  /* Hide MGRS, F-16 GRS, BNG, GARS, GEOREF Coordinate String controls */
  pWnd = GetDlgItem(IDC_EDIT_COORDSTR);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_STATIC_COORDSTR);
  pWnd->ShowWindow(SW_HIDE);

  m_height_combobox.ShowWindow(SW_HIDE);

  if (error_code)
  {
    // F-16 GRS

    // Layout:0*0*1
    // Coordinate String
    m_edit_coord_str = "31NEA00";
    pWnd = GetDlgItem(IDC_EDIT_COORDSTR);
    pWnd->ShowWindow(SW_SHOW);
    m_static_coord_str = "Coordinate String:";
    pWnd = GetDlgItem(IDC_STATIC_COORDSTR);
    pWnd->ShowWindow(SW_SHOW);
    f16GRS = true;
  }
  else
  {
    char longitude[15];
    char latitude[14];

    f16GRS = false;

    switch (type)
    {
    case Albers_Equal_Area_Conic:
      {
        // Layout 4*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit21_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT21);
        pWnd->ShowWindow(SW_SHOW);
        m_static21_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC21);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(45.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //1st Std Parallel
        Latitude_to_String(40.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "1st Std. Parallel:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //2nd Std Parallel
        Latitude_to_String(50.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit24_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT24);
        pWnd->ShowWindow(SW_SHOW);
        m_static24_str = "2nd Std. Parallel:";
        pWnd = GetDlgItem(IDC_STATIC24);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Azimuthal_Equidistant:
      {
        // Layout 2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Bonne:
      {
        // Layout 2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(45.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case BNG:
      {
        // Layout:0*0*1
        // Coordinate String
        m_edit_coord_str = "SV 0000000000";
        pWnd = GetDlgItem(IDC_EDIT_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        m_static_coord_str = "Coordinate String:";
        pWnd = GetDlgItem(IDC_STATIC_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Cassini:
      {
        // Layout 2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Cylindrical_Equal_Area:
      {
        // Layout 2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Eckert4:
      {
        // Layout:1*2*2
  // Set Parameters
        // Central Meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //False Easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //False Northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Eckert6:
      {
        // Layout:3*0*2
  // Set Parameters
        // Central Meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //False Easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //False Northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Equidistant_Cylindrical:
      {
        // Layout 2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //Standard Parallel
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Standard Parallel:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Geocentric:
      {
        // Layout:0*0*3
  //  Set Coordinates
        // X
        m_edit7_str = "0";
        pWnd = GetDlgItem(IDC_EDIT7);
        pWnd->ShowWindow(SW_SHOW);
        m_static7_str = " X (m):";
        pWnd = GetDlgItem(IDC_STATIC7);
        pWnd->ShowWindow(SW_SHOW);
        //  Y
        m_edit8_str = "0";
        pWnd = GetDlgItem(IDC_EDIT8);
        pWnd->ShowWindow(SW_SHOW);
        m_static8_str = " Y (m):";
        pWnd = GetDlgItem(IDC_STATIC8);
        pWnd->ShowWindow(SW_SHOW);
        //  Z
        m_edit9_str = "0";
        pWnd = GetDlgItem(IDC_EDIT9);
        pWnd->ShowWindow(SW_SHOW);
        m_static9_str = " Z (m):";
        pWnd = GetDlgItem(IDC_STATIC9);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Geodetic:
      {
        // Layout:0*1*2   
        // height type
  //  Set Parameters
        m_height_combobox.ShowWindow(SW_SHOW);

        geo_height = 0;
        ((CMainFrame*)GetParentFrame())->Check_3D_Conversion();
       
  //  Set Coordinates
        //  Longitude
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit7_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT7);
        pWnd->ShowWindow(SW_SHOW);
        m_static7_str = "Longitude:";
        pWnd = GetDlgItem(IDC_STATIC7);
        pWnd->ShowWindow(SW_SHOW);
        // Latitude 
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit8_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT8);
        pWnd->ShowWindow(SW_SHOW);
        m_static8_str = "Latitude:";
        pWnd = GetDlgItem(IDC_STATIC8);
        pWnd->ShowWindow(SW_SHOW);
        // Height  
        m_edit9_str = "0";
        pWnd = GetDlgItem(IDC_EDIT9);
        pWnd->ShowWindow(SW_SHOW);
        m_static9_str = "Height (m):";
        pWnd = GetDlgItem(IDC_STATIC9);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case GARS:
      {
        // Layout: 0*0*1
        // Coordinate String
        m_edit_coord_str = "361HN37";
        pWnd = GetDlgItem(IDC_EDIT_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        m_static_coord_str = "Coordinate String:";
        pWnd = GetDlgItem(IDC_STATIC_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case GEOREF:
      {
        // Layout: 0*0*1
        // Coordinate String
        m_edit_coord_str = "NGAA0000000000";
        pWnd = GetDlgItem(IDC_EDIT_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        m_static_coord_str = "Coordinate String:";
        pWnd = GetDlgItem(IDC_STATIC_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Gnomonic:
      {
        // Layout: 2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Lambert_Conformal_Conic_1:
      {
        // Layout: 3*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit1_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT1);
        pWnd->ShowWindow(SW_SHOW);
        m_static1_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC1);
        pWnd->ShowWindow(SW_SHOW);
        //origin latitude
        Latitude_to_String(45,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //scale factor
        m_edit3_str = "1.00000";
        pWnd = GetDlgItem(IDC_EDIT3);
       //////// ((CEdit*)pWnd)->SetReadOnly(TRUE);
        pWnd->ShowWindow(SW_SHOW);
        m_static3_str = "Scale Factor:";
        pWnd = GetDlgItem(IDC_STATIC3);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Lambert_Conformal_Conic_2:
      {
        // Layout 4*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit21_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT21);
        pWnd->ShowWindow(SW_SHOW);
        m_static21_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC21);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(45.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //1st Std Parallel
        Latitude_to_String(40.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "1st Std. Parallel:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //2nd Std Parallel
        Latitude_to_String(50.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit24_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT24);
        pWnd->ShowWindow(SW_SHOW);
        m_static24_str = "2nd Std. Parallel:";
        pWnd = GetDlgItem(IDC_STATIC24);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Local_Cartesian:
      {
        // Layout: 3*1*3
  // Set Parameters
        // origin longitude
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit1_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT1);
        pWnd->ShowWindow(SW_SHOW);
        m_static1_str = "Origin Longitude:";
        pWnd = GetDlgItem(IDC_STATIC1);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //Origin Height
        m_edit3_str = "0";
        pWnd = GetDlgItem(IDC_EDIT3);
        pWnd->ShowWindow(SW_SHOW);
        m_static3_str = "Origin Height (m):";
        pWnd = GetDlgItem(IDC_STATIC3);
        pWnd->ShowWindow(SW_SHOW);
        //Orientation
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit5_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT5);
        pWnd->ShowWindow(SW_SHOW);
        m_static5_str = "Orientation:";
        pWnd = GetDlgItem(IDC_STATIC5);
        pWnd->ShowWindow(SW_SHOW);


        //  Set Coordinates
        // X
        m_edit7_str = "0";
        pWnd = GetDlgItem(IDC_EDIT7);
        pWnd->ShowWindow(SW_SHOW);
        m_static7_str = " X (m):";
        pWnd = GetDlgItem(IDC_STATIC7);
        pWnd->ShowWindow(SW_SHOW);
        //  Y
        m_edit8_str = "0";
        pWnd = GetDlgItem(IDC_EDIT8);
        pWnd->ShowWindow(SW_SHOW);
        m_static8_str = " Y (m):";
        pWnd = GetDlgItem(IDC_STATIC8);
        pWnd->ShowWindow(SW_SHOW);
        //  Z
        m_edit9_str = "0";
        pWnd = GetDlgItem(IDC_EDIT9);
        pWnd->ShowWindow(SW_SHOW);
        m_static9_str = " Z (m):";
        pWnd = GetDlgItem(IDC_STATIC9);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }     
    case Mercator:
      {
        // Layout: 3*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit1_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT1);
        pWnd->ShowWindow(SW_SHOW);
        m_static1_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC1);
        pWnd->ShowWindow(SW_SHOW);
        //latitude of true scale
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Lat. of True Scale:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //scale factor
        m_edit3_str = "1.00000";
        pWnd = GetDlgItem(IDC_EDIT3);
        ((CEdit*)pWnd)->SetReadOnly(TRUE);
        pWnd->ShowWindow(SW_SHOW);
        m_static3_str = "Scale Factor:";
        pWnd = GetDlgItem(IDC_STATIC3);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case MGRS:
      {
        // Layout:0*0*1
        // Coordinate String
        m_edit_coord_str = "31NEA0000000000";
        pWnd = GetDlgItem(IDC_EDIT_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        m_static_coord_str = "Coordinate String:";
        pWnd = GetDlgItem(IDC_STATIC_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Miller_Cylindrical:
      {
        // Layout:1*2*2
  // Set Parameters
        // Central Meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //False Easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //False Northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Mollweide:
      {
        // Layout:1*2*2
  // Set Parameters
        // Central Meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //False Easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //False Northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Neys:
      {
        // Layout 4*2*2
  // Set Parameters
        //central meridian
        long length;
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit21_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT21);
        pWnd->ShowWindow(SW_SHOW);
        m_static21_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC21);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(80.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);

        pWnd = GetDlgItem(IDC_STD_PARALLEL1_GROUP);
        pWnd->ShowWindow(SW_SHOW);
        std_parallel1 = 0;
        //set default button for 1st Std Parallel
        OnStdParallel71();
        pWnd = GetDlgItem(IDC_STD_PARALLEL1_71);
        pWnd->ShowWindow(SW_SHOW);
        pWnd = GetDlgItem(IDC_STD_PARALLEL1_74);
        pWnd->ShowWindow(SW_SHOW);
        //2nd Std Parallel - set to read only at 89 59 59.0
        Latitude_to_String(89.99972222222222,latitude,use_NSEW,use_Minutes,use_Seconds);
        length = strlen(latitude) - 1;
        if (isalpha(latitude[length]))
          latitude[length] = '\0';
        m_edit24_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT24);
        ((CEdit*)pWnd)->SetReadOnly(TRUE);
        pWnd->ShowWindow(SW_SHOW);
        m_static24_str = "2nd Std. Parallel:";
        pWnd = GetDlgItem(IDC_STATIC24);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case NZMG:
      {
        // Layout 0*0*2
  //  Set Coordinates
        // Easting
        m_edit29_str = "2510000";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "6023150";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Oblique_Mercator:
       {
      // Layout:4*4*2
  // Set Parameters
      //Orgin Latitude
        Latitude_to_String(45.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit21_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT21);
        pWnd->ShowWindow(SW_SHOW);
        m_static21_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC21);
        pWnd->ShowWindow(SW_SHOW);
        //Scale Factor
        m_edit22_str = "1.00000";
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Scale Factor:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //Longitude 1
        Longitude_to_String(-5.0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Longitude 1:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //Latitude 1
        Latitude_to_String(40.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit24_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT24);
        pWnd->ShowWindow(SW_SHOW);
        m_static24_str = "Latitude 1:";
        pWnd = GetDlgItem(IDC_STATIC24);
        pWnd->ShowWindow(SW_SHOW);
        //Longitude 2
        Longitude_to_String(5.0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit25_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT25);
        pWnd->ShowWindow(SW_SHOW);
        m_static25_str = "Longitude 2:";
        pWnd = GetDlgItem(IDC_STATIC25);
        pWnd->ShowWindow(SW_SHOW);
        //Latitude 2
        Latitude_to_String(50.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit26_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "Latitude 2:";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit28_str = "0";
        pWnd = GetDlgItem(IDC_EDIT28);
        pWnd->ShowWindow(SW_SHOW);
        m_static28_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC28);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
    } 
    case Orthographic:
      {
        // Layout:2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Polar_Stereo:
      {
        // Layout:2*2*2
  // Set Parameters
        //Longitude..
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Long. Down:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //Latitude
        Latitude_to_String(90.0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Lat. of True Scale:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Polyconic:
      {
        // Layout:2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Sinusoidal:
      {
        // Layout:1*2*2
  // Set Parameters
        // Central Meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //False Easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //False Northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Stereographic:
      {
        // Layout 2*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit22_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT22);
        pWnd->ShowWindow(SW_SHOW);
        m_static22_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC22);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit23_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT23);
        pWnd->ShowWindow(SW_SHOW);
        m_static23_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC23);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Transverse_Cylindrical_Equal_Area:
      {
        // Layout:3*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit1_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT1);
        pWnd->ShowWindow(SW_SHOW);
        m_static1_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC1);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //scale factor
        m_edit3_str = "1.00000";
        pWnd = GetDlgItem(IDC_EDIT3);
        pWnd->ShowWindow(SW_SHOW);
        m_static3_str = "Scale Factor:";
        pWnd = GetDlgItem(IDC_STATIC3);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Transverse_Mercator:
      {
        // Layout:3*2*2
  // Set Parameters
        //central meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit1_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT1);
        pWnd->ShowWindow(SW_SHOW);
        m_static1_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC1);
        pWnd->ShowWindow(SW_SHOW);
        //origin_latitude
        Latitude_to_String(0,latitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = latitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Origin Latitude:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //scale factor
        m_edit3_str = "1.00000";
        pWnd = GetDlgItem(IDC_EDIT3);
        pWnd->ShowWindow(SW_SHOW);
        m_static3_str = "Scale Factor:";
        pWnd = GetDlgItem(IDC_STATIC3);
        pWnd->ShowWindow(SW_SHOW);
        //false_easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //false_northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case UPS:
      {
        // Layout:0*0*2
  //  Set Coordinates
        // Hemisphere
        hemisphere_type = 0;
        m_ups_hemi_n = 0;
        pWnd = GetDlgItem(IDC_UPS_HEMI_GROUP);
        pWnd->ShowWindow(SW_SHOW);
        pWnd = GetDlgItem(IDC_UPS_HEMI_S);
        pWnd->ShowWindow(SW_SHOW);
        pWnd = GetDlgItem(IDC_UPS_HEMI_N);
        pWnd->ShowWindow(SW_SHOW);

        // Easting
        m_edit29_str = "2000000";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "2000000";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case USNG:
      {
        // Layout:0*0*1
        // Coordinate String
        m_edit_coord_str = "31NEA0000000000";
        pWnd = GetDlgItem(IDC_EDIT_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        m_static_coord_str = "Coordinate String:";
        pWnd = GetDlgItem(IDC_STATIC_COORDSTR);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case UTM:
      {
        // Layout:0*0*2
        /* UTM Hemisphere controls */
        hemisphere_type = 0;
        m_ups_hemi_n = 0;
        pWnd = GetDlgItem(IDC_UPS_HEMI_GROUP);
        pWnd->ShowWindow(SW_SHOW);
        pWnd = GetDlgItem(IDC_UPS_HEMI_S);
        pWnd->ShowWindow(SW_SHOW);
        pWnd = GetDlgItem(IDC_UPS_HEMI_N);
        pWnd->ShowWindow(SW_SHOW);

        /* UTM zone override controls */
      /* If zone override is false, zone edit is read-only.*/
        tog_check = true;
        OnSetUtmZone();

        pWnd = GetDlgItem(IDC_ZONE_TITLE);
        pWnd->ShowWindow(SW_SHOW);
        pWnd = GetDlgItem(IDC_SET_ZONE_BUTTON);
        pWnd->ShowWindow(SW_SHOW);
        pWnd = GetDlgItem(IDC_ZONE_EDIT);
        pWnd->ShowWindow(SW_SHOW);
        m_zone_edit_str = "0";
  //  Set Coordinates
        // Easting
        m_edit29_str = "500000";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }
    case Van_der_Grinten:
      {
        // Layout:1*2*2
  // Set Parameters
        // Central Meridian
        Longitude_to_String(0,longitude,use_NSEW,use_Minutes,use_Seconds);
        m_edit2_str = longitude;
        pWnd = GetDlgItem(IDC_EDIT2);
        pWnd->ShowWindow(SW_SHOW);
        m_static2_str = "Central Meridian:";
        pWnd = GetDlgItem(IDC_STATIC2);
        pWnd->ShowWindow(SW_SHOW);
        //False Easting
        m_edit26_str = "0";
        pWnd = GetDlgItem(IDC_EDIT26);
        pWnd->ShowWindow(SW_SHOW);
        m_static26_str = "False Easting (m):";
        pWnd = GetDlgItem(IDC_STATIC26);
        pWnd->ShowWindow(SW_SHOW);
        //False Northing
        m_edit27_str = "0";
        pWnd = GetDlgItem(IDC_EDIT27);
        pWnd->ShowWindow(SW_SHOW);
        m_static27_str = "False Northing (m):";
        pWnd = GetDlgItem(IDC_STATIC27);
        pWnd->ShowWindow(SW_SHOW);
  //  Set Coordinates
        // Easting
        m_edit29_str = "0";
        pWnd = GetDlgItem(IDC_EDIT29);
        pWnd->ShowWindow(SW_SHOW);
        m_static29_str = "Easting / X (m):";
        pWnd = GetDlgItem(IDC_STATIC29);
        pWnd->ShowWindow(SW_SHOW);
        //  Northing
        m_edit30_str = "0";
        pWnd = GetDlgItem(IDC_EDIT30);
        pWnd->ShowWindow(SW_SHOW);
        m_static30_str = "Northing / Y (m):";
        pWnd = GetDlgItem(IDC_STATIC30);
        pWnd->ShowWindow(SW_SHOW);
        break;
      }

    }// end of Switch(type) for InitializeForm()
  }
  UpdateData(FALSE);  
}


// -------------------------------------------------------
//  Specialized Functions for Setting Hemisphere
// -------------------------------------------------------
void CMasterView::OnHemiN() 
{
  hemisphere_type = 0;      
  m_ups_hemi_n = 0;
}

void CMasterView::OnHemiS() 
{
  hemisphere_type = 1;  
  m_ups_hemi_n = 1;
}

void CMasterView::OnSetUtmZone() 
{
  CWnd *pWnd;
  tog_check = !tog_check;
  pWnd = GetDlgItem(IDC_ZONE_EDIT);

  pWnd = GetDlgItem(IDC_SET_ZONE_BUTTON);
  ((CButton*)pWnd)->SetCheck(tog_check);
}

void CMasterView::OnStdParallel71() 
{
  std_parallel1 = 0;      
  CWnd *pWnd = GetDlgItem(IDC_STD_PARALLEL1_71);
  ((CButton*)pWnd)->SetCheck(TRUE);
  pWnd = GetDlgItem(IDC_STD_PARALLEL1_74);
  ((CButton*)pWnd)->SetCheck(FALSE);
}

void CMasterView::OnStdParallel74() 
{
  std_parallel1 = 1;  
  CWnd *pWnd = GetDlgItem(IDC_STD_PARALLEL1_71);
  ((CButton*)pWnd)->SetCheck(FALSE);
  pWnd = GetDlgItem(IDC_STD_PARALLEL1_74);
  ((CButton*)pWnd)->SetCheck(TRUE);
}

void CMasterView::ReportAccuracy()
{
  char str[15];
  double ce90, le90, se90;

  Get_Conversion_Errors (Interactive, &ce90, &le90, &se90);
  if (ce90 == -1.0)
    m_ce90_str = "Unk";
  else
  {
    sprintf(str,"%1.0f",ce90);
    m_ce90_str = str;
  }
  if (!_3dConversion)
  {
    m_le90_str = "N/A";
    m_se90_str = "N/A";
  }
  else
  {
    if (le90 == -1.0)
      m_le90_str = "Unk";
    else
    {
      sprintf(str,"%1.0f",le90);
      m_le90_str = str;
    }
    if (se90 == -1.0)
      m_se90_str = "Unk";
    else
    {
      sprintf(str,"%1.0f",se90);
      m_se90_str = str;
    }
  }
  usePrevAccuracies = true;
  UpdateData(FALSE);  
}

void CMasterView::SetAccuracy()
{
  int error1 = 0, error2 = 0, error3 = 0;
  double ce90, le90, se90;

  if (!usePrevAccuracies)
  {
    if (m_ce90_str == "Unk")
      ce90 = -1.0;
    else
    {
      error1 = String_to_Double(m_ce90_str,&ce90);
      if (ce90 < 0)
        error1 = 1;
    }

    if ((m_le90_str == "Unk") || (m_le90_str == "N/A"))
      le90 = -1.0;
    else
    {
      error2 = String_to_Double(m_le90_str,&le90);
      if (le90 < 0)
        error2 = 1;
    }

    if ((m_se90_str == "Unk") || (m_se90_str == "N/A"))
      se90 = -1.0;
    else
    {
      error3 = String_to_Double(m_se90_str,&se90);
      if (se90 < 0)
        error3 = 1;
    }

    if (error1 || error2 || error3)
    {
      char err_str[256] = "Error:\nInput Sources:\n\n";
      if (error1)
        Error_Append("Invalid CE90","\n",err_str);
      if (error2)
        Error_Append("Invalid LE90","\n",err_str);
      if (error3)
        Error_Append("Invalid SE90","\n",err_str);
      AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
    }
    else
      Set_Conversion_Errors(Interactive, ce90, le90, se90);
  }
}


void CMasterView::OnChangeCE90() 
{
  usePrevAccuracies = false;
}


void CMasterView::OnChangeLE90() 
{
  usePrevAccuracies = false;
}


void CMasterView::OnChangeSE90() 
{
  usePrevAccuracies = false;
}

void CMasterView::setGeodeticHeight(int type)
{
  geo_height = type;
  m_height_combobox.SetCurSel(geo_height);

  OnSelchangeHeightCombobox();
  UpdateData(FALSE); 

}

int CMasterView::getGeodeticHeight()
{
  return geo_height;
}

void CMasterView::UpdateSrcErrors(bool _3dConv)
{
  _3dConversion = _3dConv;
  OnSelchangeErrsrc();
}

void CMasterView::OnSelchangeHeightCombobox() 
{
  geo_height = m_height_combobox.GetCurSel();
  if(geo_height == No_Height)
  {
    CWnd *pWnd = GetDlgItem(IDC_EDIT9);
    ((CEdit*)pWnd)->SetReadOnly(TRUE);
  }
  else
  {
    CWnd *pWnd = GetDlgItem(IDC_EDIT9);
    ((CEdit*)pWnd)->SetReadOnly(FALSE);
  }
}



// -------------------------------------------------------
// Get Parameters for setting defaults
// -------------------------------------------------------
void CMasterView::getDatumCode( char* code )
{
  Get_Datum_Code ( datum_index, code );
}


void CMasterView::getProjectionCode( char* code )
{
  Get_Coordinate_System_Code ( type + 1, code );
}


double CMasterView::get3ParamCentralMeridian()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit2_str,&temp_val);
  return temp_val;
}


double CMasterView::getFalseEasting()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Double(m_edit26_str,&temp_val);
  return temp_val;
}


double CMasterView::getFalseNorthing()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Double(m_edit27_str,&temp_val);
  return temp_val;
}


double CMasterView::get4ParamCentralMeridian()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit22_str,&temp_val);
  return temp_val;
}


double CMasterView::get4ParamOriginLatitude()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit23_str,&temp_val);
  return temp_val;
}


double CMasterView::get5ParamCentralMeridian()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit1_str,&temp_val);
  return temp_val;
}


double CMasterView::get5ParamOriginLatitude()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit2_str,&temp_val);
  return temp_val;
}


double CMasterView::get5ParamScaleFactor()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Double(m_edit3_str,&temp_val);
  return temp_val;
}


double CMasterView::get6ParamCentralMeridian()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit21_str,&temp_val);
  return temp_val;
}


double CMasterView::get6ParamOriginLatitude()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit22_str,&temp_val);
  return temp_val;
}


double CMasterView::get6ParamStandardParallel1()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit23_str,&temp_val);
  return temp_val;
}


double CMasterView::get6ParamStandardParallel2()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit24_str,&temp_val);
  return temp_val;
}


double CMasterView::getOriginLongitude()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit1_str,&temp_val);
  return temp_val;
}


double CMasterView::getOriginLatitude()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit2_str,&temp_val);
  return temp_val;
}


double CMasterView::getOriginHeight()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Double(m_edit3_str,&temp_val);
  return temp_val;
}


double CMasterView::getOrientation()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit5_str,&temp_val);
  return temp_val;
}


double CMasterView::getNeysStandardParallel1()
{
  UpdateData(TRUE); 

  if (std_parallel1 == 0)
    return 71.0;
  else
    return 74.0;
}


double CMasterView::getOmercOriginLatitude()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit21_str,&temp_val);
  return temp_val;
}


double CMasterView::getOmercScaleFactor()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Double(m_edit22_str,&temp_val);
  return temp_val;
}


double CMasterView::getOmercLongitude1()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit23_str,&temp_val);
  return temp_val;
}


double CMasterView::getOmercLatitude1()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit24_str,&temp_val);
  return temp_val;
}


double CMasterView::getOmercLongitude2()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Longitude(m_edit25_str,&temp_val);
  return temp_val;
}


double CMasterView::getOmercLatitude2()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Latitude(m_edit26_str,&temp_val);
  return temp_val;
}


double CMasterView::getOmercFalseEasting()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Double(m_edit27_str,&temp_val);
  return temp_val;
}


double CMasterView::getOmercFalseNorthing()
{
  UpdateData(TRUE); 

  double temp_val;
  String_to_Double(m_edit28_str,&temp_val);
  return temp_val;
}


int CMasterView::getOverride()
{
  UpdateData(TRUE); 

  if (tog_check)
  {
    return 1;
  }
  else
    return 0;
}


long CMasterView::getZone()
{
  UpdateData(TRUE); 

  if (tog_check)
  {
    double temp_val;
    String_to_Double(m_zone_edit_str,&temp_val);
    return (long)temp_val;
  }
  else
    return 0;
}


// -------------------------------------------------------
// Set Parameter defaults
// -------------------------------------------------------
void CMasterView::setDatum( int datumIndex )
{
  CWnd* wPtr = GetDlgItem(IDC_DATUM_COMBOBOX);
  ((CComboBox*)wPtr)->SetCurSel( datumIndex );

  OnSelchangeDatumCombobox();
}


void CMasterView::setProjection( int projectionIndex )
{
  CWnd* pWnd = GetDlgItem(IDC_SELECT_PROJECTION);
  ((CComboBox*)pWnd)->SetCurSel( projectionIndex );

  Initialize_Form();
  ((CMainFrame*)GetParentFrame())->Check_3D_Conversion();
  ((CMainFrame*)GetParentFrame())->Check_Valid_Conversion();
}


void CMasterView::set3ParamCentralMeridian( double central_meridian )
{
  char str[15];

  Longitude_to_String( central_meridian, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit2_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setFalseEasting( double false_easting )
{
  char str[15];

  Meter_to_String( false_easting, str );
  m_edit26_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setFalseNorthing( double false_northing )
{
  char str[15];

  Meter_to_String( false_northing, str );
  m_edit27_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set4ParamCentralMeridian( double central_meridian )
{
  char str[15];

  Longitude_to_String( central_meridian, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit22_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set4ParamOriginLatitude( double origin_latitude )
{
  char str[14];

  Latitude_to_String( origin_latitude, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit23_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set5ParamCentralMeridian( double central_meridian )
{
  char str[15];

  Longitude_to_String( central_meridian, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit1_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set5ParamOriginLatitude( double origin_latitude )
{
  char str[14];

  Latitude_to_String( origin_latitude, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit2_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set5ParamScaleFactor( double scale_factor )
{
  char str[15];

  sprintf(str, "%.5f", scale_factor);
  m_edit3_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set6ParamCentralMeridian( double central_meridian )
{
  char str[15];

  Longitude_to_String( central_meridian, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit21_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set6ParamOriginLatitude( double origin_latitude )
{
  char str[14];

  Latitude_to_String( origin_latitude, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit22_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set6ParamStandardParallel1( double standard_parallel_1 )
{
  char str[14];

  Latitude_to_String( standard_parallel_1, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit23_str = str;

  UpdateData(FALSE); 
}


void CMasterView::set6ParamStandardParallel2( double standard_parallel_2 )
{
  char str[14];

  Latitude_to_String( standard_parallel_2, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit24_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOriginLongitude( double origin_longitude )
{
  char str[15];

  Longitude_to_String( origin_longitude, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit1_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOriginLatitude( double origin_latitude )
{
  char str[14];

  Latitude_to_String( origin_latitude, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit2_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOriginHeight( double origin_height )
{
  char str[15];

  Meter_to_String( origin_height, str );
  m_edit3_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOrientation( double orientation )
{
  char str[15];

  Longitude_to_String( orientation, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit5_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setNeysStandardParallel1( double standard_parallel_1 )
{
  if (standard_parallel_1 == 71.0)
    OnStdParallel71();
  else
    OnStdParallel74();

  UpdateData(FALSE); 
}


void CMasterView::setOmercOriginLatitude( double origin_latitude )
{
  char str[14];

  Latitude_to_String( origin_latitude, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit21_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOmercScaleFactor( double scale_factor )
{
  char str[15];

  sprintf(str, "%.5f", scale_factor);
  m_edit22_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOmercLongitude1( double longitude1 )
{
  char str[15];

  Longitude_to_String( longitude1, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit23_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOmercLatitude1( double latitude1 )
{
  char str[14];

  Latitude_to_String( latitude1, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit24_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOmercLongitude2( double longitude2 )
{
  char str[15];

  Longitude_to_String( longitude2, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit25_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOmercLatitude2( double latitude2 )
{
  char str[14];

  Latitude_to_String( latitude2, str, use_NSEW, use_Minutes, use_Seconds );
  m_edit26_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOmercFalseEasting( double false_easting )
{
  char str[15];

  Meter_to_String( false_easting, str );
  m_edit27_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOmercFalseNorthing( double false_northing )
{
  char str[15];

  Meter_to_String( false_northing, str );
  m_edit28_str = str;

  UpdateData(FALSE); 
}


void CMasterView::setOverride( int override )
{
  if( override )
    tog_check = 1;
  else
    tog_check = 0;

  CWnd *pWnd;
  pWnd = GetDlgItem(IDC_ZONE_EDIT);

  pWnd = GetDlgItem(IDC_SET_ZONE_BUTTON);
  ((CButton*)pWnd)->SetCheck(tog_check);

  UpdateData(FALSE); 
}


void CMasterView::setZone( long zone )
{
  char str[3];

  Zone_to_String( zone, str );
  m_zone_edit_str = str;

  UpdateData(FALSE); 
}







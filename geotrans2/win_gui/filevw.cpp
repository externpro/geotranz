// filevw.cpp : implementation file
//

#include <direct.h>
#include "stdafx.h"
#include "geotrans.h"
#include "engine.h"
#include "filevw.h"
#include "strtoval.h"


#ifdef _DEBUG
  #undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileProcDlg dialog


CFileProcDlg::CFileProcDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CFileProcDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CFileProcDlg)
  m_input_datum = "";
  m_input_ellipsoid = "";
  m_input_label = "";
  m_input_edit1 = "";
  m_input_edit2 = "";
  m_input_edit3 = "";
  m_input_static1 = "";
  m_input_static2 = "";
  m_input_static3 = "";
  m_output_edit1 = "";
  m_output_edit2 = "";
  m_output_edit3 = "";
  m_output_static1 = "";
  m_output_static2 = "";
  m_output_static3 = "";
  m_ellipsoid = "";
  m_datum = "";
  m_zone = "0";
  m_input_edit5 = _T("");
  m_input_static5 = _T("");
  m_input_static21 = _T("");
  m_input_static22 = _T("");
  m_input_static23 = _T("");
  m_input_static24 = _T("");
  m_input_static25 = _T("");
  m_input_static26 = _T("");
  m_input_static27 = _T("");
  m_input_static28 = _T("");
  m_output_static21 = _T("");
  m_output_static22 = _T("");
  m_output_static23 = _T("");
  m_output_static24 = _T("");
  m_output_static25 = _T("");
  m_output_static26 = _T("");
  m_output_static27 = _T("");
  m_output_static28 = _T("");
  m_output_edit5 = _T("");
  m_output_static5 = _T("");
  m_input_height_type = _T("");
  m_input_edit21 = _T("");
  m_input_edit22 = _T("");
  m_input_edit23 = _T("");
  m_input_edit24 = _T("");
  m_input_edit25 = _T("");
  m_input_edit26 = _T("");
  m_input_edit27 = _T("");
  m_input_edit28 = _T("");
  m_output_edit21 = _T("");
  m_output_edit22 = _T("");
  m_output_edit23 = _T("");
  m_output_edit24 = _T("");
  m_output_edit25 = _T("");
  m_output_edit26 = _T("");
  m_output_edit27 = _T("");
  m_output_edit28 = _T("");
  //}}AFX_DATA_INIT
  Get_Coordinate_System(File,Input,&input_type);
  output_type = UTM;
  Set_Coordinate_System(File,Output,output_type);

  long input_datum;
  Get_Datum(File,Input,&input_datum);
  char buf[100];
  Get_Datum_Code(input_datum,buf);
  m_input_datum = buf;
  Get_Datum_Name(input_datum,buf);
  m_input_datum += ":   ";
  m_input_datum += buf;

  Get_Datum_Ellipsoid_Code(input_datum,buf);
  long input_ellipsoid_index;
  Get_Ellipsoid_Index(buf,&input_ellipsoid_index);
  m_input_ellipsoid = buf;
  Get_Ellipsoid_Name(input_ellipsoid_index,buf);
  m_input_ellipsoid += ": ";
  m_input_ellipsoid += buf;

  m_set_zone_button = FALSE;
  m_std_parallel1 = 0;
  //}}AFX_DATA_INIT
}


void CFileProcDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFileProcDlg)
  DDX_Control(pDX, IDC_FILE_HEIGHT_COMBOBOX, m_file_height_combobox);
  DDX_Text(pDX, IDC_INPUT_DATUM, m_input_datum);
  DDX_Text(pDX, IDC_INPUT_ELLIPSOID, m_input_ellipsoid);
  DDX_Text(pDX, IDC_INPUT_LABEL, m_input_label);
  DDX_Text(pDX, IDC_INPUT_EDIT1, m_input_edit1);
  DDX_Text(pDX, IDC_INPUT_EDIT2, m_input_edit2);
  DDX_Text(pDX, IDC_INPUT_EDIT3, m_input_edit3);
  DDX_Text(pDX, IDC_INPUT_STATIC1, m_input_static1);
  DDX_Text(pDX, IDC_INPUT_STATIC2, m_input_static2);
  DDX_Text(pDX, IDC_INPUT_STATIC3, m_input_static3);
  DDX_Text(pDX, IDC_OUTPUT_EDIT1, m_output_edit1);
  DDX_Text(pDX, IDC_OUTPUT_EDIT2, m_output_edit2);
  DDX_Text(pDX, IDC_OUTPUT_EDIT3, m_output_edit3);
  DDX_Text(pDX, IDC_OUTPUT_STATIC1, m_output_static1);
  DDX_Text(pDX, IDC_OUTPUT_STATIC2, m_output_static2);
  DDX_Text(pDX, IDC_OUTPUT_STATIC3, m_output_static3);
  DDX_Text(pDX, IDC_OUTPUT_ELLIPSOID, m_ellipsoid);
  DDX_CBString(pDX, IDC_OUTPUT_DATUM_COMBOBOX, m_datum);
  DDX_Text(pDX, IDC_DLG_UTM_ZONE_EDIT, m_zone);
  DDX_Text(pDX, IDC_INPUT_EDIT5, m_input_edit5);
  DDX_Text(pDX, IDC_INPUT_STATIC5, m_input_static5);
  DDX_Text(pDX, IDC_INPUT_STATIC21, m_input_static21);
  DDX_Text(pDX, IDC_INPUT_STATIC22, m_input_static22);
  DDX_Text(pDX, IDC_INPUT_STATIC23, m_input_static23);
  DDX_Text(pDX, IDC_INPUT_STATIC24, m_input_static24);
  DDX_Text(pDX, IDC_INPUT_STATIC25, m_input_static25);
  DDX_Text(pDX, IDC_INPUT_STATIC26, m_input_static26);
  DDX_Text(pDX, IDC_INPUT_STATIC27, m_input_static27);
  DDX_Text(pDX, IDC_INPUT_STATIC28, m_input_static28);
  DDX_Text(pDX, IDC_OUTPUT_STATIC21, m_output_static21);
  DDX_Text(pDX, IDC_OUTPUT_STATIC22, m_output_static22);
  DDX_Text(pDX, IDC_OUTPUT_STATIC23, m_output_static23);
  DDX_Text(pDX, IDC_OUTPUT_STATIC24, m_output_static24);
  DDX_Text(pDX, IDC_OUTPUT_STATIC25, m_output_static25);
  DDX_Text(pDX, IDC_OUTPUT_STATIC26, m_output_static26);
  DDX_Text(pDX, IDC_OUTPUT_STATIC27, m_output_static27);
  DDX_Text(pDX, IDC_OUTPUT_STATIC28, m_output_static28);
  DDX_Text(pDX, IDC_OUTPUT_EDIT5, m_output_edit5);
  DDX_Text(pDX, IDC_OUTPUT_STATIC5, m_output_static5);
  DDX_Text(pDX, IDC_HEIGHT_TYPE_LABEL, m_input_height_type);
  DDX_Text(pDX, IDC_INPUT_EDIT21, m_input_edit21);
  DDX_Text(pDX, IDC_INPUT_EDIT22, m_input_edit22);
  DDX_Text(pDX, IDC_INPUT_EDIT23, m_input_edit23);
  DDX_Text(pDX, IDC_INPUT_EDIT24, m_input_edit24);
  DDX_Text(pDX, IDC_INPUT_EDIT25, m_input_edit25);
  DDX_Text(pDX, IDC_INPUT_EDIT26, m_input_edit26);
  DDX_Text(pDX, IDC_INPUT_EDIT27, m_input_edit27);
  DDX_Text(pDX, IDC_INPUT_EDIT28, m_input_edit28);
  DDX_Text(pDX, IDC_OUTPUT_EDIT21, m_output_edit21);
  DDX_Text(pDX, IDC_OUTPUT_EDIT22, m_output_edit22);
  DDX_Text(pDX, IDC_OUTPUT_EDIT23, m_output_edit23);
  DDX_Text(pDX, IDC_OUTPUT_EDIT24, m_output_edit24);
  DDX_Text(pDX, IDC_OUTPUT_EDIT25, m_output_edit25);
  DDX_Text(pDX, IDC_OUTPUT_EDIT26, m_output_edit26);
  DDX_Text(pDX, IDC_OUTPUT_EDIT27, m_output_edit27);
  DDX_Text(pDX, IDC_OUTPUT_EDIT28, m_output_edit28);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileProcDlg, CDialog)
  //{{AFX_MSG_MAP(CFileProcDlg)
ON_CBN_SELCHANGE(IDC_OUTPUT_DATUM_COMBOBOX, OnSelchangeOutputDatumCombobox)
ON_CBN_SELCHANGE(IDC_OUTPUT_SYSTEM_COMBOBOX, OnSelchangeOutputSystemCombobox)
ON_BN_CLICKED(IDC_DLG_UTM_BUTTON, OnDlgUtmButton)
ON_EN_CHANGE(IDC_DLG_UTM_ZONE_EDIT, OnChangeDlgUtmZoneEdit)
ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)
ON_BN_CLICKED(IDC_FILE_OUTPUT_STD_PARALLEL1_71, OnFileOutputStdParallel71)
ON_BN_CLICKED(IDC_FILE_OUTPUT_STD_PARALLEL1_74, OnFileOutputStdParallel74)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileProcDlg message handlers

// This function is called after the constructor but before it is displayed
BOOL CFileProcDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  char longitude[15];
  char latitude[14];
  char buf[512];
  CWnd *pWnd;

  switch (input_type)
  {
  case Albers_Equal_Area_Conic:
    {
      Albers_Equal_Area_Conic_Parameters params;
      m_input_label = "Albers Equal Area Conic Projection";
      Get_Albers_Equal_Area_Conic_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit21 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static21 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "1st Std Parallel:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_2*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit24 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT24);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static24 = "2nd Std Parallel:";  
      pWnd = GetDlgItem(IDC_INPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
 case Azimuthal_Equidistant:
    {
      Azimuthal_Equidistant_Parameters params;
      m_input_label = "Azimuthal_Equidistant Projection";
      Get_Azimuthal_Equidistant_Params(File,Input,&params);
      Latitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Bonne:
    {
      Bonne_Parameters params;
      m_input_label = "Bonne Projection";
      Get_Bonne_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case BNG:
    {
      m_input_label = "British National Grid Coordinates";
      break;
    }
  case Cassini:
    {
      Cassini_Parameters params;
      m_input_label = "Cassini Projection";
      Get_Cassini_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Cylindrical_Equal_Area:
    {
      Cylindrical_Equal_Area_Parameters params;
      m_input_label = "Cylindrical Equal Area Projection";
      Get_Cylindrical_Equal_Area_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Eckert4:
    {
      Eckert4_Parameters params;
      m_input_label = "Eckert IV Projection";
      Get_Eckert4_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Eckert6:
    {
      Eckert6_Parameters params;
      m_input_label = "Eckert VI Projection";
      Get_Eckert6_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Equidistant_Cylindrical:
    {
      Equidistant_Cylindrical_Parameters params;
      m_input_label = "Equidistant Cylindrical";
      Get_Equidistant_Cylindrical_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Standard Parallel:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case GARS:
    {
      m_input_label = "GARS Coordinates";
      break;
    }
  case Geocentric:
    {
      m_input_label = "Geocentric Coordinates";
      break;
    }
  case Geodetic:
    {
      Geodetic_Parameters params;
      m_input_label = "Geodetic Coordinates";
      Get_Geodetic_Params(File,Input,&params);
      if (params.height_type == Geoid_or_MSL_Height)
        m_input_height_type = "MSL-EGM96-15M-BL Height";
      else if (params.height_type == MSL_EGM96_VG_NS_Height)
        m_input_height_type = "MSL-EGM96-VG-NS Height";
      else if (params.height_type == MSL_EGM84_10D_BL_Height)
        m_input_height_type = "MSL-EGM84-10D-BL Height";
      else if (params.height_type == MSL_EGM84_10D_NS_Height)
        m_input_height_type = "MSL-EGM84-10D-NS Height";
      else if (params.height_type == No_Height)
        m_input_height_type = "No Height";
      else
        m_input_height_type = "Ellipsoid Height";

      pWnd = GetDlgItem(IDC_HEIGHT_TYPE_LABEL);
      pWnd->ShowWindow(SW_SHOW);
      break;  
    }
  case GEOREF:
    {
      m_input_label = "GEOREF Coordinates";
      break;
    }
 case Gnomonic:
    {
      Gnomonic_Parameters params;
      m_input_label = "Gnomonic Projection";
      Get_Gnomonic_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Lambert_Conformal_Conic_1:
    {
      Lambert_Conformal_Conic_1_Parameters params;
      m_input_label = "Lambert Conformal Conic (1 parallel) Projection";
      Get_Lambert_Conformal_Conic_1_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit1 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_input_edit3 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Lambert_Conformal_Conic_2:
    {
      Lambert_Conformal_Conic_2_Parameters params;
      m_input_label = "Lambert Conformal Conic (2 parallel) Projection";
      Get_Lambert_Conformal_Conic_2_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit21 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static21 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "1st Std Parallel:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_2*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit24 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT24);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static24 = "2nd Std Parallel:";  
      pWnd = GetDlgItem(IDC_INPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Local_Cartesian:
    {
      Local_Cartesian_Parameters params;
      m_input_label = "Local Cartesian Coordinates";
      Get_Local_Cartesian_Params(File,Input,&params);
      Longitude_to_String(params.origin_longitude*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit1 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static1 = "Origin Longitude";
      pWnd = GetDlgItem(IDC_INPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.origin_height);
      m_input_edit3 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static3 = "Origin Height (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      Longitude_to_String(params.orientation*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit5 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT5);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static5 = "Orientation:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC5);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }     
  case Mercator:
    {
      Mercator_Parameters params;
      m_input_label = "Mercator Projection";
      Convert(File); /* this is to update mercator scale factor */
      Get_Mercator_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit1 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.latitude_of_true_scale*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Lat. of True Scale:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_input_edit3 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case MGRS:
    {
      m_input_label = "MGRS Coordinates";
      break;
    }
  case Miller_Cylindrical:
    {
      Miller_Cylindrical_Parameters params;
      m_input_label = "Miller Cylindrical Projection";
      Get_Miller_Cylindrical_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Mollweide:
    {
      Mollweide_Parameters params;
      m_input_label = "Mollweide Projection";
      Get_Mollweide_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Neys:
    {
      Neys_Parameters params;
      long north_hemi = 1;
      m_input_label = "Ney's (Modified Lambert Conformal Conic) Projection";
      Get_Neys_Params(File,Input,&params);
      if (params.origin_latitude < 0)
        north_hemi = 0;
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit21 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static21 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      if (north_hemi)
        Latitude_to_String(params.std_parallel_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      else
        Latitude_to_String(-params.std_parallel_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "1st Std Parallel:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      /* std parallel 2 = 89 59 59.0 */
      if (north_hemi)
        Latitude_to_String(89.99972222222222,latitude,use_NSEW,use_Minutes,use_Seconds);
      else
        Latitude_to_String(-89.99972222222222,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit24 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT24);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static24 = "2nd Std Parallel:";  
      pWnd = GetDlgItem(IDC_INPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case NZMG:
    {
      m_input_label = "New Zealand Map Grid Projection";
      break;
    }
  case Oblique_Mercator:
    {
      Oblique_Mercator_Parameters params;
      m_input_label = "Oblique Mercator Projection";
      Get_Oblique_Mercator_Params(File,Input,&params);
    // origin latitude
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit21 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static21 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
    // scale factor
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_input_edit22 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
    // longitude 1
      Longitude_to_String(params.longitude_1*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Longitude 1:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
    // latitude 1
      Latitude_to_String(params.latitude_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit24= latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT24);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static24 = "Latitude 1:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);
    // longitude 2
      Longitude_to_String(params.longitude_2*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit25 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT25);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static25 = "Longitude 2:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC25);
      pWnd->ShowWindow(SW_SHOW);
    // latitude 2
      Latitude_to_String(params.latitude_2*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit26= latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "Latitude 2:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
    // false easting
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
    // false northing
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit28 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT28);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static28 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC28);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Orthographic:
    {
      Orthographic_Parameters params;
      m_input_label = "Orthographic Projection";
      Get_Orthographic_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Polar_Stereo:
    {
      Polar_Stereo_Parameters params;
      m_input_label = "Polar Stereographic Projection";
      Get_Polar_Stereo_Params(File,Input,&params);
      Longitude_to_String(params.longitude_down_from_pole*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Long. Down:"; 
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.latitude_of_true_scale *180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Lat. of True Scale:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Polyconic:
    {
      Polyconic_Parameters params;
      m_input_label = "Polyconic Projection";
      Get_Polyconic_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_edit2 = "";
      m_input_static2 = "";
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_edit5 = "";
      m_input_static5 = "";
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Sinusoidal:
    {
      Sinusoidal_Parameters params;
      m_input_label = "Sinusoidal Projection";
      Get_Sinusoidal_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
 case Stereographic:
    {
      Stereographic_Parameters params;
      m_input_label = "Stereographic Projection";
      Get_Stereographic_Params(File,Input,&params);
      Latitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit22 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit23 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Transverse_Cylindrical_Equal_Area:
    {
      Transverse_Cylindrical_Equal_Area_Parameters params;
      m_input_label = "Transverse Cylindrical Equal Area Projection";
      Get_Transverse_Cylindrical_Equal_Area_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit1 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_input_edit3 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Transverse_Mercator:
    {
      Transverse_Mercator_Parameters params;
      m_input_label = "Transverse Mercator Projection";
      Get_Transverse_Mercator_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit1 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = latitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_input_edit3 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case UPS:
    {
      m_input_label = "Universal Polar Stereographic (UPS) Projection";
      break;
    }
  case USNG:
    {
      m_input_label = "USNG Coordinates";
      break;
    }
  case UTM:
    {
      m_input_label = "Universal Transverse Mercator (UTM) Projection";
      break;
    }
  case Van_der_Grinten:
    {
      Van_der_Grinten_Parameters params;
      m_input_label = "Van der Grinten Projection";
      Get_Van_der_Grinten_Params(File,Input,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_input_edit2 = longitude;
      pWnd = GetDlgItem(IDC_INPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_INPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_input_edit26 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_input_edit27 = buf;
      pWnd = GetDlgItem(IDC_INPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_input_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_INPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  } /* switch (input_type) */
  FillDatumListBox();
  FillHeightList();
  FillSystemListBox();
  UpdateData(FALSE);
  pWnd = GetDlgItem(IDOK);
  pWnd->EnableWindow(TRUE);
  return (TRUE);
}

void CFileProcDlg::OnSelchangeOutputDatumCombobox()
{
/*
 * This function is called when the user selects a different output datum
 * from the drop down list.
 *
 */
  CWnd *wPtr;
  long ellipsoid_index;
  long error_code;
  char code[10];
  char name[40];
  char full_name[50];

  wPtr = GetDlgItem(IDC_OUTPUT_DATUM_COMBOBOX);
  long datum_index = ((CComboBox*)wPtr)->GetCurSel( ) + 1;

  Set_Datum(File,Output,datum_index);
  error_code = Get_Datum_Code(datum_index,code);
  sprintf(code,"%s:",code);
  error_code = Get_Datum_Name(datum_index,name);
  sprintf(full_name,"%-8s%s",code,name);
  m_datum = full_name;

  error_code =  Get_Datum_Ellipsoid_Code ( datum_index, code );
  error_code = Get_Ellipsoid_Index ( code, &ellipsoid_index );
  error_code = Get_Ellipsoid_Name ( ellipsoid_index, name );
  sprintf(full_name,"%s: %s",code,name);
  m_ellipsoid = full_name;

  UpdateData(FALSE);
}

void CFileProcDlg::FillDatumListBox()
{
/*
 * This function fills the datum drop-down list with values retrieved from
 * the datum module.
 */
  long error_code, i;
  long count;
  char datum_code[10];
  char datum_name[40];
  char datum_full_name[50];
  CWnd *wPtr;

  error_code = Get_Datum_Count(&count);
  if (error_code)
    MessageBox("Error getting datum count!",NULL,MB_OK);
  else
  {
    wPtr = GetDlgItem(IDC_OUTPUT_DATUM_COMBOBOX);
    for (i=0;i<count;i++)
    {
      error_code = Get_Datum_Code(i+1,datum_code);
      sprintf(datum_code,"%s:",datum_code);
      error_code = Get_Datum_Name(i+1,datum_name);
      sprintf(datum_full_name,"%-8s%s",datum_code,datum_name);
      ((CComboBox*)wPtr)->AddString(datum_full_name);
    }
    ((CComboBox*)wPtr)->SetCurSel(0);
    OnSelchangeOutputDatumCombobox();
  }
}


// This function fills the height drop down combo box.
void CFileProcDlg::FillHeightList()
{
  m_file_height_combobox.AddString( "No Height" );
  m_file_height_combobox.AddString( "Ellipsoid Height" );
  m_file_height_combobox.AddString( "MSL-EGM96-15M-BL Height (recommended)" );
  m_file_height_combobox.AddString( "MSL-EGM96-VG-NS Height" );
  m_file_height_combobox.AddString( "MSL-EGM84-10D-BL Height" );
  m_file_height_combobox.AddString( "MSL-EGM84-10D-NS Height" );

  m_file_height_combobox.SetCurSel( 0 );
}


void CFileProcDlg::OnSelchangeOutputSystemCombobox()
{
/*
 * This function is called when the user selects a different output system.
 */
  CWnd *pWnd;
  long system_index;
  char longitude[15];
  char latitude[14];
  char buf[50];
  long error_code;

  UpdateData(TRUE);
  pWnd = GetDlgItem(IDC_OUTPUT_SYSTEM_COMBOBOX);
  system_index = ((CComboBox*)pWnd)->GetCurSel() + 1;
  error_code = Get_Coordinate_System_Type (system_index, &output_type);
  /* Hide general-purpose output edit fields */
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT1);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC1);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT3);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC3);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT5);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC5);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT21);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC21);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT24);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC24);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT25);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC25);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT28);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_OUTPUT_STATIC28);
  pWnd->ShowWindow(SW_HIDE);

  /* Make Mercator scale factor field editable */
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT3);
  ((CEdit*)pWnd)->SetReadOnly(FALSE);
  /* Hide UTM zone override controls */
  pWnd = GetDlgItem(IDC_DLG_UTM_BUTTON);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_DLG_UTM_ZONE_LABEL);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_DLG_UTM_ZONE_EDIT);
  pWnd->ShowWindow(SW_HIDE);

  /* Hide Neys std parallel 1 controls */
  pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_GROUP);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_71);
  pWnd->ShowWindow(SW_HIDE);
  pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_74);
  pWnd->ShowWindow(SW_HIDE);
  /* Make Neys std parallel 2 field editable */
  pWnd = GetDlgItem(IDC_OUTPUT_EDIT24);
  ((CEdit*)pWnd)->SetReadOnly(FALSE);

  m_file_height_combobox.ShowWindow(SW_HIDE);

  switch (output_type)
  {
  case Albers_Equal_Area_Conic:
    {
      Albers_Equal_Area_Conic_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Albers_Equal_Area_Conic_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit21 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static21 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "1st Std Parallel:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_2*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit24 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT24);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static24 = "2nd Std Parallel:";  
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
 case Azimuthal_Equidistant:
    {
      Azimuthal_Equidistant_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Azimuthal_Equidistant_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Bonne:
    {
      Bonne_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Bonne_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
/*  case BNG:
    {
      Set_Coordinate_System(File,Output,output_type);
      break;
    }*/
  case Cassini:
    {
      Cassini_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Cassini_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Cylindrical_Equal_Area:
    {
      Cylindrical_Equal_Area_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Cylindrical_Equal_Area_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Eckert4:
    {
      Eckert4_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Eckert4_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Eckert6:
    {
      Eckert6_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Eckert6_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Equidistant_Cylindrical:
    {
      Equidistant_Cylindrical_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Equidistant_Cylindrical_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_edit2 = "";
      m_output_static2 = "";
      Latitude_to_String(params.std_parallel*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Standard Parallel:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_edit5 = "";
      m_output_static5 = "";
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  /*case Geocentric:
    {
      Set_Coordinate_System(File,Output,output_type);
      break;
    }*/
  case Geodetic:
    {
      Geodetic_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      m_file_height_combobox.ShowWindow(TRUE);
      if ((input_type == Geodetic) || (input_type == Geocentric) || (input_type == Local_Cartesian))
      {
        m_file_height_combobox.EnableWindow(TRUE);

        Get_Geodetic_Params(File,Output,&params);

        if (params.height_type == No_Height)
          m_file_height_combobox.SetCurSel( No_Height );
        else if (params.height_type == Ellipsoid_Height)
          m_file_height_combobox.SetCurSel( Ellipsoid_Height );
        else if (params.height_type == Geoid_or_MSL_Height)
          m_file_height_combobox.SetCurSel( Geoid_or_MSL_Height );
        else if (params.height_type == MSL_EGM96_VG_NS_Height)
          m_file_height_combobox.SetCurSel( MSL_EGM96_VG_NS_Height );
        else if (params.height_type == MSL_EGM84_10D_BL_Height)
          m_file_height_combobox.SetCurSel( MSL_EGM84_10D_BL_Height );
        else if (params.height_type == MSL_EGM84_10D_NS_Height)
          m_file_height_combobox.SetCurSel( MSL_EGM84_10D_NS_Height );
      }
      else
        m_file_height_combobox.EnableWindow(FALSE);
      
      break;
    }
  case BNG:
  case GARS:
  case GEOREF:
  case Geocentric:
  case MGRS:
  case NZMG:
  case UPS:
  case USNG:
    {
      Set_Coordinate_System(File,Output,output_type);
      break;
    }
 case Gnomonic:
    {
      Gnomonic_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Gnomonic_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Lambert_Conformal_Conic_1:
    {
      Lambert_Conformal_Conic_1_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Lambert_Conformal_Conic_1_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit1 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_output_edit3 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Lambert_Conformal_Conic_2:
    {
      Lambert_Conformal_Conic_2_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Lambert_Conformal_Conic_2_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit21 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static21 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "1st Std Parallel:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.std_parallel_2*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit24 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT24);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static24 = "2nd Std Parallel:";  
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Local_Cartesian:
    {
      Local_Cartesian_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Local_Cartesian_Params(File,Output,&params);
      Longitude_to_String(params.origin_longitude*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit1 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static1 = "Origin Longitude";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.origin_height);
      m_output_edit3 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static3 = "Origin Height (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      Longitude_to_String(params.orientation*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit5 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT5);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static5 = "Orientation:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC5);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }     
  case Mercator:
    {
      Mercator_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Mercator_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit1 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.latitude_of_true_scale*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Lat. of True Scale:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_output_edit3 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT3);
      ((CEdit*)pWnd)->SetReadOnly(TRUE);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  /*case MGRS:
  case USNG:
    {
      Set_Coordinate_System(File,Output,output_type);
      break;
    }*/
  case Miller_Cylindrical:
    {
      Miller_Cylindrical_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Miller_Cylindrical_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Mollweide:
    {
      Mollweide_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Mollweide_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Neys:
    {
      Neys_Parameters params;
      long length;
      Set_Coordinate_System(File,Output,output_type);
      Get_Neys_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit21 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static21 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);

      pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_GROUP);
      pWnd->ShowWindow(SW_SHOW);
      pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_71);
      pWnd->ShowWindow(SW_SHOW);
      if (params.std_parallel_1*180/PI == 71)
      {
        m_std_parallel1 = 0;
        ((CButton*)pWnd)->SetCheck(TRUE);
      }
      else
        ((CButton*)pWnd)->SetCheck(FALSE);

      pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_74);
      pWnd->ShowWindow(SW_SHOW);
      if (params.std_parallel_1*180/PI == 74)
      {
        m_std_parallel1 = 1;
        ((CButton*)pWnd)->SetCheck(TRUE);
      }
      else
        ((CButton*)pWnd)->SetCheck(FALSE);

      //2nd Std Parallel - set to read only at 89 59 59.0
      Latitude_to_String(89.99972222222222,latitude,use_NSEW,use_Minutes,use_Seconds);
      length = strlen(latitude) - 1;
      if (isalpha(latitude[length]))
        latitude[length] = '\0';
      m_output_edit24 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT24);
      ((CEdit*)pWnd)->SetReadOnly(TRUE);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static24 = "2nd Std. Parallel:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);

      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
/*  case NZMG:
    {
      Set_Coordinate_System(File,Output,output_type);
      break;
    }*/
  case Oblique_Mercator:
    {
      Oblique_Mercator_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Oblique_Mercator_Params(File,Output,&params);
    // origin latitude
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit21 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT21);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static21 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC21);
      pWnd->ShowWindow(SW_SHOW);
    // scale factor
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_output_edit22 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
    // longitude 1
      Longitude_to_String(params.longitude_1*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Longitude 1:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
    // latitude 1
      Latitude_to_String(params.latitude_1*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit24= latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT24);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static24 = "Latitude 1:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC24);
      pWnd->ShowWindow(SW_SHOW);
    // longitude 2
      Longitude_to_String(params.longitude_2*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit25 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT25);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static25 = "Longitude 2:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC25);
      pWnd->ShowWindow(SW_SHOW);
    // latitude 2
      Latitude_to_String(params.latitude_2*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit26= latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "Latitude 2:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
    // false easting
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
    // false northing
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit28 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT28);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static28 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC28);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Orthographic:
    {
      Orthographic_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Orthographic_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Polar_Stereo:
    {
      Polar_Stereo_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Polar_Stereo_Params(File,Output,&params);
      Longitude_to_String(params.longitude_down_from_pole*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Long. Down:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.latitude_of_true_scale*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Lat. Of True Scale:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Polyconic:
    {
      Polyconic_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Polyconic_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Sinusoidal:
    {
      Sinusoidal_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Sinusoidal_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
 case Stereographic:
    {
      Stereographic_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Stereographic_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit22 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT22);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static22 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC22);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit23 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT23);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static23 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC23);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Transverse_Cylindrical_Equal_Area:
    {
      Transverse_Cylindrical_Equal_Area_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Transverse_Cylindrical_Equal_Area_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit1 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_output_edit3 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Transverse_Mercator:
    {
      Transverse_Mercator_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Transverse_Mercator_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit1 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT1);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static1 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC1);
      pWnd->ShowWindow(SW_SHOW);
      Latitude_to_String(params.origin_latitude*180/PI,latitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = latitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Origin Latitude:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.5lf",params.scale_factor);
      m_output_edit3 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT3);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static3 = "Scale Factor:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC3);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW); 
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
 /* case UPS:
    {
      Set_Coordinate_System(File,Output,output_type);
      break;
    }*/
  case UTM:
    {
      UTM_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_UTM_Params(File,Output,&params);

      m_set_zone_button = TRUE;
      OnDlgUtmButton();
      pWnd = GetDlgItem(IDC_DLG_UTM_BUTTON);
      pWnd->ShowWindow(SW_SHOW);
      pWnd = GetDlgItem(IDC_DLG_UTM_ZONE_LABEL);
      pWnd->ShowWindow(SW_SHOW);
      pWnd = GetDlgItem(IDC_DLG_UTM_ZONE_EDIT);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  case Van_der_Grinten:
    {
      Van_der_Grinten_Parameters params;
      Set_Coordinate_System(File,Output,output_type);
      Get_Van_der_Grinten_Params(File,Output,&params);
      Longitude_to_String(params.central_meridian*180/PI,longitude,use_NSEW,use_Minutes,use_Seconds);
      m_output_edit2 = longitude;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT2);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static2 = "Central Meridian:";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC2);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_easting);
      m_output_edit26 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT26);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static26 = "False Easting (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC26);
      pWnd->ShowWindow(SW_SHOW);
      sprintf(buf,"%1.0lf",params.false_northing);
      m_output_edit27 = buf;
      pWnd = GetDlgItem(IDC_OUTPUT_EDIT27);
      pWnd->ShowWindow(SW_SHOW);
      m_output_static27 = "False Northing (m):";
      pWnd = GetDlgItem(IDC_OUTPUT_STATIC27);
      pWnd->ShowWindow(SW_SHOW);
      break;
    }
  } /* switch (output_type) */
  UpdateData(FALSE);
}

// This function fills the system drop down list box.
void CFileProcDlg::FillSystemListBox()
{
  long count;

  long error_code = Get_Coordinate_System_Count(&count);
  if (error_code)
    MessageBox("Error getting coordinate system count!",NULL,MB_OK);
  else
  {
    CWnd* wPtr = GetDlgItem(IDC_OUTPUT_SYSTEM_COMBOBOX);
    for (int i = 0; i < count; i++)
    {
      char system_name[50];
      error_code = Get_Coordinate_System_Name(i+1,system_name);
      ((CComboBox*)wPtr)->AddString(system_name);
    }
    ((CComboBox*)wPtr)->SetCurSel(0);
    OnSelchangeOutputSystemCombobox();
  }
}

// This function sets the format to be used by the file proccessing module.
void CFileProcDlg::SetFormat(bool nsew,bool minutes,bool seconds)
{
  use_NSEW = nsew;
  use_Minutes = minutes;
  use_Seconds = seconds;
}

// This function is called when the user changes the state of the UTM Zone
// Override button.
void CFileProcDlg::OnDlgUtmButton()
{
  m_set_zone_button = !m_set_zone_button;
  CWnd* pWnd = GetDlgItem(IDC_DLG_UTM_BUTTON);
  ((CButton*)pWnd)->SetCheck(m_set_zone_button);
}

// This function is called when the user changes the zone overide edit field.
void CFileProcDlg::OnChangeDlgUtmZoneEdit()
{
  UpdateData(TRUE);

  CWnd* pWnd = GetDlgItem(IDC_DLG_UTM_ZONE_EDIT);

  double temp_val = 30;
  if ((m_zone.GetLength() > 0) && 
      (String_to_Double(m_zone, &temp_val) || 
      (temp_val < 1) || (temp_val > 60)))
  {
    int start,end;
    ((CEdit*)pWnd)->GetSel(start,end);
    ((CEdit*)pWnd)->SetSel(start-1,end);
    ((CEdit*)pWnd)->ReplaceSel("");
    MessageBeep(MB_ICONEXCLAMATION);
  }
  else
  {
    UTM_Parameters params;
    params.zone = (long)temp_val;
    params.override = 1;
    Set_UTM_Params(File,Output,params);
  }
}

// This function is called when the user presses the OK button.
void CFileProcDlg::OnOK()
{
  int status = 0;
  char err_str[256];
  UpdateData(TRUE); 
  switch (output_type)
  {
  case Albers_Equal_Area_Conic:
    {
      Albers_Equal_Area_Conic_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit21,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit22,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Latitude(m_output_edit23,&temp_val);
      params.std_parallel_1 = temp_val*PI/180;
      int error4 = String_to_Latitude(m_output_edit24,&temp_val);
      params.std_parallel_2 = temp_val*PI/180;
      int error5 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error6 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5 || error6)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
        Set_Albers_Equal_Area_Conic_Params(File,Output,params);
      break;
    }
  case Azimuthal_Equidistant:
    {
      // Layout 2*2*2
      Azimuthal_Equidistant_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
        Set_Azimuthal_Equidistant_Params(File,Output,params);
      break;
    }
  case Bonne:
    {
      // Layout 2*2*2
      Bonne_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Bonne_Params(File,Output,params);
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
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Cassini_Params(File,Output,params);
      break;
    }
  case Cylindrical_Equal_Area:
    {
      // Layout 2*2*2
      Cylindrical_Equal_Area_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Cylindrical_Equal_Area_Params(File,Output,params);
      break;
    }
  case Eckert4:
    {
      // Layout 1*2*2
      Eckert4_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit2,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error3 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Eckert4_Params(File,Output,params);
      break;
    }
  case Eckert6:
    {
      // Layout 1*2*2
      Eckert6_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit2,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error3 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Eckert6_Params(File,Output,params);
      break;
    }
  case Equidistant_Cylindrical:
    {
      // Layout 2*2*2
      Equidistant_Cylindrical_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.std_parallel = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Equidistant_Cylindrical_Params(File,Output,params);
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

      params.height_type = (Height_Types)m_file_height_combobox.GetCurSel();
      Set_Geodetic_Params(File,Output,params);
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
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Gnomonic_Params(File,Output,params);
      break;
    }
  case Lambert_Conformal_Conic_1:
    {
      // Layout:3*2*2
      Lambert_Conformal_Conic_1_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit1,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit2,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit3,&temp_val);
      params.scale_factor = temp_val;
      int error4 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error5 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Lambert_Conformal_Conic_1_Params(File,Output,params);
      break;
    }
  case Lambert_Conformal_Conic_2:
    {
      // Layout: 4*2*2
      Lambert_Conformal_Conic_2_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit21,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit22,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Latitude(m_output_edit23,&temp_val);
      params.std_parallel_1 = temp_val*PI/180;
      int error4 = String_to_Latitude(m_output_edit24,&temp_val);
      params.std_parallel_2 = temp_val*PI/180;
      int error5 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error6 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5 || error6)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
        Set_Lambert_Conformal_Conic_2_Params(File,Output,params);
      break;
    }
  case Local_Cartesian:
    {
      // Layout: 3*1*3
      Local_Cartesian_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit1,&temp_val);
      params.origin_longitude = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit2,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit3,&temp_val);
      params.origin_height = temp_val;
      int error4 = String_to_Longitude(m_output_edit5,&temp_val);
      params.orientation = temp_val*PI/180;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Local_Cartesian_Params(File,Output,params);
      break;
    }     
  case Mercator:
    {
      // Layout: 3*2*2
      Mercator_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit1,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit2,&temp_val);
      params.latitude_of_true_scale = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit3,&temp_val);
      params.scale_factor = temp_val;
      int error4 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error5 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Mercator_Params(File,Output,params);
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
      int error1 = String_to_Longitude(m_output_edit2,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error3 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Miller_Cylindrical_Params(File,Output,params);
      break;
    }
  case Mollweide:
    {
      // Layout:1*2*2
      Mollweide_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit2,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error3 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Mollweide_Params(File,Output,params);
      break;
    }
  case Neys:
    {
      // Layout: 4*2*2
      Neys_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit21,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit22,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = 0;     
      if (m_std_parallel1 == 0)
        params.std_parallel_1 = 71.0*PI/180;
      else if (m_std_parallel1 == 1)
        params.std_parallel_1 = 74.0*PI/180;
      else
        error3 = 1;

      int error4 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error5 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
        Set_Neys_Params(File,Output,params);
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
      int error1 = String_to_Latitude(m_output_edit21,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error2 = String_to_Double(m_output_edit22,&temp_val);
      params.scale_factor = temp_val;
      int error3 = String_to_Longitude(m_output_edit23,&temp_val);
      params.longitude_1 = temp_val*PI/180;
      int error4 = String_to_Latitude(m_output_edit24,&temp_val);
      params.latitude_1 = temp_val*PI/180;
      int error5 = String_to_Longitude(m_output_edit25,&temp_val);
      params.longitude_2 = temp_val*PI/180;
      int error6 = String_to_Latitude(m_output_edit26,&temp_val);
      params.latitude_2 = temp_val*PI/180;
      int error7 = String_to_Double(m_output_edit27,&temp_val);
      params.false_easting = temp_val;
      int error8 = String_to_Double(m_output_edit28,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5 || error6 || error7 || error8)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Oblique_Mercator_Params(File,Output,params);
      break;
    }
  case Orthographic:
    {
      // Layout:2*2*2
      Orthographic_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Orthographic_Params(File,Output,params);
      break;
    }
  case Polar_Stereo:
    {
      // Layout:2*2*2
      Polar_Stereo_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.longitude_down_from_pole = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.latitude_of_true_scale = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Polar_Stereo_Params(File,Output,params);
      break;
    }
  case Polyconic:
    {
      // Layout:2*2*2
      Polyconic_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Polyconic_Params(File,Output,params);
      break;
    }
  case Sinusoidal:
    {
      // Layout:1*2*2
      Sinusoidal_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit2,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error3 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Sinusoidal_Params(File,Output,params);
      break;

    }
  case Stereographic:
    {
      // Layout 2*2*2
      Stereographic_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit22,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit23,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error4 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
        Set_Stereographic_Params(File,Output,params);
      break;
    }
  case Transverse_Cylindrical_Equal_Area:
    {
      // Layout:3*2*2
      Transverse_Cylindrical_Equal_Area_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit1,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit2,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit3,&temp_val);
      params.scale_factor = temp_val;
      int error4 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error5 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Transverse_Cylindrical_Equal_Area_Params(File,Output,params);
      break;
    }
  case Transverse_Mercator:
    {
      // Layout:3*2*2
      Transverse_Mercator_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit1,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Latitude(m_output_edit2,&temp_val);
      params.origin_latitude = temp_val*PI/180;
      int error3 = String_to_Double(m_output_edit3,&temp_val);
      params.scale_factor = temp_val;
      int error4 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error5 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3 || error4 || error5)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Transverse_Mercator_Params(File,Output,params);
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
      UTM_Parameters params;
      double temp_val;
      if (m_set_zone_button)
      {
        params.override = 1;
        String_to_Double(m_zone,&temp_val);
        if (temp_val == 0)
        {
          status = 1;
          char temp_err_str[256];
          sprintf(err_str,"Error:\n");
          Error_Prefix(Output,output_type,"\n",temp_err_str);
          Error_Append("Invalid Zone","\n",temp_err_str);
          strcat(err_str, temp_err_str);
          AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
        }
        else
        {
          params.zone = (long)temp_val;
          Set_UTM_Params(File,Output,params);
        }
      }
      else
      {
        params.override = 0;
        params.zone = 0;
        Set_UTM_Params(File,Output,params);
      }
      break;
    }
  case Van_der_Grinten:
    {
      //Layout: 1*2*2
      Van_der_Grinten_Parameters params;
      double temp_val;
      int error1 = String_to_Longitude(m_output_edit2,&temp_val);
      params.central_meridian = temp_val*PI/180;
      int error2 = String_to_Double(m_output_edit26,&temp_val);
      params.false_easting = temp_val;
      int error3 = String_to_Double(m_output_edit27,&temp_val);
      params.false_northing = temp_val;
      if(error1 || error2 || error3)
      {
        status = 1;
        char temp_err_str[256];
        sprintf(err_str,"Error:\n");
        Error_Prefix(Output,output_type,"\n",temp_err_str);
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
      Set_Van_der_Grinten_Params(File,Output,params);
      break;
    }
  } // end of switch
  if (!status)
    CDialog::OnOK();
}

// This function is called when the user presses the Help button.
void CFileProcDlg::OnHelpButton()
{
  char buf[256];
  getcwd(buf, 256);

  chdir(current_dir);
  chdir("../help");

  ShellExecute( 0, NULL, "fileproc.htm",NULL, NULL, SW_NORMAL );

  chdir(buf);
}

void CFileProcDlg::OnFileOutputStdParallel71() 
{
  m_std_parallel1 = 0; /* std parallel 1 71 */
  CWnd *pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_71);
  ((CButton*)pWnd)->SetCheck(TRUE);
  pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_74);
  ((CButton*)pWnd)->SetCheck(FALSE);
  UpdateData(TRUE);
}

void CFileProcDlg::OnFileOutputStdParallel74() 
{
  m_std_parallel1 = 1; /* std parallel 1 74 */
  CWnd *pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_71);
  ((CButton*)pWnd)->SetCheck(FALSE);
  pWnd = GetDlgItem(IDC_FILE_OUTPUT_STD_PARALLEL1_74);
  ((CButton*)pWnd)->SetCheck(TRUE);
  UpdateData(TRUE);
}


void CFileProcDlg::Set_Current_Directory(char* dir)
{
  strcpy(current_dir, dir);
}

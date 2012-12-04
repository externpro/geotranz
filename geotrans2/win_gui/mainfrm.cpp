// mainfrm.cpp : implementation of the CMainFrame class
//

#include <direct.h>
#include <sys/stat.h>
#include "stdafx.h"
#include "geotrans.h"
#include "engine.h"
#include "fiomeths.h"
#include "strtoval.h"
#include "filevw.h"
#include "progress.h"
#include "ellipsevw.h"
#include "delellipvw.h"
#include "deldatumvw.h"
#include "mainfrm.h"
#include "mastervw.h"
#include "convertvw.h"
#include "defaults.h"
#include "CreateDatumPropertySheet.h"

#ifdef _DEBUG
  #undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
  ON_WM_CREATE()
  ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
  ON_COMMAND(ID_OPTIONS_COLORS_BACKGROUND, OnOptionsColorsBackground)
  ON_COMMAND(ID_OPTIONS_COLORS_TEXT, OnOptionsColorsText)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_SIGNHEMISPHERE_NSEW, OnOptionsGeodeticformatSignhemisphereNsew)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_SIGNHEMISPHERE_PLUS_MINUS, OnOptionsGeodeticformatSignhemispherePlusMinus)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_UNITS_DEGREESMINUTESSECONDS, OnOptionsGeodeticformatUnitsDegreesminutesseconds)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_UNITS_DEGREESMINUTES, OnOptionsGeodeticformatUnitsDegreesminutes)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_UNITS_DEGREE, OnOptionsGeodeticformatUnitsDegree)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_SIGNHEMISPHERE_NSEW, OnUpdateOptionsGeodeticformatSignhemisphereNsew)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_SIGNHEMISPHERE_PLUS_MINUS, OnUpdateOptionsGeodeticformatSignhemispherePlusMinus)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_UNITS_DEGREE, OnUpdateOptionsGeodeticformatUnitsDegree)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_UNITS_DEGREESMINUTES, OnUpdateOptionsGeodeticformatUnitsDegreesminutes)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_UNITS_DEGREESMINUTESSECONDS, OnUpdateOptionsGeodeticformatUnitsDegreesminutesseconds)
  ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
  ON_COMMAND(ID_OPTIONS_PRECISION_100000M, OnOptionsPrecision100000m)
  ON_COMMAND(ID_OPTIONS_PRECISION_10000M, OnOptionsPrecision10000m)
  ON_COMMAND(ID_OPTIONS_PRECISION_1000M, OnOptionsPrecision1000m)
  ON_COMMAND(ID_OPTIONS_PRECISION_100M, OnOptionsPrecision100m)
  ON_COMMAND(ID_OPTIONS_PRECISION_10M, OnOptionsPrecision10m)
  ON_COMMAND(ID_OPTIONS_PRECISION_1M, OnOptionsPrecision1m)
  ON_COMMAND(ID_OPTIONS_PRECISION_PNT1M, OnOptionsPrecisionPnt1m)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_100000M, OnUpdateOptionsPrecision100000m)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_10000M, OnUpdateOptionsPrecision10000m)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_1000M, OnUpdateOptionsPrecision1000m)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_100M, OnUpdateOptionsPrecision100m)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_10M, OnUpdateOptionsPrecision10m)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_1M, OnUpdateOptionsPrecision1m)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_PNT1M, OnUpdateOptionsPrecisionPnt1m)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_SEPARATOR_BLANKSPACE, OnOptionsGeodeticformatSeparatorBlankspace)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_SEPARATOR_BLANKSPACE, OnUpdateOptionsGeodeticformatSeparatorBlankspace)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_SEPARATOR_SLASH, OnUpdateOptionsGeodeticformatSeparatorSlash)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_SEPARATOR_SLASH, OnOptionsGeodeticformatSeparatorSlash)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_SEPARATOR_COLON, OnOptionsGeodeticformatSeparatorColon)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_SEPARATOR_COLON, OnUpdateOptionsGeodeticformatSeparatorColon)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_LONGITUDERANGE_180180, OnUpdateOptionsGeodeticformatLongituderange180180)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_LONGITUDERANGE_180180, OnOptionsGeodeticformatLongituderange180180)
  ON_COMMAND(ID_OPTIONS_GEODETICFORMAT_LONGITUDERANGE_0360, OnOptionsGeodeticformatLongituderange0360)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_GEODETICFORMAT_LONGITUDERANGE_0360, OnUpdateOptionsGeodeticformatLongituderange0360)
  ON_COMMAND(ID_OPTIONS_PRECISION_1CM, OnOptionsPrecision1cm)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_1CM, OnUpdateOptionsPrecision1cm)
  ON_COMMAND(ID_OPTIONS_PRECISION_1MM, OnOptionsPrecision1mm)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRECISION_1MM, OnUpdateOptionsPrecision1mm)
  ON_COMMAND(ID_OPTIONS_LEADING_ZEROS, OnOptionsLeadingZeros)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_LEADING_ZEROS, OnUpdateOptionsLeadingZeros)
  ON_COMMAND(ID_DATUM_CREATE, OnDatumCreate)
  ON_COMMAND(ID_DATUM_DELETE, OnDatumDelete)
  ON_COMMAND(ID_ELLIPSOID_CREATE, OnEllipsoidCreate)
  ON_COMMAND(ID_ELLIPSOID_DELETE, OnEllipsoidDelete)
  ON_COMMAND(ID_CONVERT_TO_LOWER, OnConvertUppertoLower)
  ON_COMMAND(ID_CONVERT_TO_UPPER, OnConvertLowertoUpper)
	ON_COMMAND(ID_SAVE_AS_DEFAULT, OnSaveAsDefault)
	ON_COMMAND(ID_RESTORE_DEFAULT, OnRestoreDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
  // same order as in the bitmap 'toolbar.bmp'
  ID_FILE_NEW,
  ID_FILE_OPEN,
  ID_FILE_SAVE,
  ID_SEPARATOR,
  ID_EDIT_CUT,
  ID_EDIT_COPY,
  ID_EDIT_PASTE,
  ID_SEPARATOR,
  ID_FILE_PRINT,
  ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
  ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() :
  data_dir_path_name( 0 )
{
  char *path_name = NULL;
 // char* data_dir_path_name = 0;
  const int file_name_length = 20;

  engine_initialized = true;
  precis = Tenth_of_Second;
  geodetic_hemiFlag = NSEW;
  geodetic_format = DMS;
  leading_zeros = 0;
  Set_Separator(' ');
  m_pSplitter = new CSplitterWnd();
  LOGBRUSH lb;
  lb.lbStyle = BS_SOLID;
  background_color = RGB(192,192,192);
  lb.lbColor = background_color;
  lb.lbHatch = HS_BDIAGONAL;
  background_brush = CreateBrushIndirect(&lb);
  text_color = RGB(0,0,0);
  long error_code = Initialize_Engine();
  // Check for ellipsoid file errors
  if (error_code  & ENGINE_ELLIPSOID_ERROR)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Unable to locate ellipsoid data file: ellips.dat!",MB_OK | MB_ICONEXCLAMATION);
  }
  if (error_code  & ENGINE_ELLIPSOID_OVERFLOW)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Ellipsoid table is full!",MB_OK | MB_ICONEXCLAMATION);
  }
  if (error_code  & ENGINE_INVALID_CODE_ERROR)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Invalid ellipsoid code!",MB_OK | MB_ICONEXCLAMATION);
  }

  // Check for datum file errors
  if (error_code  & ENGINE_DATUM_ERROR)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Unable to locate datum data files: 3_param.dat, 7_param.dat!",MB_OK | MB_ICONEXCLAMATION);
  }
  if (error_code  & ENGINE_DATUM_OVERFLOW)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Datum table is full!",MB_OK | MB_ICONEXCLAMATION);
  }
  if (error_code  & ENGINE_DATUM_FILE_PARSE_ERROR)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Unable to read datum file!",MB_OK | MB_ICONEXCLAMATION);
  }

  // Check for geoid file errors
  if (error_code  & ENGINE_GEOID_ERROR)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Unable to locate geoid data files: egm84.grd, egm96.grd!",MB_OK | MB_ICONEXCLAMATION);
  }
  if (error_code  & ENGINE_GEOID_FILE_PARSE_ERROR)
  {
    engine_initialized = false;
    AfxMessageBox("Error initializing GEOTRANS engine: Unable to read geoid file!",MB_OK | MB_ICONEXCLAMATION);
  }

  Set_Precision(precis);
  getcwd(current_dir, 256);


  /*  Check the environment for a user provided path, else current directory;   */
  /*  Build a File Name, including specified or default path:                   */

  path_name = getenv( "GEOTRANS_DATA" );
  if (path_name != NULL)
  {
    data_dir_path_name = new char[ strlen( path_name ) + 13 ];
    strcpy( data_dir_path_name, path_name );
    strcat( data_dir_path_name, "/" );
  }
  else
  {
    data_dir_path_name = new char[ file_name_length ];
    strcpy( data_dir_path_name, "../data/" );
  }
  strcat( data_dir_path_name, "default.xml" );

  defaults = new Defaults( data_dir_path_name );

  createDatumPropertySheet = new CCreateDatumPropertySheet("Create Datum");

}

CMainFrame::~CMainFrame()
{
  delete m_pSplitter;
  DeleteObject((HGDIOBJ)background_brush);

  delete [] data_dir_path_name;
  data_dir_path_name = 0;

  delete createDatumPropertySheet;
  createDatumPropertySheet = 0;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  lpCreateStruct->cx = 350;
  lpCreateStruct->cy = 300;
  lpCreateStruct->x = 50;
  lpCreateStruct->y = 50;

  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators,
                                    sizeof(indicators)/sizeof(UINT)))
  {
    TRACE("Failed to create status bar\n");
    return -1;      // fail to create
  }
  return 0;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
  if(engine_initialized)
  {
    BOOL rtn = m_pSplitter->CreateStatic(this,3,1);

    rtn |= m_pSplitter->CreateView(0,0,RUNTIME_CLASS(CMasterView),
                                   CSize( 20,265),pContext);

    rtn |= m_pSplitter->CreateView(1,0,RUNTIME_CLASS(CConvertView),
              CSize(25,30),pContext);

    rtn |= m_pSplitter->CreateView(2,0,RUNTIME_CLASS(CMasterView),
              CSize(280,265),pContext);

    CWnd* upper_p = m_pSplitter->GetPane(0,0); // upper view
    CWnd* lower_p = m_pSplitter->GetPane(2,0); // lower view

    ((CMasterView*)upper_p)->FillListBox();
    ((CMasterView*)lower_p)->FillListBox();

    ((CMasterView*)upper_p)->FillSourcesListBox();
    ((CMasterView*)lower_p)->FillSourcesListBox();

    ((CMasterView*)upper_p)->SetFormat(geodetic_format);
    ((CMasterView*)lower_p)->SetFormat(geodetic_format);

    ((CMasterView*)upper_p)->SetHemiFlag(geodetic_hemiFlag);
    ((CMasterView*)lower_p)->SetHemiFlag(geodetic_hemiFlag);

    ((CMasterView*)upper_p)->FillHeightList();
    ((CMasterView*)lower_p)->FillHeightList();

    ((CMasterView*)upper_p)->FillProjectionList(Geodetic);
    ((CMasterView*)lower_p)->FillProjectionList(UTM);

    CWnd* convert_p = m_pSplitter->GetPane(1,0); // convert view
    // These two functions of convertvw set up pointers to the forms.
    ((CConvertView*)convert_p)->SetUpperPointer((CMasterView*)upper_p);
    ((CConvertView*)convert_p)->SetLowerPointer((CMasterView*)lower_p);

    int width = 460;
    int height = 640; // dimensions of outer frame

    SetWindowPos(&wndNoTopMost,150,20,width,height,SWP_NOZORDER);

    struct stat stbuf;

    // If default file exists, initialize gui with defaults
    if( stat ( data_dir_path_name, &stbuf ) != -1 )
      defaults->restoreDefault( (CMasterView*)upper_p, (CMasterView*)lower_p, this );

    return rtn;
  }
  else
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
  CFrameWnd::Dump(dc);
}

#endif //_DEBUG


HBRUSH CMainFrame::GetBackgroundBrush()
{
  return background_brush;
}

COLORREF CMainFrame::GetBackgroundColor()
{
  return background_color;
}

COLORREF CMainFrame::GetTextColor()
{
  return text_color;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnHelpHelp()
{
  chdir(current_dir);
  chdir("../help");

  ShellExecute( 0, NULL, "contents.htm",NULL, NULL, SW_NORMAL );

}

void CMainFrame::OnOptionsColorsBackground()
{
  CColorDialog* m_wndColorDlg = new CColorDialog(background_color);
  LOGBRUSH lb;

  if (m_wndColorDlg->DoModal() != IDCANCEL)
  {
    background_color = m_wndColorDlg->GetColor();
    lb.lbStyle = BS_SOLID;
    lb.lbColor = background_color;
    lb.lbHatch = HS_BDIAGONAL;
    DeleteObject((HGDIOBJ)background_brush);
    background_brush = CreateBrushIndirect(&lb);
    RedrawWindow();
  }
  delete m_wndColorDlg;
}

void CMainFrame::OnOptionsColorsText()
{
  CColorDialog* m_wndColorDlg = new CColorDialog(text_color);

  if (m_wndColorDlg->DoModal() != IDCANCEL)
  {
    text_color = m_wndColorDlg->GetColor();
    RedrawWindow();
  }
  delete m_wndColorDlg;
}


void CMainFrame::OnOptionsGeodeticformatSignhemisphereNsew()
{
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);

  geodetic_hemiFlag = NSEW;
  ((CMasterView*)upper_pointer)->SetHemiFlag(geodetic_hemiFlag);
  ((CMasterView*)lower_pointer)->SetHemiFlag(geodetic_hemiFlag);
}

void CMainFrame::OnOptionsGeodeticformatSignhemispherePlusMinus()
{
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);

  geodetic_hemiFlag = PLUS_MINUS;
  ((CMasterView*)upper_pointer)->SetHemiFlag(geodetic_hemiFlag);
  ((CMasterView*)lower_pointer)->SetHemiFlag(geodetic_hemiFlag);
}

void CMainFrame::OnOptionsGeodeticformatUnitsDegreesminutesseconds()
{
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);

  geodetic_format = DMS;
  ((CMasterView*)upper_pointer)->SetFormat(geodetic_format);
  ((CMasterView*)lower_pointer)->SetFormat(geodetic_format);
}

void CMainFrame::OnOptionsGeodeticformatUnitsDegreesminutes()
{
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);

  geodetic_format = DM;
  ((CMasterView*)upper_pointer)->SetFormat(geodetic_format);
  ((CMasterView*)lower_pointer)->SetFormat(geodetic_format);
}

void CMainFrame::OnOptionsGeodeticformatUnitsDegree()
{
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);

  geodetic_format = DD;
  ((CMasterView*)upper_pointer)->SetFormat(geodetic_format);
  ((CMasterView*)lower_pointer)->SetFormat(geodetic_format);
}

void CMainFrame::OnUpdateOptionsGeodeticformatSignhemisphereNsew(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(geodetic_hemiFlag == NSEW);
}

void CMainFrame::OnUpdateOptionsGeodeticformatSignhemispherePlusMinus(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(geodetic_hemiFlag == PLUS_MINUS);
}

void CMainFrame::OnUpdateOptionsGeodeticformatUnitsDegree(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(geodetic_format == DD);
}

void CMainFrame::OnUpdateOptionsGeodeticformatUnitsDegreesminutes(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(geodetic_format == DM);
}

void CMainFrame::OnUpdateOptionsGeodeticformatUnitsDegreesminutesseconds(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(geodetic_format == DMS);
}


void CMainFrame::OnFileOpen()
{
  CFileDialog* p_fileOpenDlg = new CFileDialog(TRUE,"dat","*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Data Files (*.dat)|*.dat|All Files (*.*)|*.*||");
  if (p_fileOpenDlg->DoModal() != IDCANCEL)
  {
    CString filename = p_fileOpenDlg->GetPathName();
    FIO_Status file_error = Set_Input_Filename(filename);
    if (file_error)
    {
      char err_str[256];
      char temp_err_str[256];
      sprintf(err_str,"Error:\n");
      Get_File_Error_String(file_error,temp_err_str);
      strcat(err_str, temp_err_str);
      AfxMessageBox(err_str,MB_OK | MB_ICONEXCLAMATION);
      Close_Input_File();
    }
    else
    {
      CFileProcDlg* p_fileProcDlg = new CFileProcDlg();
      p_fileProcDlg->Set_Current_Directory(current_dir);
      p_fileProcDlg->SetFormat
          ( (geodetic_hemiFlag == NSEW) ? TRUE : FALSE,
            (geodetic_format != DD) ? TRUE : FALSE,
            (geodetic_format == DMS) ? TRUE : FALSE);
      Use_NSEW( (geodetic_hemiFlag == NSEW) ? TRUE : FALSE);
      Use_Minutes( (geodetic_format != DD) ? TRUE : FALSE);
      Use_Seconds( (geodetic_format == DMS) ? TRUE : FALSE);

      if (p_fileProcDlg->DoModal() != IDCANCEL)
      {
        CFileDialog* p_fileSaveDlg = new CFileDialog(FALSE,"dat","*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Data Files (*.dat)|*.dat|All Files (*.*)|*.*||");

        if (p_fileSaveDlg->DoModal() != IDCANCEL)
        {
          filename = p_fileSaveDlg->GetPathName();
          if (Set_Output_Filename(filename))
          {
            AfxMessageBox("Error opening output file.",MB_OK | MB_ICONEXCLAMATION);
            Close_Input_File();
          }
          else
          {
            Progress* p_Progress = new Progress(this);
            if (p_Progress->DoModal() == IDCANCEL)
            {
              Close_Input_File();
              Close_Output_File();
            }
            delete p_Progress;
          }
        }
        else
          Close_Input_File();
        delete p_fileSaveDlg;
      }
      else
        Close_Input_File();
      delete p_fileProcDlg;
    }
  }
  delete p_fileOpenDlg;
}

void CMainFrame::OnOptionsPrecision100000m()
{
  precis = Degree;
  Set_Precision(Degree);
  Set_Lat_Long_Precision(Degree);
}

void CMainFrame::OnOptionsPrecision10000m()
{
  precis = Ten_Minutes;
  Set_Precision(Ten_Minutes);
  Set_Lat_Long_Precision(Ten_Minutes);
}

void CMainFrame::OnOptionsPrecision1000m()
{
  precis = Minute;
  Set_Precision(Minute);
  Set_Lat_Long_Precision(Minute);
}

void CMainFrame::OnOptionsPrecision100m()
{
  precis = Ten_Seconds;
  Set_Precision(Ten_Seconds);
  Set_Lat_Long_Precision(Ten_Seconds);
}

void CMainFrame::OnOptionsPrecision10m()
{
  precis = Second;
  Set_Precision(Second);
  Set_Lat_Long_Precision(Second);
}

void CMainFrame::OnOptionsPrecision1m()
{
  precis = Tenth_of_Second;
  Set_Precision(Tenth_of_Second);
  Set_Lat_Long_Precision(Tenth_of_Second);
}

void CMainFrame::OnOptionsPrecisionPnt1m()
{
  AfxMessageBox("Warning:  Output accuracy is limited to ~1m",MB_OK | MB_ICONEXCLAMATION);
  precis = Hundredth_of_Second;
  Set_Precision(Hundredth_of_Second);
  Set_Lat_Long_Precision(Hundredth_of_Second);
}

void CMainFrame::OnOptionsPrecision1cm()
{
  AfxMessageBox("Warning:  Output accuracy is limited to ~1m",MB_OK | MB_ICONEXCLAMATION);
  precis = Thousandth_of_Second;
  Set_Precision(Thousandth_of_Second);
  Set_Lat_Long_Precision(Thousandth_of_Second);
}

void CMainFrame::OnOptionsPrecision1mm()
{
  AfxMessageBox("Warning:  Output accuracy is limited to ~1m",MB_OK | MB_ICONEXCLAMATION);
  precis = Ten_Thousandth_of_Second;
  Set_Precision(Ten_Thousandth_of_Second);
  Set_Lat_Long_Precision(Ten_Thousandth_of_Second);
}

void CMainFrame::OnUpdateOptionsPrecision100000m(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Degree);
}

void CMainFrame::OnUpdateOptionsPrecision10000m(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Ten_Minutes);
}

void CMainFrame::OnUpdateOptionsPrecision1000m(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Minute);
}

void CMainFrame::OnUpdateOptionsPrecision100m(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Ten_Seconds);
}

void CMainFrame::OnUpdateOptionsPrecision10m(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Second);
}

void CMainFrame::OnUpdateOptionsPrecision1m(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Tenth_of_Second);
}

void CMainFrame::OnUpdateOptionsPrecisionPnt1m(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Hundredth_of_Second);
}

void CMainFrame::OnUpdateOptionsPrecision1cm(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Thousandth_of_Second);
}

void CMainFrame::OnUpdateOptionsPrecision1mm(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(precis == Ten_Thousandth_of_Second);
}

void CMainFrame::OnOptionsGeodeticformatSeparatorBlankspace()
{
  Set_Separator(' ');
}

void CMainFrame::OnOptionsGeodeticformatSeparatorSlash()
{
  Set_Separator('/');
}

void CMainFrame::OnOptionsGeodeticformatSeparatorColon()
{
  Set_Separator(':');
}

void CMainFrame::OnUpdateOptionsGeodeticformatSeparatorBlankspace(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(Get_Separator() == ' ');
}

void CMainFrame::OnUpdateOptionsGeodeticformatSeparatorSlash(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(Get_Separator() == '/');
}

void CMainFrame::OnUpdateOptionsGeodeticformatSeparatorColon(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(Get_Separator() == ':');
}

void CMainFrame::OnUpdateOptionsGeodeticformatLongituderange180180(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(Get_Long_Range() == _180_180);
}

void CMainFrame::OnOptionsGeodeticformatLongituderange180180()
{
  Set_Long_Range(_180_180);
}

void CMainFrame::OnOptionsGeodeticformatLongituderange0360()
{
  Set_Long_Range(_0_360);
}

void CMainFrame::OnUpdateOptionsGeodeticformatLongituderange0360(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(Get_Long_Range() == _0_360);
}

void CMainFrame::OnOptionsLeadingZeros()
{
  leading_zeros = !leading_zeros;
  Show_Leading_Zeros(leading_zeros);
}

void CMainFrame::OnUpdateOptionsLeadingZeros(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(leading_zeros);
}

void CMainFrame::OnDatumCreate()
{
    createDatumPropertySheet->Create(this);

    CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
    CWnd* lower_pointer = m_pSplitter->GetPane(2,0);
    createDatumPropertySheet->setViews((CMasterView*)upper_pointer, (CMasterView*)lower_pointer);
}

void CMainFrame::OnDatumDelete()
{
  CDeleteDatumView* p_DeleteDatumDlg = new CDeleteDatumView();
  p_DeleteDatumDlg->DoModal();
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);
  ((CMasterView*)upper_pointer)->FillListBox();
  ((CMasterView*)lower_pointer)->FillListBox();
  delete p_DeleteDatumDlg;
}

void CMainFrame::OnEllipsoidCreate()
{
  CEllipsoidView* p_EllipsoidDlg = new CEllipsoidView();
  p_EllipsoidDlg->DoModal();
  delete p_EllipsoidDlg;
}

void CMainFrame::OnEllipsoidDelete()
{
  CDeleteEllipsoid* p_DeleteEllipsoidDlg = new CDeleteEllipsoid();
  p_DeleteEllipsoidDlg->DoModal();
  delete p_DeleteEllipsoidDlg;
}


void CMainFrame::OnConvertUppertoLower() 
{
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);

  ((CMasterView*)upper_pointer)->SetFormat(geodetic_format);
  ((CMasterView*)upper_pointer)->SetHemiFlag(geodetic_hemiFlag);
  ((CMasterView*)lower_pointer)->SetFormat(geodetic_format);
  ((CMasterView*)lower_pointer)->SetHemiFlag(geodetic_hemiFlag);

  ((CConvertView*)upper_pointer)->SetUpperPointer((CMasterView*)upper_pointer);
  ((CConvertView*)upper_pointer)->SetLowerPointer((CMasterView*)lower_pointer);
  ((CConvertView*)upper_pointer)->OnConvertUppertoLower();
}


void CMainFrame::OnConvertLowertoUpper() 
{
  CWnd* upper_pointer = m_pSplitter->GetPane(0,0);
  CWnd* lower_pointer = m_pSplitter->GetPane(2,0);

  ((CMasterView*)upper_pointer)->SetFormat(geodetic_format);
  ((CMasterView*)upper_pointer)->SetHemiFlag(geodetic_hemiFlag);
  ((CMasterView*)lower_pointer)->SetFormat(geodetic_format);
  ((CMasterView*)lower_pointer)->SetHemiFlag(geodetic_hemiFlag);

  ((CConvertView*)lower_pointer)->SetUpperPointer((CMasterView*)upper_pointer);
  ((CConvertView*)lower_pointer)->SetLowerPointer((CMasterView*)lower_pointer);
  ((CConvertView*)lower_pointer)->OnConvertLowertoUpper();

}

void CMainFrame::Check_3D_Conversion()
{
  bool _3dConversion = false;
  CWnd *pWnd;
  CMasterView* upper_view = (CMasterView*)m_pSplitter->GetPane(0,0);
  CMasterView* lower_view = (CMasterView*)m_pSplitter->GetPane(2,0);

  if (upper_view->type == Geodetic)
  {
    if ((lower_view->type == Geodetic) || (lower_view->type == Geocentric) || (lower_view->type == Local_Cartesian))
    {
      upper_view->m_height_combobox.EnableWindow(TRUE);

        if( upper_view->getGeodeticHeight() == No_Height )
          upper_view->setGeodeticHeight(Ellipsoid_Height);
        _3dConversion = true;
        pWnd = upper_view->GetDlgItem(IDC_EDIT9);
        ((CEdit*)pWnd)->SetReadOnly(FALSE);

      if (lower_view->type == Geodetic)
      {
        lower_view->m_height_combobox.EnableWindow(TRUE);
        lower_view->setGeodeticHeight(Ellipsoid_Height);
        pWnd = lower_view->GetDlgItem(IDC_EDIT9);
        ((CEdit*)pWnd)->SetReadOnly(FALSE);
      }
    }
    else
    {
      upper_view->setGeodeticHeight(No_Height);
      pWnd = upper_view->GetDlgItem(IDC_EDIT9);
      ((CEdit*)pWnd)->SetReadOnly(TRUE);
      ((CEdit*)pWnd)->SetWindowText("0");
      upper_view->m_height_combobox.EnableWindow(FALSE);
    }
  }
  else if (lower_view->type == Geodetic)
  {
    if ((upper_view->type == Geocentric) || (upper_view->type == Local_Cartesian)) 
    {
      lower_view->m_height_combobox.EnableWindow(TRUE);

      if( lower_view->getGeodeticHeight() == No_Height )
        lower_view->setGeodeticHeight(Ellipsoid_Height);
      _3dConversion = true;
      pWnd = lower_view->GetDlgItem(IDC_EDIT9);
      ((CEdit*)pWnd)->SetReadOnly(FALSE);
    }
    else
    {
      lower_view->setGeodeticHeight(No_Height);
      pWnd = lower_view->GetDlgItem(IDC_EDIT9);
      ((CEdit*)pWnd)->SetReadOnly(TRUE);
      ((CEdit*)pWnd)->SetWindowText("0");
      lower_view->m_height_combobox.EnableWindow(FALSE);
    }
  }
  else if (((upper_view->type == Geocentric) || (upper_view->type == Local_Cartesian)) &&
        ((lower_view->type == Geocentric) || (lower_view->type == Local_Cartesian)))
      _3dConversion = true;

  if (_3dConversion)
  {
      pWnd = upper_view->GetDlgItem(ID_LE90);
        ((CEdit*)pWnd)->EnableWindow(TRUE);
      pWnd = upper_view->GetDlgItem(ID_SE90);
        ((CEdit*)pWnd)->EnableWindow(TRUE);
      pWnd = lower_view->GetDlgItem(ID_LE90);
        ((CEdit*)pWnd)->EnableWindow(TRUE);
      pWnd = lower_view->GetDlgItem(ID_SE90);
        ((CEdit*)pWnd)->EnableWindow(TRUE);
  }
  else
  {
      pWnd = upper_view->GetDlgItem(ID_LE90);
        ((CEdit*)pWnd)->EnableWindow(FALSE);
      pWnd = upper_view->GetDlgItem(ID_SE90);
        ((CEdit*)pWnd)->EnableWindow(FALSE);
      pWnd = lower_view->GetDlgItem(ID_LE90);
        ((CEdit*)pWnd)->EnableWindow(FALSE);
      pWnd = lower_view->GetDlgItem(ID_SE90);
        ((CEdit*)pWnd)->EnableWindow(FALSE);
  }

  upper_view->UpdateSrcErrors(_3dConversion);
  lower_view->UpdateSrcErrors(_3dConversion);
}


void CMainFrame::Check_Valid_Conversion()
{
  CMasterView* upper_view = (CMasterView*)m_pSplitter->GetPane(0,0);
  CMasterView* lower_view = (CMasterView*)m_pSplitter->GetPane(2,0);

  int valid = Valid_Conversion(upper_view->type, lower_view->type, upper_view->datum_index, lower_view->datum_index);
  
  CConvertView* convert_view = (CConvertView*)(m_pSplitter->GetPane(1,0)); 

  if(valid == RED)
    convert_view->SetButtonColor(235, 85, 85);
  else if(valid == YELLOW)
    convert_view->SetButtonColor(224, 224, 123);
  else if(valid == GREEN)
    convert_view->SetButtonColor(94, 192, 94);
  RedrawWindow();
}


// Set current format settings as defaults
void CMainFrame::OnSaveAsDefault() 
{
  CMasterView* upper_view = (CMasterView*)m_pSplitter->GetPane(0,0);
  CMasterView* lower_view = (CMasterView*)m_pSplitter->GetPane(2,0);

  defaults->saveAsDefault( upper_view, lower_view, this );
}


// Restore format settings to default values
void CMainFrame::OnRestoreDefault() 
{
  CMasterView* upper_view = (CMasterView*)m_pSplitter->GetPane(0,0);
  CMasterView* lower_view = (CMasterView*)m_pSplitter->GetPane(2,0);

  defaults->restoreDefault( upper_view, lower_view, this );
}


// Get current format settings
int CMainFrame::getUnits()
{
  if( geodetic_format == DMS )
    return 0;
  else if( geodetic_format == DM )
    return 1;
  else//// if( geodetic_format == DD )
    return 2;
}


char* CMainFrame::getUnitsString()
{
  if( geodetic_format == DMS )
    return "DMS";
  else if( geodetic_format == DM )
    return "DM";
  else//// if( geodetic_format ==  DD)
    return "DEG";
}


int CMainFrame::getSeparatorIndex()
{
  char separator = Get_Separator();

  if( separator == ' ')
    return 0;
  else if( separator == '/')
    return 1;
  else ///if( separator == ':')
    return 2;

}


char CMainFrame::getSeparator()
{
  return Get_Separator();
}


int CMainFrame::getSignHemi()
{
  if( geodetic_hemiFlag == PLUS_MINUS )
    return 0;
  else// if( geodetic_hemiFlag == NSEW )
    return 1;
}


char* CMainFrame::getSignHemiString()
{
  if( geodetic_hemiFlag == PLUS_MINUS)
    return "+/-";
  else //if( geodetic_hemiFlag == NSEW  )
    return "N/S,E/W";
}


int CMainFrame::getRange()
{
  return Get_Long_Range();
}


char* CMainFrame::getRangeString()
{
  int longitudeRange = Get_Long_Range();
  if( longitudeRange == _180_180)
    return "(-180,180)";
  else //if( geodetic_hemiFlag == NSEW  )
    return "(0,360)";
}


int CMainFrame::getPrecision()
{
  return precis;
}


char* CMainFrame::getPrecisionString()
{
  if( precis == Degree )
    return "100,000m";
  else if( precis == Ten_Minutes )
    return "10,000m";
  else if( precis ==  Minute)
    return "1,000m";
  else if( precis ==  Ten_Seconds)
    return "100m";
  else if( precis ==  Second)
    return "10m";
  else if( precis ==  Tenth_of_Second)
    return "1m";
  else if( precis ==  Hundredth_of_Second)
    return "0.1m";
  else if( precis ==  Thousandth_of_Second)
    return "0.01m";
  else/// if( precis ==  Ten_Thousandth_of_Second)
    return "0.001m";
}


char* CMainFrame::getLeadingZeros()
{
  if( leading_zeros )
    return "true";
  else 
    return "false";
}


// Set format settings
void CMainFrame::setUnits( int units )
{
  switch( units )
  {
    case 0:
      OnOptionsGeodeticformatUnitsDegreesminutesseconds();
      break;
    case 1:
      OnOptionsGeodeticformatUnitsDegreesminutes();
      break;
    case 2:
      OnOptionsGeodeticformatUnitsDegree();
      break;
  }
}


void CMainFrame::setSeparator( int separator )
{
  switch( separator )
  {
    case 0:
      OnOptionsGeodeticformatSeparatorBlankspace();
      break;
    case 1:
      OnOptionsGeodeticformatSeparatorSlash();
      break;
    case 2:
      OnOptionsGeodeticformatSeparatorColon();
      break;
  }
}


void CMainFrame::setSignHemi( int signHemi )
{
  switch( signHemi )
  {
    case 0:
      OnOptionsGeodeticformatSignhemispherePlusMinus();
      break;
    case 1:
      OnOptionsGeodeticformatSignhemisphereNsew();
      break;
  }
}


void CMainFrame::setLongitudeRange( int longitudeRange )
{
  switch( longitudeRange )
  {
    case 0:
      OnOptionsGeodeticformatLongituderange180180();
      break;
    case 1:
      OnOptionsGeodeticformatLongituderange0360();
      break;
  }
}


void CMainFrame::setPrecision( int precision )
{
  switch( precision )
  {
    case 0:
      OnOptionsPrecision100000m();
      break;
    case 1:
      OnOptionsPrecision10000m();
      break;
    case 2:
      OnOptionsPrecision1000m();
      break;
    case 3:
      OnOptionsPrecision100m();
      break;
    case 4:
      OnOptionsPrecision10m();
      break;
    case 5:
      OnOptionsPrecision1m();
      break;
    case 6:
      OnOptionsPrecisionPnt1m();
      break;
    case 7:
      OnOptionsPrecision1cm();
      break;
    case 8:
      OnOptionsPrecision1mm();
      break;
  }
}

void CMainFrame::setLeadingZeros( char* leadingZeros )
{
  if( strcmp( leadingZeros, "false" ) == 0 )
    leading_zeros = 0;
  else
    leading_zeros = 1;

  Show_Leading_Zeros( leading_zeros );
}

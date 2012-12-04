// progress.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "progress.h"
#include "fiomeths.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Progress dialog


Progress::Progress(CWnd* pParent /*=NULL*/)
: CDialog(Progress::IDD, pParent)
{
  //{{AFX_DATA_INIT(Progress)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void Progress::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(Progress)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Progress, CDialog)
//{{AFX_MSG_MAP(Progress)
ON_BN_CLICKED(IDC_START, OnStart)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Progress message handlers

void Progress::OnStart()
{
  SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
 
  CWnd *pWnd = GetDlgItem(IDC_START);
  pWnd->EnableWindow(FALSE);
  pWnd = GetDlgItem(IDCANCEL);
  pWnd->EnableWindow(FALSE);
  pWnd = GetDlgItem(IDC_LABEL);
  pWnd->ShowWindow(SW_SHOW);
  pWnd->SetWindowText("In Progress");

  long errors;
  long processed;
  long warnings;
  if (Convert_File(&errors,&processed,&warnings))
  {
    AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    AfxMessageBox("Error parsing input file.",MB_OK | MB_ICONEXCLAMATION);
    EndDialog(IDCANCEL);
  }

  char str[256];
  sprintf(str,"Completed\n\nNumber of coordinates processed = %ld\nNumber of warnings = %ld\nNumber of errors = %ld\n",processed, warnings, errors);
  pWnd->SetWindowText(str);
  pWnd = GetDlgItem(IDOK);
  pWnd->EnableWindow(TRUE);
  SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}


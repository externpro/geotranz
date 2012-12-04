// geotrans.h : main header file for the GEOTRANS application
//
#define GEODETIC_FRAME 		1
#define GEOCENTRIC_FRAME	2
#define MERCATOR_FRAME		3
#define TRANSMERC_FRAME		4
#define UTM_FRAME			   5
#define LAM1_FRAME			6
#define LAM2_FRAME			7
#define PS_FRAME			   8
#define UPS_FRAME			   9
#define GEOREF_FRAME		  10
#define MGRS_FRAME		  11

#define NSEW				12
#define PLUS_MINUS		13
#define DMS					14
#define DM					15
#define DD					16

/* These must match the mapped values in the help
   project file */
#define HID_CONTENTS		101
#define HID_FILE_PROCESSING 102

#define PI 3.14159265358979323e0

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGeotransApp:
// See geotrans.cpp for the implementation of this class
//

class CGeotransApp : public CWinApp
{
public:
	CGeotransApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CGeotransApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

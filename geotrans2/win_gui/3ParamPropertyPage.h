#if !defined(AFX_3PARAMPROPERTYPAGE_H__EF957C82_2DC5_438B_9B2E_1E6BD72AD1B3__INCLUDED_)
#define AFX_3PARAMPROPERTYPAGE_H__EF957C82_2DC5_438B_9B2E_1E6BD72AD1B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3ParamPropertyPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3ParamPropertyPage dialog

class C3ParamPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(C3ParamPropertyPage)

// Construction
public:
	C3ParamPropertyPage();
	~C3ParamPropertyPage();

  long createDatum();

// Dialog Data
	//{{AFX_DATA(C3ParamPropertyPage)
	enum { IDD = IDD_3PARAM_PROPPAGE };
	CString	m_datum_code;
	CString	m_deltaX;
	CString	m_deltaY;
	CString	m_deltaZ;
	CString	m_datum_name;
	CString	m_sigmaX;
	CString	m_sigmaY;
	CString	m_sigmaZ;
	int		m_ellipsoid_index;
	CString	m_east_lon;
	CString	m_north_lat;
	CString	m_south_lat;
	CString	m_west_lon;
	//}}AFX_DATA
   const char* m_datum_code_value;
   const char* m_datum_name_value;
   double   m_deltaX_value;
   double   m_deltaY_value;
   double   m_deltaZ_value;
   double   m_sigmaX_value;
   double   m_sigmaY_value;
   double   m_sigmaZ_value;
   double   m_west_lon_value;
   double   m_east_lon_value;
   double   m_south_lat_value;
   double   m_north_lat_value;
   bool close_property_page;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C3ParamPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void FillListBox();

protected:
    BOOL OnInitDialog(void);
	// Generated message map functions
	//{{AFX_MSG(C3ParamPropertyPage)
	afx_msg void OnChangeDatumCode();
	afx_msg void OnChangeDatumName();
	afx_msg void OnChangeDatumDeltax();
	afx_msg void OnChangeDatumDeltay();
	afx_msg void OnChangeDatumDeltaz();
	afx_msg void OnChangeDatumSigmax();
	afx_msg void OnChangeDatumSigmay();
	afx_msg void OnChangeDatumSigmaz();
	afx_msg void OnSelchangeDatumEllipsoidCombobox();
	afx_msg void OnChangeDatumEastLon();
	afx_msg void OnChangeDatumNorthLat();
	afx_msg void OnChangeDatumSouthLat();
	afx_msg void OnChangeDatumWestLon();
//	virtual BOOL OnKillActive();
//	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3PARAMPROPERTYPAGE_H__EF957C82_2DC5_438B_9B2E_1E6BD72AD1B3__INCLUDED_)

#if !defined(AFX_7PARAMPROPERTYPAGE_H__A143374B_F773_4D02_AB8F_5C828616F952__INCLUDED_)
#define AFX_7PARAMPROPERTYPAGE_H__A143374B_F773_4D02_AB8F_5C828616F952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 7ParamPropertyPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C7ParamPropertyPage dialog

class C7ParamPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(C7ParamPropertyPage)

// Construction
public:
	C7ParamPropertyPage();
	~C7ParamPropertyPage();

  long createDatum();

// Dialog Data
	//{{AFX_DATA(C7ParamPropertyPage)
	enum { IDD = IDD_7PARAM_PROPPAGE };
	CString	m_datum_code;
	CString	m_deltaX;
	CString	m_deltaY;
	CString	m_deltaZ;
	CString	m_datum_name;
	CString	m_rotationX;
	CString	m_rotationY;
	CString	m_rotationZ;
	CString	m_scale;
	int		m_ellipsoid_index;
	//}}AFX_DATA
   const char* m_datum_code_value;
   const char* m_datum_name_value;
   double   m_deltaX_value;
   double   m_deltaY_value;
   double   m_deltaZ_value;
   double   m_rotationX_value;
   double   m_rotationY_value;
   double   m_rotationZ_value;
   double   m_scale_value;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C7ParamPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
  void FillListBox();

protected:
	// Generated message map functions
	//{{AFX_MSG(C7ParamPropertyPage)
	afx_msg void OnChangeDatumCode();
	afx_msg void OnChangeDatumName();
	afx_msg void OnChangeDatumDeltax();
	afx_msg void OnChangeDatumDeltay();
	afx_msg void OnChangeDatumDeltaz();
	afx_msg void OnChangeDatumRotationX();
	afx_msg void OnChangeDatumRotationY();
	afx_msg void OnChangeDatumRotationZ();
	afx_msg void OnSelchangeDatumEllipsoidCombobox();
	afx_msg void OnChange7ParamDatumScale();
	virtual BOOL OnInitDialog();
//	virtual BOOL OnKillActive();
//	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_7PARAMPROPERTYPAGE_H__A143374B_F773_4D02_AB8F_5C828616F952__INCLUDED_)

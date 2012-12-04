#if !defined(AFX_ELLIPSEVW_H__E67C9FC1_1C1E_11D3_BCEB_0000E20FD521__INCLUDED_)
#define AFX_ELLIPSEVW_H__E67C9FC1_1C1E_11D3_BCEB_0000E20FD521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ellipsevw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEllipsoidView dialog

class CEllipsoidView : public CDialog
{
// Construction
public:
	CEllipsoidView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
private:
	//{{AFX_DATA(CEllipsoidView)
	enum { IDD = IDD_ELLIPSOID_DIALOG };
	CString	m_ellipsoid_code;
	CString	m_ellipsoid_name;
	CString	m_semimajor_axis;
	CString	m_inverse_flat;
	//}}AFX_DATA
   double   m_semimajor_axis_value;
   double   m_inverse_flat_value;
   const char* m_ellipsoid_code_value;
   const char* m_ellipsoid_name_value;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEllipsoidView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEllipsoidView)
	afx_msg void OnChangeEllipsoidCode();
	afx_msg void OnChangeEllipsoidName();
	afx_msg void OnChangeEllipsoidSemimajorAxis();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeEllipsoidInverseFlat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELLIPSEVW_H__E67C9FC1_1C1E_11D3_BCEB_0000E20FD521__INCLUDED_)

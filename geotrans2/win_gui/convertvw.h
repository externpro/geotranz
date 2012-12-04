#if !defined(AFX_CONVERTVW_H__DAB26525_3C58_11D4_BCEB_0000E20FD521__INCLUDED_)
#define AFX_CONVERTVW_H__DAB26525_3C58_11D4_BCEB_0000E20FD521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// convertvw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvertView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ColorButton.h"

class CConvertView : public CFormView
{
protected:
	DECLARE_DYNCREATE(CConvertView)

// Form Data
public:
	CConvertView();           // protected constructor used by dynamic creation
	void SetUpperPointer( CMasterView* p_view1);
	void SetLowerPointer( CMasterView* p_view2);
  void SetButtonColor(int red, int green, int blue);

private:
	CMasterView* p_upper_view;
	CMasterView* p_lower_view;


	//{{AFX_DATA(CConvertView)
	enum { IDD = IDD_CONVERT_FORM };
	CColorButton*	c_convert_to_upper_button;
	CColorButton*	c_convert_to_lower_button;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

	afx_msg void OnConvertUppertoLower();
	afx_msg void OnConvertLowertoUpper();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvertView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CConvertView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CConvertView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERTVW_H__DAB26525_3C58_11D4_BCEB_0000E20FD521__INCLUDED_)

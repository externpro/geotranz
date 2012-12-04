#if !defined(AFX_COLORBUTTON_H__DF02F3D6_73E0_467E_BF9A_289767173537__INCLUDED_)
#define AFX_COLORBUTTON_H__DF02F3D6_73E0_467E_BF9A_289767173537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
// Construction
public:
	CColorButton();

// Attributes
public:

// Operations
public:
  void SetColor( COLORREF color );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
  COLORREF button_color;
  CBrush c_brush;
//  HBRUSH c_brush;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__DF02F3D6_73E0_467E_BF9A_289767173537__INCLUDED_)
